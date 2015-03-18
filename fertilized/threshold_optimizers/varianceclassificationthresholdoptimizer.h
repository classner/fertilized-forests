/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_H_

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
#include "../default_values.h"
#include "../gains/igaincalculator.h"
#include "../impurities/ientropyfunction.h"
#include "../util/checks.h"
#include "../util/sampling.h"
#include "../util/argsort.h"
#include "./ithresholdoptimizer.h"
#include "./feature_value_selection.h"

namespace fertilized {
  // Forward declaration.
  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ThresholdClassifier;

  /**
   * \brief Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.
   *
   * The annotations are assumed to be a class label followed by its offset
   * values. Since all these values must be of the same datatype, the only supported type
   * is (signed) int in this case (to allow for negative offsets). The class labels
   * must still be in [0; n_classes - 1].
   *
   * This threshold optimizer draws n_thresholds random values between
   * the minimum and maximum observed feature value and returns the best
   * one.
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
   * - int; int; uint
   * - int; float; uint
   * - float; int; uint
   * - uint8_t; int; uint
   * - uint8_t; uint8_t; uint
   * - uint8_t; float; uint
   * - uint8_t; int16_t; uint
   * - float; float; uint
   * - double; double; uint
   * - uint8_t; int16_t; int16_t
   * .
   *
   * -----
   */
  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class VarianceClassificationThresholdOptimizer
    : public IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>{
   public:
    typedef IThresholdOptimizer<input_dtype, feature_dtype,
                                annotation_dtype> IThresholdOptimizer_t;
    using typename IThresholdOptimizer_t::data_prov_t;
    using typename IThresholdOptimizer_t::optimization_tuple_t;
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_list_t;

    /**
     * Standard constructor.
     *
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
     *   The number of thresholds to evaluate per split.
     * \param n_classes size_t>1
     *   The number of classes in the data. Currently only 2 are supported! Default: 2.
     * \param offset_dim size_t>0
     *   The dimensionality of the offset annotation (usually 2). Default: 2.
     * \param gain_threshold float
     *   The minimum gain to accept a split as valid. Default: 0.f.
     * \param random_seed unsigned int>0
     *   The seed for the RNG. Must be greater 0. Default: 1.
     */
    VarianceClassificationThresholdOptimizer(
      const size_t &n_thresholds,
      const size_t &n_classes = 2,
      const size_t &offset_dim = 2,
      const float &gain_threshold=0.f,
      const unsigned int &random_seed=1)
      : n_thresholds(n_thresholds),
        n_classes(n_classes),
        gain_threshold(gain_threshold),
        offset_dim(offset_dim),
        random_engine(std::make_shared<std::mt19937>(random_seed)),
        thread_engines(),
        main_seed(0),
        entropy_calculator(_NULL_ENTROPY_PTR),
        seed_dist(0U, std::numeric_limits<unsigned int>::max()) {
      if (n_thresholds == 0) {
        throw Fertilized_Exception("The number of thresholds must be >0!");
      }
      if (n_classes <= 1) {
        throw Fertilized_Exception("The number of classes must be > 1!");
      }
      if (offset_dim == 0) {
        throw Fertilized_Exception("The number of offset dimensions must be > 0!");
      }
      if (random_seed == 0) {
        throw Fertilized_Exception("Need a random seed >= 1!");
      }
      if (n_classes != 2) {
        throw Fertilized_Exception("The VarianceClassificationThresholdOptimizer "
          "currently only supports two classes!");
      }
    }

    /**
     * Constructor with optional entropy function specification.
     *
     * \param n_thresholds size_t
     *   The number of thresholds to evaluate per split.
     * \param n_classes size_t
     *   The number of classes in the data. Currently only 2 are supported! Default: 2.
     * \param offset_dim size_t
     *   The dimensionality of the offset annotation (usually 2). Default: 2.
     * \param ent_calc shared(IEntropyFunction<float>) or nullptr
     *   If not nullptr, a normal distribution of offsets is assumed and the
     *   entropy is measured using the specified differential entropy.
     *   Default: nullptr.
     * \param gain_threshold float
     *   The minimum gain to accept a split as valid. Default: 0.f.
     * \param random_seed unsigned int>0
     *   The seed for the RNG. Must be greater 0. Default: 1.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * .
     * Exported name: VarianceClassificationThresholdOptimizerWEntropy
     *
     * -----
     */
    VarianceClassificationThresholdOptimizer(
      const size_t &n_thresholds,
      const size_t &n_classes,
      const size_t &offset_dim,
      const std::shared_ptr<IEntropyFunction<float>> &ent_calc,
      const float &gain_threshold=1.f,
      const unsigned int &random_seed=1)
      : n_thresholds(n_thresholds),
        n_classes(n_classes),
        gain_threshold(gain_threshold),
        offset_dim(offset_dim),
        random_engine(std::make_shared<std::mt19937>(random_seed)),
        entropy_calculator(ent_calc),
        thread_engines(),
        main_seed(0),
        seed_dist(0U, std::numeric_limits<unsigned int>::max()) {
      if (random_seed == 0) {
        throw Fertilized_Exception("Need a random seed >= 1!");
      }
      if (n_classes != 2) {
        throw Fertilized_Exception("The VarianceClassificationThresholdOptimizer "
          "currently only supports two classes!");
      }
    }

    /**
     * Initializes RNGs for multithreaded use.
     */
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

    /**
     * Gets the gain threshold for a specific node id. Returns always the
     * one specified in the constructor.
     */
    float get_gain_threshold_for(const size_t &node_id) {
      return gain_threshold;
    }

    /** Return true. */
    bool supports_weights() const { return true; }

    /**
     * \brief Returns true.
     */
    bool needs_negatives(const size_t &node_id) {
      //TODO(Christoph): If offloading is implemented and copy-speed is an
      // issue, time coud be saved here. However, setting this to false
      // requires quite some changes: the classifier must handle missing
      // samples in the statistics properly (which it DOES NOT right now!)
      // The speedup shortcuts while walking over the samples ignoring splits
      // that contain too few features for leaf nodes must be removed.
      // Otherwise, the interface should change and the threshold optimizers
      // should directly return the lists of samples for left and right to
      // save time.
      return true;
    }

    /**
     *\brief See \ref IThresholdOptimizer.
     *
     * Additionally, this method has the following constraints:
     *   - The sample weights must be positive.
     *   - The sum of weights of all selected samples must be < FLOAT_MAX
     *   - The annotations must be in the interval [0, n_classes[.
     *   - Any constraints that the selected gain calculator enforces.
     */
    optimization_tuple_t optimize(
              const node_id_t &node_id,
              const int &suggestion_index,
              const size_t &min_samples_at_leaf,
              const size_t &n_samples,
              const input_dtype *selected_data,
              const size_t &data_dimension,
              const annotation_dtype *annotations,
              const size_t &annontation_dimension,
              const float *weights,
              const feature_dtype *feature_values,
              bool *valid) {
      // Return value.
      *valid = true;
      feature_dtype threshold = std::numeric_limits<feature_dtype>::lowest();
      auto best_result = optimization_tuple_t(
        std::make_pair(threshold, static_cast<feature_dtype>(0)),
        EThresholdSelection::less_only, 0, static_cast<unsigned int>(n_samples), 0.f);
      // Handle this case quickly.
      if (2 * min_samples_at_leaf > n_samples ||
          n_samples <= 2) {
        // In this case, no valid threshold can be found.
        // Return the leftmost threshold directly.
        return best_result;
      }
      // At least two elements are required to perform this operation.
      FASSERT(n_samples > 2);
      // Get a sorting permutation.
      std::vector<size_t> sort_perm = argsort(feature_values, n_samples);
      // No threshold fits "in between".
      if (feature_values[sort_perm[0]] == feature_values[*(sort_perm.end()-1)]) {
        *valid = false;
        return best_result;
      }

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

      // Checks.
      FASSERT(check_sample_classes_ok(annotations, n_samples, n_classes, 3));

      // Initialize.
      float current_weight;
      // Means and variances.
      std::vector<float> means_right(offset_dim, 0.f);
      std::vector<float> vars_right(offset_dim, 0.f);
      std::vector<float> means_left(means_right), vars_left(vars_right);
      float weight_sum_left = 0.f;
      float weight_sum_right = 0.f;
      float mu_old;
      const annotation_dtype *xn = annotations;
      float xnv;
      for (size_t i = 0; i < n_samples; ++i) {
        // Ignore the class annotation if its from the negative class (class
        // label zero). Otherwise just jump over the class label.
        if (*xn == 0) {
          xn += 1 + offset_dim;
          continue;
        } else {
          xn++;
        }
        weight_sum_right += weights[i];
        for (size_t j = 0; j < offset_dim; ++j, ++xn) {
          mu_old = means_right[j];
          xnv = static_cast<float>(*xn);
          means_right[j] += weights[i] / weight_sum_right * (xnv - mu_old);
          vars_right[j] += weights[i]*(xnv - mu_old)*(xnv - means_right[j]);
        }
      }
      float weight_sum = weight_sum_right;
      // Calculate the current 'entropy' of the data.
      Eigen::Matrix<float,
              Eigen::Dynamic,
              Eigen::Dynamic,
              Eigen::RowMajor> covar_mat(offset_dim, offset_dim);
      covar_mat.setZero();
      float current_entropy = 0.f;
      if (entropy_calculator.get() == nullptr) {
        for (size_t i = 0; i < offset_dim; ++i)
          current_entropy += vars_right[i];
        current_entropy /= weight_sum;
      } else {
        for (size_t i = 0; i < offset_dim; ++i) {
          covar_mat(i, i) = vars_right[i] / weight_sum_right;
        }
        current_entropy = entropy_calculator -> differential_normal(covar_mat);
      }
      // Feature value trackers.
      feature_dtype last_val = std::numeric_limits<feature_dtype>::lowest();
      feature_dtype current_val;
      auto feat_val_it = selected_feat_vals.begin();
      // Gain trackers.
      float current_gain;
      float best_gain = std::numeric_limits<float>::lowest();
      last_val = std::numeric_limits<feature_dtype>::lowest();
      float eleft, eright;
      for (size_t index = 0;
           index < n_samples &&
           feat_val_it != selected_feat_vals.end(); ++index) {
        current_val = feature_values[ sort_perm[index] ];
        current_weight = weights[ sort_perm[ index ]];
        // No element can be 'moved' any more to the left. Otherwise the
        // 'right' elements would be empty: variance and mean are ill defined
        // for that case.
        if (current_weight == weight_sum_right)
          break;
        // Check if a relevant change took place.
        if (current_val >= *feat_val_it && last_val < *feat_val_it &&
            weight_sum_left > 0.f && weight_sum_right > 0.f
              && index >= min_samples_at_leaf
              && n_samples - index >= min_samples_at_leaf) {
          eleft = 0.f;
          eright = 0.f;
          bool is_invalid = false;
          if (entropy_calculator.get() == nullptr) {
            for (size_t dim_index = 0; dim_index < offset_dim; ++dim_index)
              eleft += vars_left[dim_index]; // Add / weight_sum_left; for variance.
            for (size_t dim_index = 0; dim_index < offset_dim; ++dim_index)
              eright += vars_right[dim_index]; // Add / weight_sum_left; for variance.
            // Approximate it.
            // This is already the weighted sum, since the vars_left and
            // vars_right have not been normalized with the set size when
            // adding up. Normalize by the total number of instances at the end.
            current_gain = - eleft - eright;
          } else {
            for (size_t i = 0; i < offset_dim; ++i)
              covar_mat(i, i) = vars_left[i] / weight_sum_left;
            eleft = entropy_calculator -> differential_normal(covar_mat);
            if (eleft == -std::numeric_limits<float>::infinity()) {
              // This is the case if the determinant of the matrix has been
              // zero and an indicator for an unusable entropy value.
              is_invalid = true;
              goto gain_comparison;
            }
            for (size_t i = 0; i < offset_dim; ++i)
              covar_mat(i, i) = vars_right[i] / weight_sum_right;
            eright = entropy_calculator -> differential_normal(covar_mat);
            if (eright == -std::numeric_limits<float>::infinity()) {
              is_invalid = true;
              goto gain_comparison;
            }
            current_gain = -weight_sum_left*eleft -weight_sum_right*eright;
          }
          gain_comparison:
          if (! is_invalid &&
              current_gain > best_gain) {
            best_gain = current_gain;
            best_result = optimization_tuple_t(
              std::make_pair(*feat_val_it, static_cast<feature_dtype>(0)),
              EThresholdSelection::less_only,
              static_cast<unsigned int>(index),
              static_cast<unsigned int>(n_samples - index),
              current_entropy + current_gain / weight_sum);  // Real gain.
          }
        }
        annotation_dtype current_annot = annotations[ sort_perm[ index ]  * (1+offset_dim)];
        if (current_annot != 0) {
          // Update the histograms.
          weight_sum_left += current_weight;
          FASSERT(weight_sum_right >= current_weight);
          float wquot = weight_sum_right / current_weight;
          weight_sum_right -= current_weight;
          float current_elem;
          for (size_t dim_index = 0; dim_index < offset_dim; ++dim_index) {
            mu_old = means_left[dim_index];
            current_elem = static_cast<float>(annotations[sort_perm[index] *(1+offset_dim) + dim_index+1]);
            means_left[dim_index] += current_weight / weight_sum_left * (current_elem - means_left[dim_index]);
            vars_left[dim_index] += current_weight*(current_elem - mu_old)*(current_elem - means_left[dim_index]);
            mu_old = means_right[dim_index];
            means_right[dim_index] = (means_right[dim_index] * wquot - current_elem) / (wquot - 1.f);
            vars_right[dim_index] -= current_weight*(current_elem - means_right[dim_index])*(current_elem - mu_old);
            // It might happen that due to numerical issues the estimated
            // variance value becomes <0 for the last 2 or three elements.
            // In this case, set the variance in this dimension to zero.
            // Since the variance is only approximated by a diagonal covariance
            // matrix, the determinant of this matrix will become zero in that
            // case. The entropy functions can detect and deal with that and
            // will return -infinite entropy.
            vars_right[dim_index] = std::max(vars_right[dim_index], 0.f);
          }
        }

        // Update the feature value pointer.
        while (feat_val_it != selected_feat_vals.end() &&
               *feat_val_it < current_val)
          feat_val_it++;

        // Update the trackers.
        if (last_val != current_val)
          last_val = current_val;
      }
      if (std::get<2>(best_result) >= min_samples_at_leaf &&
          std::get<3>(best_result) >= min_samples_at_leaf)
      { *valid = true; } else { *valid = false; }
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
                    annotation_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<VarianceClassificationThresholdOptimizer<input_dtype,
                                                           feature_dtype,
                                                           annotation_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_thresh = n_thresholds == rhs_c -> n_thresholds;
        bool eq_cls = n_classes == rhs_c -> n_classes;
        bool eq_ofs = offset_dim == rhs_c -> offset_dim;
        bool eq_re = *random_engine == *(rhs_c -> random_engine);
        bool eq_gaint = gain_threshold == rhs_c -> gain_threshold;
        bool eq_ms = main_seed == rhs_c -> main_seed;
        bool eq_ec = *entropy_calculator == *(rhs_c -> entropy_calculator);
        return eq_thresh && eq_cls && eq_ofs && eq_re && eq_gaint &&
               eq_ms && eq_ec;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IThresholdOptimizer_t>(*this);
      ar & n_thresholds;
      ar & n_classes;
      ar & offset_dim;
      ar & random_engine;
      ar & gain_threshold;
      ar & main_seed;
      ar & entropy_calculator;
    }
#endif
   protected:
     // cppcheck-suppress uninitVar
     VarianceClassificationThresholdOptimizer() :
        seed_dist(0U, std::numeric_limits<unsigned int>::max()) {}

   private:
    size_t n_thresholds;
    size_t n_classes;
    float gain_threshold;
    size_t offset_dim;
    std::shared_ptr<std::mt19937> random_engine;
    std::shared_ptr<IEntropyFunction<float>> entropy_calculator;
    std::vector<std::unique_ptr<std::mt19937>> thread_engines;
    unsigned int main_seed;
    std::uniform_int_distribution<unsigned int> seed_dist;

    DISALLOW_COPY_AND_ASSIGN(VarianceClassificationThresholdOptimizer);
  };


}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_H_