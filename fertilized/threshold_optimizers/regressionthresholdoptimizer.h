/* Author: Moritz Einfalt, Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_REGRESSIONTHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_REGRESSIONTHRESHOLDOPTIMIZER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#if defined(_OPENMP)
#include <omp.h>
#endif

#include <type_traits>
#include <vector>
#include <limits>
#include <random>
#include <set>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/sampling.h"
#include "../util/argsort.h"
#include "../regression/iregressioncalculator.h"
#include "../impurities/ientropyfunction.h"
#include "./ithresholdoptimizer.h"
#include "./feature_value_selection.h"

namespace fertilized {

  /**
   * \brief Optimizes the threshold for splitting a dataset, to ensure optimal
   * regression results on the splits.
   *
   * This threshold optimizer draws n_thresholds random values between
   * the minimum and maximum observed feature value and returns the best
   * one.
   * Multiple annotations (and therefore multiple output regression) are allowed.
   * The splits are evaluated using a provided regression calculator.
   *
   * \ingroup fertilizedthreshold_optimizersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float; float
   * - double; double
   * .
   *
   * -----
   *
   */
  template<typename input_dtype, typename feature_dtype>
  class RegressionThresholdOptimizer
    : public IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> {
   public:
    typedef IThresholdOptimizer<input_dtype,
                  feature_dtype,
                                input_dtype> IThresholdOptimizer_t;
    using typename IThresholdOptimizer_t::data_prov_t;
    using typename IThresholdOptimizer_t::optimization_tuple_t;
    typedef IRegressionCalculator<input_dtype> IRegressionCalculator_t;
    typedef typename IRegressionCalculator_t::Matrix_regression_t Matrix_regression_t;
    typedef typename IRegressionCalculator_t::Vector_regression_t Vector_regression_t;


    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param n_thresholds size_t>0
     *   Number of randomly drawn threshold values that are asessed.
     * \param regression_calculator shared(IRegressionCalculator)
     *   The regression calculator used to evaluate possible splits.
     * \param entropy_function shared(IEntropyFunction)
     *   The entropy function used on the regression results.
     * \param gain_threshold float >=0.f
     *   The minimum information gain a split has to achieve.
     * \param annotation_step size_t >0
     *   The memory layout of sample annotations.
     * \param random_seed uint >0
     *   The random seed.
     * \returns A new RegressionThresholdOptimizer.
     */
    RegressionThresholdOptimizer(
      const size_t & n_thresholds,
      const std::shared_ptr<IRegressionCalculator<input_dtype>> & regression_calculator,
      const std::shared_ptr<IEntropyFunction<float>> &entropy_function,
      const float &gain_threshold=1E-7f,
      const size_t &annotation_step=1,
      const unsigned int  & random_seed=1)
      : n_thresholds(n_thresholds),
        reg_calc_template(regression_calculator),
        entropy_function(entropy_function),
        gain_threshold(gain_threshold),
        random_engine(std::make_shared<std::mt19937>(random_seed)),
        annotation_step(annotation_step),
        seed_dist(0U, std::numeric_limits<unsigned int>::max()){
      // Check for usable regression data type
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");
      if (n_thresholds == 0) {
        throw Fertilized_Exception("The number of thresholds must be >0!");
      }
      if (gain_threshold < 0.f) {
        throw Fertilized_Exception("The minimum gain threshold must be >=0.f!");
      }
      if (annotation_step == 0) {
        throw Fertilized_Exception("The annotation step must be > 0!");
      }
      if (random_seed == 0) {
        throw Fertilized_Exception("Need a random seed >= 1!");
      }
    }

    /** Returns the gain threshold specified in the constructor. */
    float get_gain_threshold_for(const size_t &node_id) {
      return gain_threshold;
    }

    /** Initializes the random engines for parallel processing. */
    void prepare_for_optimizing(const size_t &node_id,
                                const int &num_threads) {
      FASSERT (num_threads > 0);
#ifndef _OPENMP
      if (num_threads > 1) {
        throw Fertilized_Exception("This executable has been built without "
          "OpenMP support. The number of threads must =1!");
      }
#endif
      while (thread_engines.size() < num_threads) {
        thread_engines.emplace_back(new std::mt19937());
      }
      main_seed = seed_dist(*random_engine);
    }

    /** Returns false! */
    bool supports_weights() const { return false; }

    /** Performs the threshold optimization. */
    optimization_tuple_t optimize(
              const node_id_t &node_id,
              const int &suggestion_index,
              const size_t &min_samples_at_leaf,
              const size_t &n_samples,
              const input_dtype *selected_data,
              const size_t &data_dimension,
              const input_dtype *annotations,
              const size_t &annontation_dimension,
              const float *weights,
              const feature_dtype *feature_values,
              bool *valid) {
       FASSERT(n_samples > 0);
       FASSERT(min_samples_at_leaf > 0);
       *valid = true;
       feature_dtype threshold = std::numeric_limits<feature_dtype>::lowest();
       auto best_result = optimization_tuple_t(
         std::make_pair(threshold, static_cast<feature_dtype>(0)),
         EThresholdSelection::less_only,
         0, static_cast<unsigned int>(n_samples), 0.f);

       // Handle this case quickly.
       // Also care for sufficiently large data set to perform line fitting
       size_t min_samples_for_line_fit = data_dimension + 2;
       size_t min_samples = 2 * min_samples_at_leaf;
       size_t min_samples_combined = (min_samples_for_line_fit < min_samples) ? (min_samples) : (min_samples_for_line_fit);
       if (min_samples_combined > n_samples ||
           n_samples <= 1) {
         // In this case, no valid threshold can be found.
         // Return the leftmost threshold directly.
         return best_result;
       }

       // Get a sorting permutation.
       std::vector<size_t> sort_perm = argsort(feature_values, n_samples);
       // No threshold fits "in between".
       if (feature_values[sort_perm[0]] == feature_values[*(sort_perm.end()-1)])
         return best_result;


       std::set<feature_dtype> selected_feat_vals;
       int thread_id = 0;
       #if defined(_OPENMP)
       thread_id = omp_get_thread_num();
       #endif
       FASSERT(thread_engines.size() > thread_id);
       unsigned int seed = main_seed + static_cast<unsigned int>(suggestion_index);
       if (seed == 0U) {
           seed += std::numeric_limits<unsigned int>::max() / 2;
       }

       thread_engines[thread_id] -> seed(seed);
       draw_feat_vals(feature_values[sort_perm[0]],
                      feature_values[*(sort_perm.end()-1)],
                      n_thresholds,
                      thread_engines[thread_id].get(),
                      &selected_feat_vals,
                      std::is_integral<feature_dtype>());

       // Create the sample matrix.
       // The sample-rows are sorted according to the ascending feature order.
       // It has +1 cols, due to "homogenous samples".
       // Only do this, if it is needed by the IRegressionCalculator
       // If not, avoid the copying
       size_t homogenous_data_dimension = data_dimension + 1;
       auto sample_mat = std::make_shared<Matrix_regression_t>(1, 1);
       if (reg_calc_template->needs_input_data()) {
         sample_mat = std::make_shared<Matrix_regression_t>(n_samples, homogenous_data_dimension);
         for (size_t col = 0; col < homogenous_data_dimension; col++) {
           for (size_t row = 0; row < n_samples; row++) {
             if (col == homogenous_data_dimension - 1) {
               (*sample_mat)(row,col) = static_cast<input_dtype>(1);
             } else {
               // Note: Given data is in column major format!
               (*sample_mat)(row,col) = selected_data[sort_perm[row] + (data_dimension * col)];
             }
           }
         }
       }

       // Create the annoation matrix
       auto annot_mat = std::make_shared<Matrix_regression_t>(n_samples, annontation_dimension);
       for (size_t row = 0; row < n_samples; row++) {
         for (size_t col = 0; col < annontation_dimension; col++) {
           (*annot_mat)(row,col) = annotations[(sort_perm[row] * annontation_dimension * annotation_step) + (col * annotation_step)];
         }
       }

       auto left_reg_calc = std::unique_ptr<IRegressionCalculator<input_dtype>>((*reg_calc_template).get_descendant_copy());
       auto right_reg_calc = std::unique_ptr<IRegressionCalculator<input_dtype>>(reg_calc_template->get_descendant_copy());
       left_reg_calc->initialize(sample_mat, annot_mat, std::make_pair(0,0));
       right_reg_calc->initialize(sample_mat, annot_mat, std::make_pair(0,static_cast<int>(n_samples)));

       // Initialize.
       // Calculate the entropy of the total sample set
       float total_entropy;
       bool numerical_instable = false;
       bool unique_solution_found = right_reg_calc->has_solution();
       if (unique_solution_found) {
         // Now calculate the combined entropy
         total_entropy = 0.f;
         Vector_regression_t prediction = Vector_regression_t(annontation_dimension);
         Matrix_regression_t pred_covar_mat = Matrix_regression_t(annontation_dimension, annontation_dimension);
         // faster entropy calculation, if the prediction (co)-variance does not depend on the actual input
         if (right_reg_calc->has_constant_prediction_covariance()) {
           // Calculate the determinant of the prediction covariance matrix (is diagonal!).
           right_reg_calc->get_constant_prediction_covariance(pred_covar_mat);
           input_dtype determinant = pred_covar_mat.diagonal().prod();
           if (determinant < 0.f)
             numerical_instable = true;
           else
             total_entropy = entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension))
                             * static_cast<float>(n_samples);
         } else {
           for (size_t i = 0; i < n_samples; i++) {
              // Calculate the determinant of the prediction covariance matrix (is diagonal!).
             right_reg_calc->predict((*sample_mat).row(i), prediction, pred_covar_mat);
             input_dtype determinant = pred_covar_mat.diagonal().prod();
               if (determinant < 0.f) {
                 numerical_instable = true;
                 break;
               }
             total_entropy += entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension));
           }
         }

       }
       if ((!unique_solution_found) || numerical_instable) {
         // If no line fitting can be performed on the total sample set,
         // it won't work on the subsets either
         *valid = false;
         //std::cout << "TO: no unique solution for complete set found." << std::endl;
         return best_result;
       }

       // Storage for the left regression prediction and covariance
       Vector_regression_t left_prediction = Vector_regression_t(annontation_dimension);
       Matrix_regression_t left_pred_covar_mat = Matrix_regression_t(annontation_dimension, annontation_dimension);
       // Storage for the right regression prediction and covariance
       Vector_regression_t right_prediction = Vector_regression_t(annontation_dimension);
       Matrix_regression_t right_pred_covar_mat = Matrix_regression_t(annontation_dimension, annontation_dimension);

       // Gain trackers.
       float current_gain;
       float current_left_entropy;
       float current_right_entropy;
       size_t best_split_index = 0;
       float best_gain = std::numeric_limits<float>::lowest();
       // Feature value trackers.
       feature_dtype last_val = std::numeric_limits<feature_dtype>::lowest();
       feature_dtype current_val;
       auto feat_val_it = selected_feat_vals.begin();
       bool usable_split;
       *valid = false;
       // Iterate over the possible thresholds.
       // During the iteration it is assumed that the split is "left" of the
       // current index.
       for (size_t index = 0; (index < n_samples + 1) && (feat_val_it != selected_feat_vals.end()); ++index) {
         usable_split = true;
         if (index < n_samples) {
           current_val = feature_values[ sort_perm[index] ];
         } else {
           current_val = std::numeric_limits<feature_dtype>::max();
         }
         // Check if gain calculation is necessary
         if ((current_val >= *feat_val_it) && (last_val < *feat_val_it)
              && (index >= min_samples_at_leaf) && ((n_samples - index) >= min_samples_at_leaf)) {
                    //Update the regression calculators
           left_reg_calc->change_index_interval(std::make_pair(0, static_cast<int>(std::min(index, n_samples))));
           right_reg_calc->change_index_interval(std::make_pair(static_cast<int>(std::min(index, n_samples)), static_cast<int>(n_samples)));
           // Get the left entropy
           if (! left_reg_calc->has_solution()) {
             usable_split = false;
             current_left_entropy = std::numeric_limits<float>::infinity();
           } else {
             // Now calculate the left entropy
             current_left_entropy = 0.f;
             // faster entropy calculation, if the prediction (co)-variance does not depend on the actual input
             if (left_reg_calc->has_constant_prediction_covariance()) {
               // Calculate the determinant of the prediction covariance matrix (is diagonal!).
               left_reg_calc->get_constant_prediction_covariance(left_pred_covar_mat);
               input_dtype determinant = left_pred_covar_mat.diagonal().prod();
               if (determinant < 0.f) {
                 usable_split = false;
                 current_left_entropy = std::numeric_limits<float>::infinity();
                 numerical_instable = true;
               } else {
                 current_left_entropy = entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension))
                                        * static_cast<float>(index);
               }
             } else {
               for (size_t i = 0; i < index; i++) {
                 // Calculate the determinant of the prediction covariance matrix (is diagonal!).
                 left_reg_calc->predict((*sample_mat).row(i), left_prediction, left_pred_covar_mat);
                 input_dtype determinant = left_pred_covar_mat.diagonal().prod();
                 if (determinant < 0.f) {
                   usable_split = false;
                   current_left_entropy = std::numeric_limits<float>::infinity();
                   break;
                 }
                 current_left_entropy += entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension));
               }
             }
           }

           // Get the right entropy
           if ((! usable_split) || (! right_reg_calc->has_solution())) {
             current_right_entropy = std::numeric_limits<float>::infinity();
             usable_split = false;
           } else {
             usable_split = usable_split & true;
             // Now calculate the right entropy
             current_right_entropy = 0.f;
             // faster entropy calculation, if the prediction (co)-variance does not depend on the actual input
             if (right_reg_calc->has_constant_prediction_covariance()) {
               // Calculate the determinant of the prediction covariance matrix (is diagonal!).
               right_reg_calc->get_constant_prediction_covariance(right_pred_covar_mat);
               input_dtype determinant = right_pred_covar_mat.diagonal().prod();
               if (determinant < 0.f) {
                 usable_split = false;
                 current_right_entropy = std::numeric_limits<float>::infinity();
                 numerical_instable = true;
               } else {
                 current_right_entropy = entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension))
                                         * static_cast<float>(n_samples - index);
               }
             } else {
               for (size_t i = index; i < n_samples; i++) {
                 // Calculate the determinant of the prediction covariance matrix (is diagonal!).
                 right_reg_calc->predict((*sample_mat).row(i), right_prediction, right_pred_covar_mat);
                 input_dtype determinant = right_pred_covar_mat.diagonal().prod();
                 if (determinant < 0.f) {
                   usable_split = false;
                   current_right_entropy = std::numeric_limits<float>::infinity();
                   break;
                 }
                 current_right_entropy += entropy_function->differential_normal(static_cast<float>(determinant), static_cast<const uint>(annontation_dimension));
               }
             }
           }


           if (usable_split) {
             current_gain = total_entropy - (current_left_entropy + current_right_entropy);
           } else {
             current_gain = std::numeric_limits<float>::lowest();
           }

           if (current_gain > best_gain) {
             *valid = true;
             best_gain = current_gain;
             best_split_index = index;
             threshold = *feat_val_it;
           }
         }

         // Update the feature value pointer.
          while (feat_val_it != selected_feat_vals.end() &&
                 *feat_val_it < current_val)
            feat_val_it++;

         // Update the trackers.
         if (last_val != current_val)
             last_val = current_val;


       }/*end for*/


       if (*valid) {
         // Create the best-result return value
         best_result = optimization_tuple_t(std::make_pair(threshold, static_cast<feature_dtype>(0)),
                                            EThresholdSelection::less_only, static_cast<unsigned int>(best_split_index),
                                            static_cast<unsigned int>(n_samples - best_split_index),
                                            best_gain);
       }

      // Check that the sum of elements going in either direction is the total.
       FASSERT(static_cast<size_t>(std::get<2>(best_result) + std::get<3>(best_result)) == n_samples);
       return best_result;
     };

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    bool operator==(const IThresholdOptimizer<input_dtype,
                    feature_dtype,
                    input_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<RegressionThresholdOptimizer<input_dtype,
                                                           feature_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_thresh = n_thresholds == rhs_c -> n_thresholds;
        bool eq_ef = *entropy_function == *(rhs_c -> entropy_function);
        bool eq_rc = *reg_calc_template == *(rhs_c -> reg_calc_template);
        bool eq_gaint = gain_threshold == rhs_c -> gain_threshold;
        bool eq_ann_step = annotation_step == rhs_c -> annotation_step;
        bool eq_re = *random_engine == *(rhs_c -> random_engine);
        bool eq_ms = main_seed == rhs_c -> main_seed;
        return eq_thresh && eq_ef && eq_rc && eq_gaint && eq_ann_step && 
               eq_re && eq_ms;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IThresholdOptimizer_t>(*this);
      ar & n_thresholds;
      ar & entropy_function;
      ar & reg_calc_template;
      ar & gain_threshold;
      ar & annotation_step;
      ar & random_engine;
      ar & main_seed;
    }
#endif

   protected:
   RegressionThresholdOptimizer() :
     seed_dist(0U, std::numeric_limits<unsigned int>::max()){}

   private:
    size_t n_thresholds;
    std::shared_ptr<IEntropyFunction<float>> entropy_function;
    std::shared_ptr<IRegressionCalculator<input_dtype>> reg_calc_template;
    size_t annotation_step;
    float gain_threshold;
    std::shared_ptr<std::mt19937> random_engine;
    std::vector<std::unique_ptr<std::mt19937>> thread_engines;
    unsigned int main_seed;
    std::uniform_int_distribution<unsigned int> seed_dist;

    DISALLOW_COPY_AND_ASSIGN(RegressionThresholdOptimizer);
  };
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_REGRESSIONTHRESHOLDOPTIMIZER_H_