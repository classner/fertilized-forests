/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_CLASSIFICATIONTHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_CLASSIFICATIONTHRESHOLDOPTIMIZER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <type_traits>
#include <vector>
#include <limits>
#include <random>

#include "../global.h"
#include "../types.h"
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
   * \brief Optimizes one threshold very efficiently.
   *
   * Supports only classification annotations (unsigned int) with annotation
   * values ranging in [0; n_classes - 1]. Searches the perfect threshold to
   * split the data.
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
  class ClassificationThresholdOptimizer
    : public IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> {
   public:
    typedef IThresholdOptimizer<input_dtype,
                  feature_dtype,
                                annotation_dtype> IThresholdOptimizer_t;
    using typename IThresholdOptimizer_t::data_prov_t;
    using typename IThresholdOptimizer_t::optimization_tuple_t;
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_list_t;

    /**
     * \brief Standard constructor.
     *
     * use_fast_search_approximation is an interesting option to speed up the
     * optimization process. In general, the elements are considered in sorted
     * feature order. If use_fast_search_approximation is set to true, the
     * gain is only calculated at positions, where the currently considered
     * element is from a different class than the last one AND if the
     * feature value changed.
     *
     * This is a true approximation (i.e. the optimal gain can be at a
     * position where the current element is from the same class than the
     * last), but this hardly ever occurs for the usual gain calculation
     * functions.
     *
     * A necessary, but not sufficient criterion for the approximation to
     * be equal to the optimal value is the following:
     * Assuming the (weighted) histogram values at position \f$k\f$ are
     * \f$k_{li}\f$ for the left hand-side histogram and \f$k_{ri}\f$ for the
     * right hand-side histogram, \f$i\in[0,n\_classes-1]\f$. Then the gain
     * function \f$g(.)\f$ must have the property
     * \f[\forall j\forall k_{li},k_{ri}: g(\{k_{li}\},\{k_{ri}\})<
     * g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}+1\},
     *   \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}-1\}) \vee
     * g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}-1\},
     *   \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}+1\})\f].
     *
     * This does not hold in general, but for the standard information gain
     * based measures, cases where it doesn't hold occur very rarely and even
     * if so, the found positions aren't a lot worse than the theoretical
     * optimum.
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
     * \param use_fast_search_approximation bool
     *     Whether to use the approximation described above or not.
     * \param n_classes size_t >1
     *     The number of classes. All annotations must be in [0, ..., n_classes[.
     * \param gain_calculator \ref IGainCalculator
     *     The gain calculator to estimate the gain at each split.
     * \param gain_threshold float>=0f
     *     The minimum gain that must be reached to continue splitting. Default: 1E-7f.
     * \param annotation_step size_t>0
     *     The memory step size for the annotation data. Default: 1.
     */
    ClassificationThresholdOptimizer(
      const bool &use_fast_search_approximation,
      const size_t &n_classes,
      const std::shared_ptr<IGainCalculator<float>> &gain_calculator,
      const float &gain_threshold=1E-7f,
      const size_t &annotation_step=1)
      : use_fast_search_approximation(use_fast_search_approximation),
        n_classes(n_classes),
        annotation_step(annotation_step),
        gain_threshold(gain_threshold),
        gain_calculator(gain_calculator) {
      if (n_classes < 2) {
        throw Fertilized_Exception("Need at least 2 classes!");
      }
      if (gain_threshold < 0.f) {
        throw Fertilized_Exception("The gain threshold must be >= 0f!");
      }
      if (annotation_step == 0) {
        throw Fertilized_Exception("The annotation step size must be > 0.");
      }
    }

    /** Returns the gain threshold specified in the constructor. */
    float get_gain_threshold_for(const size_t &node_id) {
      return gain_threshold;
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
        EThresholdSelection::less_only,
        0, static_cast<unsigned int>(n_samples), 0.f);
      // Handle this case quickly.
      if (2 * min_samples_at_leaf > n_samples ||
          n_samples <= 1) {
        // In this case, no valid threshold can be found.
        // Return the leftmost threshold directly.
        return best_result;
      }

      // Check.
      FASSERT(check_sample_classes_ok(annotations, n_samples, n_classes, annotation_step));

      // Get a sorting permutation.
      std::vector<size_t> sort_perm = argsort(feature_values, n_samples);
      // No threshold fits "in between".
      if (feature_values[sort_perm[0]] == feature_values[*(sort_perm.end()-1)])
        return best_result;

      // Create the weighted occurrence histograms.
      std::vector<float> right_histogram(n_classes, 0.f);
      for (size_t i = 0; i < n_samples; ++i) {
        right_histogram[static_cast<size_t>(annotations[i*annotation_step])] += weights[i];
      }
      std::vector<float> left_histogram(n_classes, 0);

      // Initialize.
      annotation_dtype last_element_type;
      annotation_dtype current_element_type;
      float current_weight;
      // Gain trackers.
      bool test_gain = true;
      float current_gain;
      float best_gain = std::numeric_limits<float>::lowest();
      // Feature value trackers.
      feature_dtype last_val = std::numeric_limits<feature_dtype>::lowest();
      feature_dtype current_val;
      *valid = false;
      // Iterate over the feature list.
      // During the iteration it is assumed that the split is "left" of the
      // current index.
      for (size_t index = 0; index < n_samples; ++index) {
        current_val = feature_values[ sort_perm[index] ];
        current_element_type = annotations[sort_perm[index]*annotation_step];
        current_weight = weights[sort_perm[index]];
        // Check if a relevant change took place.
        if (use_fast_search_approximation) {
          if (index != 0 &&
                (current_val == last_val ||
                 current_element_type == last_element_type)) {
            test_gain = false;
          } else {
            test_gain = true;
          }
        } else {
          test_gain = (current_val != last_val);
        }
        // Calculate the gain if necessary.
        // (Remember that the index corresponds to the number of elements left
        //  of the split! :)
        if (test_gain && index >= min_samples_at_leaf
                      && n_samples - index >= min_samples_at_leaf) {
          current_gain = gain_calculator -> approx(left_histogram,
                                                   right_histogram);
          if (current_gain > best_gain) {
            *valid = true;
            best_gain = current_gain;
            // Take into account rounding issues if necessary.
            if (std::is_floating_point<feature_dtype>::value ||
                current_val != last_val + 1) {
              threshold = (last_val + current_val) /
                              static_cast<feature_dtype>(2);
              // If both values are just eps apart, there can't be a value
              // in between. This would lead to erroneous sample counts at
              // the following nodes. Correct it, if it happens.
              if (threshold == last_val) {
                // This is completely ok, since a 'less-than' comparison
                // is used.
                threshold = current_val;
              }
            } else {
              threshold = current_val;
            }
            best_result = optimization_tuple_t(
              std::make_pair(threshold, static_cast<feature_dtype>(0)),
              EThresholdSelection::less_only, static_cast<unsigned int>(index),
              static_cast<unsigned int>(n_samples - index),
              (*gain_calculator)(left_histogram, right_histogram));
          }
        }

        // Update the histograms.
        left_histogram[ static_cast<size_t>(current_element_type) ] += current_weight;
        FASSERT(right_histogram[ static_cast<size_t>(current_element_type) ] >= current_weight);
        right_histogram[ static_cast<size_t>(current_element_type) ] -= current_weight;

        // Update the trackers.
        last_val = current_val;
        last_element_type = current_element_type;
      }
      // Check that the sum of elements going in either direction is the total.
      FASSERT(
       static_cast<size_t>(std::get<2>(best_result) + std::get<3>(best_result))
       == n_samples);
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
      const auto *rhs_c = dynamic_cast<ClassificationThresholdOptimizer<input_dtype,
                                                           feature_dtype,
                                                           annotation_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_approx = use_fast_search_approximation == rhs_c -> use_fast_search_approximation;
        bool eq_cls = n_classes == rhs_c -> n_classes;
        bool eq_gainc = *gain_calculator == *(rhs_c -> gain_calculator);
        bool eq_gaint = gain_threshold == rhs_c -> gain_threshold;
        bool eq_ann_step = annotation_step == rhs_c -> annotation_step;
        return eq_approx && eq_cls && eq_gainc && eq_gaint && eq_ann_step;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IThresholdOptimizer_t>(*this);
      ar & use_fast_search_approximation;
      ar & n_classes;
      ar & gain_calculator;
      ar & gain_threshold;
      ar & annotation_step;
    }
#endif
   protected:
     // cppcheck-suppress uninitVar
     ClassificationThresholdOptimizer() {}

   private:
    bool use_fast_search_approximation;
    size_t n_classes;
    size_t annotation_step;
    float gain_threshold;
    std::shared_ptr<IGainCalculator<float>> gain_calculator;

    DISALLOW_COPY_AND_ASSIGN(ClassificationThresholdOptimizer);
  };
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_CLASSIFICATIONTHRESHOLDOPTIMIZER_H_