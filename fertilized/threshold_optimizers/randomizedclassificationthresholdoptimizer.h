/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_H_

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
#include "../data_providers/idataprovider.h"
#include "../gains/igaincalculator.h"
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
   * \brief Optimizes a threshold by selecting the best of few random values.
   *
   * Supports only classification annotations (unsigned int) with annotation
   * values in [0, ..., n_classes[.
   * The threshold optimizer draws n_thresholds random values between
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
  class RandomizedClassificationThresholdOptimizer
    : public IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> {
   public:
    typedef IThresholdOptimizer<input_dtype, feature_dtype,
                                annotation_dtype> IThresholdOptimizer_t;
    using typename IThresholdOptimizer_t::data_prov_t;
    using typename IThresholdOptimizer_t::optimization_tuple_t;
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_list_t;

    /**
     * \brief Standard constructor.
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
     *     The number of thresholds to test per node.
     * \param n_classes size_t>1
     *     The number of classes. All annotations must be within
     *     [0, ..., n_classes[.
     * \param gain_calculator \ref IGainCalculator
     *     The gain calculator to use.
     * \param gain_threshold float >= 0f
     *     The minimum gain that must be reached to continue splitting. Optional.
     * \param annotation_step size_t>0
     *     The memory step from one annotation value to the next. Optional.
     * \param random_seed uint>0
     *     The random seed to initialize the RNG. Optional.
     */
    RandomizedClassificationThresholdOptimizer(
      const size_t &n_thresholds,
      const size_t &n_classes,
      const std::shared_ptr<IGainCalculator<float>> &gain_calculator,
      const float &gain_threshold=1E-7f,
      const size_t &annotation_step=1,
      const unsigned int &random_seed = 1)
      : n_thresholds(n_thresholds),
        n_classes(n_classes),
        annotation_step(annotation_step),
        gain_threshold(gain_threshold),
        gain_calculator(gain_calculator),
        random_engine(std::make_shared<std::mt19937>(random_seed)),
        main_seed(0),
        seed_dist(0U, std::numeric_limits<unsigned int>::max()) {
      if (n_thresholds == 0) {
        throw Fertilized_Exception("The RandomizedClassificationThresholdOptimizer "
          "needs an n_thresholds specification > 0!");
      }
      if (n_classes < 2) {
        throw Fertilized_Exception("The number of classes must be > 1!");
      }
      if (gain_threshold < 0.f) {
        throw Fertilized_Exception("The gain threshold must be >= 0f!");
      }
      if (random_seed == 0) {
        throw Fertilized_Exception("The RandomizedClassificationThresholdOptimizer "
          "needs a random seed >= 1!");
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

    /** Returns true. */
    bool supports_weights() const { return true; }

    /**
     * \brief Check for early stopping.
     *
     * If true is returned, a leaf is created without searching for a threshold.
     */
    virtual bool check_for_early_stop(const annotation_dtype * annotations,
                                      const size_t &annot_dim,
                                      const size_t &n_samples,
                                      const node_id_t &node_id) {
      if (annot_dim != 1) {
        throw Fertilized_Exception("Early stopping only possible for 1D annotations!");
      }
      annotation_dtype first_class = annotations[0];
      for (size_t i = 1; i < n_samples; ++i) {
        if (annotations[i * annot_dim] != first_class) {
          return false;
        }
      }
      return true;
    };

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
          n_samples <= 1) {
        // In this case, no valid threshold can be found.
        // Return the leftmost threshold directly.
        return best_result;
      }
      // At least two elements are required to perform this operation.
      FASSERT(n_samples >= 2);
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
      // Used knuth_b here first, but had to work around a bug in MSVC11
      // (MSVS2012) (see
      // http://connect.microsoft.com/VisualStudio/feedback/details/829637/implementation-bug-in-c-11-features-random-engine),
      // so switched to mersenne twister.
      thread_engines[thread_id] -> seed(seed);
      draw_feat_vals(feature_values[sort_perm[0]],
                     feature_values[*(sort_perm.end()-1)],
                     n_thresholds,
                     thread_engines[thread_id].get(),
                     &selected_feat_vals,
                     std::is_integral<feature_dtype>());

      // Checks.
      FASSERT(check_sample_classes_ok(annotations, n_samples, n_classes, annotation_step));

      // Initialize.
      annotation_dtype current_element_type;
      float current_weight;
      // Histograms.
      std::vector<float> right_histogram(n_classes, 0.f);
      for (size_t i = 0; i < n_samples; ++i) {
        right_histogram[static_cast<size_t>(annotations[i*annotation_step])] += weights[i];
      }
      std::vector<float> left_histogram(n_classes, 0.f);
      // Feature value trackers.
      feature_dtype last_val = std::numeric_limits<feature_dtype>::lowest();
      feature_dtype current_val;
      auto feat_val_it = selected_feat_vals.begin();
      // Gain trackers.
      float current_gain;
      float best_gain = std::numeric_limits<float>::lowest();
      last_val = std::numeric_limits<feature_dtype>::lowest();
      /// Code to check for discrepancy between T_2 and N_2 and with a
      /// possible solution.
      // TODO(Christoph): Cleanup.
      //feature_dtype center = (feature_values[sort_perm[0]] +
      //                        feature_values[*(sort_perm.end()-1)]) /
      //                        static_cast<feature_dtype>(2);
      //feature_dtype best_cent_dist = std::numeric_limits<feature_dtype>::max();
      //auto refent = std::make_shared<InducedPEntropy<float>>(2.f);
      //auto refgain = std::make_shared<EntropyGain<float>>(refent);
      //float refgval; float refgbest = best_gain;
      //std::vector<float> best_hist_l;
      //std::vector<float> best_hist_r;
      ///
      for (size_t index = 0;
           index < n_samples &&
           feat_val_it != selected_feat_vals.end(); ++index) {
        current_val = feature_values[ sort_perm[index] ];
        current_element_type = annotations[ sort_perm[index] * annotation_step ];
        current_weight = weights[ sort_perm[ index ]];
        // Check if a relevant change took place.
        if (current_val >= *feat_val_it && last_val < *feat_val_it
              && index >= min_samples_at_leaf
              && n_samples - index >= min_samples_at_leaf) {
          current_gain = gain_calculator -> approx(left_histogram,
                                                   right_histogram);
          ///
          //refgval = refgain -> approx(left_histogram, right_histogram);
          //if (current_gain > best_gain && ! (refgval > refgbest)) {
          //  current_gain = gain_calculator -> approx(left_histogram,
          //                                         right_histogram);
          //  refgval = refgain -> approx(left_histogram, right_histogram);
          //}
          ///
          if (current_gain > best_gain/* ||
              fabs(current_gain - best_gain) < 0.0000001f &&
              abs(current_val - center) < best_cent_dist*/) {
            ///
            //refgbest = refgval;
            //best_hist_l = left_histogram;
            //best_hist_r = right_histogram;
            //best_cent_dist = abs(current_val - center);
            //if (current_gain > best_gain)
              ///
              best_gain = current_gain;
            best_result = optimization_tuple_t(
              std::make_pair(*feat_val_it, static_cast<feature_dtype>(0)),
              EThresholdSelection::less_only,
              static_cast<unsigned int>(index),
              static_cast<unsigned int>(
                n_samples - index),
              (*gain_calculator)(left_histogram, right_histogram));
          }
        }

        // Update the histograms.
        left_histogram[ static_cast<size_t>(current_element_type) ] += current_weight;
        FASSERT(right_histogram[ static_cast<size_t>(current_element_type) ] >= current_weight);
        right_histogram[ static_cast<size_t>(current_element_type) ] -= current_weight;

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
      const auto *rhs_c = dynamic_cast<RandomizedClassificationThresholdOptimizer<input_dtype,
                                                           feature_dtype,
                                                           annotation_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_thresh = n_thresholds == rhs_c -> n_thresholds;
        bool eq_cls = n_classes == rhs_c -> n_classes;
        bool eq_gainc = *gain_calculator == *(rhs_c -> gain_calculator);
        bool eq_re = *random_engine == *(rhs_c -> random_engine);
        bool eq_gaint = gain_threshold == rhs_c -> gain_threshold;
        bool eq_ann_step = annotation_step == rhs_c -> annotation_step;
        bool eq_main_seed = main_seed == rhs_c -> main_seed;
        return eq_thresh && eq_cls && eq_gainc && eq_re && eq_gaint &&
               eq_ann_step && eq_main_seed;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IThresholdOptimizer_t>(*this);
      ar & n_thresholds;
      ar & n_classes;
      ar & gain_calculator;
      ar & random_engine;
      ar & gain_threshold;
      ar & annotation_step;
      ar & main_seed;
    }
#endif
   protected:
     // cppcheck-suppress uninitVar
     RandomizedClassificationThresholdOptimizer() :
        seed_dist(0U, std::numeric_limits<unsigned int>::max()) {}

   private:
    size_t n_thresholds;
    size_t n_classes;
    size_t annotation_step;
    float gain_threshold;
    std::shared_ptr<IGainCalculator<float>> gain_calculator;
    std::shared_ptr<std::mt19937> random_engine;
    std::vector<std::unique_ptr<std::mt19937>> thread_engines;
    unsigned int main_seed;
    std::uniform_int_distribution<unsigned int> seed_dist;

    DISALLOW_COPY_AND_ASSIGN(RandomizedClassificationThresholdOptimizer);
  };
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_H_