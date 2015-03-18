/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DECIDERS_THRESHOLDDECIDER_H_
#define FERTILIZED_DECIDERS_THRESHOLDDECIDER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <unordered_map>
#include <mutex>
#include <utility>
#include <vector>
#include <limits>
#include <typeinfo>

#include "../global.h"
#include "../types.h"
#include "../features/isurfacecalculator.h"
#include "../features/directpatchdifferencesurfcalculator.h"
#include "../features/differencesurfacecalculator.h"
#include "../features/ifeatureselectionprovider.h"
#include "../threshold_optimizers/ithresholdoptimizer.h"
#include "../threshold_optimizers/alternatingthresholdoptimizer.h"
#include "./idecider.h"
#include "../ndarray.h"

namespace fertilized {
  /**
   * \brief A classifier manager for weak classifiers with a filter function,
   * a feature calculation function and a thresholding.
   *
   * The classifier design is heavily inspired by "Decision Forests for
   * Classification, Regression, Density Estimation, Manifold Learning and
   * Semi-Supervised Learning" (Criminisi, Shotton and Konukoglu, 2011).
   * With their definition, node classifier parameters \f$\theta\f$ can
   * be split into three parts:
   *  - \f$\phi\f$: a filter function that selects relevant features,
   *  - \f$\psi\f$: parameters of a function that combines the feature values
   *                to a single scalar,
   *  - \f$\tau\f$: thresholding parameters for the calculated scalar.
   *
   * With this model, a decision can be made at each node based on whether the
   * calculated scalar lies withing the thresholding bounds.
   *
   * \ingroup fertilizeddecidersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int; int; uint
   * - uint8_t; uint8_t; uint
   * - uint8_t; int16_t; uint
   * - float; float; uint
   * - double; double; uint
   * - uint8_t; int16_t; int16_t
   * - float; float; float
   * - double; double; double
   * .
   *
   * -----
   */
  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ThresholdDecider
    : public IDecider<input_dtype, feature_dtype, annotation_dtype> {
   public:
    // Convenience typedefs
    typedef IDecider<input_dtype, feature_dtype,
                     annotation_dtype> iclassifier_manager_t;
    using typename iclassifier_manager_t::dprov_t;
    typedef ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>
                   feat_calc_t;
    typedef IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>
      thresh_opt_t;
    typedef typename thresh_opt_t::optimization_tuple_t optimization_tuple_t;
    /**
     * \brief A tuple to store all parameters for one decision node.
     *
     * The parameters are stored as follows:
     *  -# A vector with the data dimensions used for feature calculation.
     *  -# A pointer to a feature calculation parameter set.
     *  -# Which thresholds should be used.
     *  -# A pair of < and > threshold values.
     */
    typedef std::tuple<std::vector<size_t>, FeatCalcParamSet,
      EThresholdSelection, std::pair<feature_dtype, feature_dtype>>
      decision_tuple_t;

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
     * \param selection_provider shared(IFeatureSelectionProvider)
     *   It suggests tuples
     *   for the optimization of \f$\phi\f$. It must be compatible
     *   to the feature calculator.
     * \param feature_calculator shared(ISurfaceCalculator)
     *   The feature calculation function. Its
     *   parameters are \f$\psi\f$, and it combines the data
     *   dimensions to a single scalar feature.
     * \param threshold_optimizer shared(IThresholdOptimizer)
     *   Optimizes \f$\tau\f$.
     * \param n_valid_features_to_use size_t
     *   The threshold optimizer may hint that
     *   a selected feature may be completely inappropriate for the
     *   currently searched split. If the feature selection provider
     *   does provide  sufficiently many features, the classifier may
     *   use the next one and "not count" the inappropriate one.
     *   This is the maximum number of "valid" features that are
     *   used per split. If 0, ignore the flag returned by the
     *   optimizer and always use all suggested feature combinations
     *   provided by the feature selection provider. Default: 0.
     * \param num_threads size_t>0
     *   The number of threads to use for threshold optimization.
     *   Independent of the number of threads, the result is
     *   guaranteed to be the same. Default: 1.
     * \param use_hough_heuristic bool
     *   Whether or not to use a heuristic for hough
     *   forests introduced by Juergen Gall
     *   (http://www.vision.ee.ethz.ch/~gallju/projects/houghforest/houghforest.html)
     *   Can be used only with an \ref AlternatingThresholdOptimizer.
     *   If used, the AlternatingThresholdOptimizer will guaranteed
     *   use opt2 if the ratio of negative samples is < \ref hough_heuristic_ratio or
     *   depth >= \ref hough_heuristic_maxd. opt2 must be a
     *   \ref VarianceClassificationThresholdOptimizer (check this
     *   manually!). Default: false.
     * \param hough_heuristic_ratio float>=0.f
     *   Default: 0.05f.
     * \param hough_heuristic_maxd uint
     *   Default: 0.
     * \param allow_early_stopping bool
     *   Allows the threshold optimizer to stop training if, e.g., all samples
     *   are of the same class in a classification setting. This is currently
     *   only supported by the classification threshold optimizers for 1D
     *   class annotations. Default: false.
     */
    ThresholdDecider(
      const std::shared_ptr<IFeatureSelectionProvider> &selection_provider,
      const std::shared_ptr<feat_calc_t> &feature_calculator,
      const std::shared_ptr<thresh_opt_t> &threshold_optimizer,
      const size_t &n_valid_features_to_use = 0,
      const int &num_threads = 1,
      const bool &use_hough_heuristic = false,
      const float &hough_heuristic_ratio = 0.05f,
      const uint &hough_heuristic_maxd = 0,
      const bool &allow_early_stopping = false)
    : selection_provider(selection_provider),
      feature_calculator(feature_calculator),
      threshold_optimizer(threshold_optimizer),
      n_valids_to_use(n_valid_features_to_use),
      decision_param_map(std::unordered_map<node_id_t, decision_tuple_t>()),
      num_threads(num_threads),
      use_heuristic(use_hough_heuristic),
      heuristic_ratio(hough_heuristic_ratio),
      heuristic_maxd(hough_heuristic_maxd),
      compat_SurfCalc_DProv_checked(false),
      allow_early_stopping(allow_early_stopping) {
      // Compatibility check of seleciton provider and feature calculator
      // dimensions.
      if (this -> selection_provider -> get_selection_dimension() !=
          this -> feature_calculator -> required_num_features()) {
        throw Fertilized_Exception("The number of selected features by the "
          "feature selection provider and the number of features required "
          "by the feature calculator does not match!");
      }
      if (num_threads <= 0) {
        throw Fertilized_Exception("The number of threads must be >0!");
      }
#ifndef _OPENMP
      if (num_threads > 1) {
        throw Fertilized_Exception("This executable has been built without "
          "OpenMP support. The number of threads must =1!");
      }
#endif
      if (use_hough_heuristic) {
        if (!std::is_integral<annotation_dtype>::value) {
          throw Fertilized_Exception("The hough heuristic can only be used "
            "in a hough forest scenarion => the annotation dtype must be "
            "integral!");
        }
        if (std::dynamic_pointer_cast<
              AlternatingThresholdOptimizer<
                input_dtype,
                feature_dtype,
                annotation_dtype>>(threshold_optimizer).get() == NULL) {
          throw Fertilized_Exception("The hough heuristic can only applied if "
            "the used threshold optimizer is an "
            "AlternatingThresholdOptimizer!");
        }
        if (hough_heuristic_ratio < 0.f || hough_heuristic_ratio > 1.f) {
          throw Fertilized_Exception(
            "hough_heuristic_ratio must be in [0., 1.]");
        }
        if (hough_heuristic_maxd == 0) {
          throw Fertilized_Exception("Invalid value for hough heuristic maxd. "
            "The canonic choice is tree max depth - 2. The value 0 is not "
            "accepted.");
        }
      }
    };

    /** Gets the input dimension of the feature selection provider. */
    size_t get_required_num_data_dim() const {
      return selection_provider -> get_input_dimension();
    };

    /**
     * \brief Optimizes \f$\theta=(\phi,\psi,\tau)\f$ by a (non-exhaustive)
     * random search over the parameter space. \f$\tau\f$ is usually optimized
     * perfectly.
     *
     * See the description of the virtual interface function
     * \ref IClassifierManager::optimize_and_set_for_node for more
     * information on the general purpose and parameter descriptions.
     */
    void optimize_and_set_for_node(
      const node_id_t &node_id,
      const uint &node_depth,
      const uint &min_samples_at_leaf,
      const elem_id_vec_t &element_id_list,
      const dprov_t &data_provider,
      bool *make_to_leaf,
      std::shared_ptr<elem_id_vec_t> *element_list_left,
      std::shared_ptr<elem_id_vec_t> *element_list_right) {
      if (! compat_SurfCalc_DProv_checked) {
        if (! this -> feature_calculator -> is_compatible_to(&data_provider)) {
          throw Fertilized_Exception("Incompatible feature calculator and data provider!");
        }
        compat_SurfCalc_DProv_checked = true;
      }
      // Iterate over all suggested feature selections.
      auto suggested_feature_sets =
        selection_provider -> get_proposal_generator();
      FASSERT(suggested_feature_sets -> available());
      float best_gain = std::numeric_limits<float>::lowest();
      std::tuple<
        std::vector<size_t>,
        FeatCalcParamSet,
        optimization_tuple_t> best_configuration;

      // Assure that resources are available for all threads, etc.
      threshold_optimizer -> prepare_for_optimizing(node_id, num_threads);

      // cppcheck-suppress variableScope
      size_t processed_val_count = 0;
      size_t processed_val_max = (n_valids_to_use > 0 ? n_valids_to_use :
                                    suggested_feature_sets -> max_count());
      bool search_valid;
      /**
       * \brief Required to guarantee equivalent parallel results.
       * The maximum operation alone is not equivalent in serial and parallel
       * versions, since the first configuration with the best value is used.
       * It can be guaranteed if additional to the value also the loop index
       * is used.
       */
      int best_config_index =
        static_cast<int>(suggested_feature_sets -> max_count() + 1);
      // cppcheck-suppress variableScope
      int suggestion_index = 0;
      const elem_id_vec_t *used_elems = &element_id_list;
      auto sample_list = data_provider.get_samples();
      std::vector<annotation_dtype> prepared_annots(
        used_elems -> size() * data_provider.get_annot_vec_dim());
      std::vector<float> prepared_weights(used_elems -> size());
      uint neg_count = 0;
      // TODO(Christoph): Replace with std::copy if its a reordering data
      // provider to gain speed!
      const annotation_dtype *annot_ptr;
      annotation_dtype *prep_ptr = &prepared_annots[0];
      for (size_t i = 0; i < used_elems -> size(); ++i) {
        annot_ptr = (*sample_list)[(*used_elems)[i]].annotation;
        if (use_heuristic && *annot_ptr == 0) {
          neg_count++;
        }
        for (size_t j = 0; j < data_provider.get_annot_vec_dim(); ++j) {
          *(prep_ptr++) = *(annot_ptr++);
        }
        prepared_weights[i] = (*sample_list)[(*used_elems)[i]].weight;
      }
      // Check for early stopping.
      if (allow_early_stopping) {
        bool early_stop = threshold_optimizer -> check_for_early_stop(&prepared_annots[0],
          data_provider.get_annot_vec_dim(), used_elems -> size(), node_id);
        if (early_stop) {
          *make_to_leaf = true;
          return;
        }
      }
      // Apply the hough heuristic if necessary.
      if (use_heuristic &&
          !(static_cast<float>(neg_count) /
            static_cast<float>(element_id_list.size()) >= heuristic_ratio &&
            node_depth < heuristic_maxd)) {
        AlternatingThresholdOptimizer<input_dtype,
           feature_dtype, annotation_dtype> *ato =
              dynamic_cast<AlternatingThresholdOptimizer<input_dtype,
                                                         feature_dtype,
                                                         annotation_dtype>*>(
                threshold_optimizer.get());
        ato -> opt_sel_map[node_id] = false;
      }
      // TODO(Christoph): Remove locks in non-parallel mode to improve perf.?
      std::mutex mutex_track;
      std::mutex mutex_opt;
#if defined(_MSC_VER)
#define ADDITIONAL_SHARED_VARS , elem_id_vec_t
#else
#define ADDITIONAL_SHARED_VARS 
#endif
#if !defined(__INTEL_COMPILER)
      #pragma omp parallel num_threads(num_threads) if (num_threads != 1) \
        private(search_valid) default(none) /* Require explicit spec. */\
        shared(best_gain, best_configuration, best_config_index, \
        suggested_feature_sets, data_provider, element_id_list, \
        min_samples_at_leaf, processed_val_count, processed_val_max, \
        mutex_track, mutex_opt, suggestion_index, node_id,\
        prepared_annots, prepared_weights, used_elems, sample_list \
        ADDITIONAL_SHARED_VARS)
#else
      #pragma omp parallel num_threads(num_threads) if (num_threads != 1) \
        private(search_valid) default(none) /* Require explicit spec. */\
        shared(best_gain, best_configuration, best_config_index, \
        suggested_feature_sets, data_provider, element_id_list, \
        min_samples_at_leaf, processed_val_count, processed_val_max, \
        mutex_track, mutex_opt, suggestion_index, node_id,\
        prepared_annots, prepared_weights, used_elems, sample_list)
#endif
      {
#undef ADDITIONAL_SHARED_VARS
        while (suggested_feature_sets -> available() &&
               processed_val_count < processed_val_max) {
          std::vector<size_t> feature_selection_vector;
          int my_suggestion_index;
          {
            std::lock_guard<std::mutex> lock(mutex_track);
            #pragma omp flush(suggestion_index, processed_val_count)
            if (suggested_feature_sets -> available() &&
                processed_val_count < processed_val_max) {
              // Assume that this run is valid.
              processed_val_count++;
              my_suggestion_index = suggestion_index++;
              #pragma omp flush(suggestion_index, processed_val_count)
              feature_selection_vector = suggested_feature_sets -> get_next();
              //std::cout << "Checking feature " << feature_selection_vector[0] << std::endl;
            } else {
              // Set break flag here. OpenMP doesn't allow breaks in criticals.
              my_suggestion_index = -1;
            }
          }
          if (my_suggestion_index == -1)
            break;

          bool feature_could_be_used = false;
          std::vector<FeatCalcParamSet> param_sets =
            feature_calculator -> propose_params();
          FASSERT(param_sets.size() > 0);

          // Prepare everything for offloading.
          // TODO(Christoph): Replace with std::copy if its a reordering data
          // provider to gain speed!
          elem_id_vec_t pos_elems = elem_id_vec_t(0);
          if (!threshold_optimizer -> needs_negatives(node_id)) {
            // If this is enabled, the sample counting is broken (and
            // thresholds are ignored that shouldn't be ignored).
            throw Fertilized_Exception("The standard classifier currently "
              "does not support the 'needs_negatives' option!");
            // Only prepare the positives and save some time.
            //for (const auto &element_id : element_id_list) {
            //  if (*((*sample_list)[ element_id ].annotation) != 0)
            //    pos_elems.push_back(element_id);
            //}
            //used_elems = &pos_elems;
          }
          std::vector<input_dtype> prepared_inputs(0);
          if (feature_calculator -> needs_elements_prepared()) {
            prepared_inputs.resize(used_elems -> size() * feature_selection_vector.size());
            // Checks.
            FASSERT(check_elem_ids_ok((*sample_list).size(), *used_elems));
            FASSERT(check_sample_weights_ok(*sample_list, *used_elems));
            for (size_t j = 0; j < feature_selection_vector.size(); ++j) {
              for (size_t i = 0; i < used_elems -> size(); ++i) {
                // TODO(Christoph): Optimize! Change the order of loops dependent
                // of row or column major data to improve cache locality.
                prepared_inputs[i+j*used_elems -> size()] =
                  *((*sample_list)[ (*used_elems)[i] ].data +
                    (*sample_list)[ (*used_elems)[i] ].data_step * feature_selection_vector[j]);
              }
            }
          }

          size_t n_samples = used_elems -> size();
          //////////////// Offload here if possible.
          for (const auto &param_set : param_sets) {
            auto feature_values =
              feature_calculator -> calculate(prepared_inputs.data(),
                                              prepared_inputs.size(),
                                              feature_selection_vector,
                                              *used_elems,
                                              sample_list,
                                              param_set);
            optimization_tuple_t optimization_result =
              threshold_optimizer -> optimize(node_id,
                                              my_suggestion_index,
                                              min_samples_at_leaf,
                                              n_samples,
                                              prepared_inputs.data(),
                                              feature_selection_vector.size(),
                                              prepared_annots.data(),
                                              data_provider.get_annot_vec_dim(),
                                              prepared_weights.data(),
                                              feature_values.get(),
                                              &search_valid);
            if (n_valids_to_use != 0 && !search_valid)
              continue;
            else
              feature_could_be_used = true;
            //#pragma omp critical (FERTILIZED_CLASSIFIERS_H_THRESHOLD_CLASSIFIER_1_)
            {
              std::lock_guard<std::mutex> lock(mutex_opt);
              #pragma omp flush(best_gain, best_configuration, best_config_index)
              if (std::get<4>(optimization_result) > best_gain ||
                  std::get<4>(optimization_result) == best_gain &&
                  my_suggestion_index < best_config_index) {
                best_gain = std::get<4>(optimization_result);
                best_configuration = std::make_tuple(feature_selection_vector,
                                                     param_set,
                                                     optimization_result);
                best_config_index = my_suggestion_index;
                #pragma omp flush(best_gain, best_configuration, best_config_index)
              }
            }
          }
          ////////////// Return here.
          // It was assumed that it worked. If no use could be found, reduce
          // the val count to the correct value.
          if (n_valids_to_use != 0 && !feature_could_be_used) {
          //#pragma omp critical (FERTILIZED_CLASSIFIERS_H_THRESHOLD_CLASSIFIER_0_)
          {
            std::lock_guard<std::mutex> lock(mutex_track);
            processed_val_count--;
            #pragma omp flush(processed_val_count)
          }
          }
        }
      }

      //std::cout << "S. left: " << std::get<2>(std::get<2>(best_configuration)) <<
      //  ". S. right: " << std::get<3>(std::get<2>(best_configuration)) <<
      //  ". Gain: " << std::get<4>(std::get<2>(best_configuration)) <<
      //  ". Index: " << best_config_index << "." << std::endl;
      // Check whether this node must become a leaf or a decision node.
      if (std::get<2>(std::get<2>(best_configuration)) < min_samples_at_leaf ||
          std::get<3>(std::get<2>(best_configuration)) < min_samples_at_leaf ||
          std::get<4>(std::get<2>(best_configuration)) <
                      threshold_optimizer -> get_gain_threshold_for(node_id)) {
        // Make it a leaf node.
        *make_to_leaf = true;
        return;
      } else {
        // Make it a decision node.
        *make_to_leaf = false;
        // Store the parameters.
        auto ret = decision_param_map.emplace(node_id, std::make_tuple(
          std::get<0>(best_configuration),
          std::get<1>(best_configuration),
          std::get<1>(std::get<2>(best_configuration)),
          std::get<0>(std::get<2>(best_configuration))));

        if (!ret.second) {
          throw Fertilized_Exception("Tried to reset a node's decision "
            "parameters.");
        }

        // Create the element lists.
        *element_list_left = std::make_shared<elem_id_vec_t>();
        *element_list_right = std::make_shared<elem_id_vec_t>();
        auto sample_list = data_provider.get_samples();
        for (const auto &element_id : element_id_list) {
          if (decide(node_id,
                     (*sample_list)[element_id].data,
                     (*sample_list)[element_id].data_step,
                     data_provider.get_decision_transf_func(element_id))) {
            (*element_list_left) -> push_back(element_id);
          } else {
            (*element_list_right) -> push_back(element_id);
          }
        }
        // Check.
        FASSERT(std::get<2>(std::get<2>(best_configuration)) == (*element_list_left) -> size() &&
                std::get<3>(std::get<2>(best_configuration)) == (*element_list_right)-> size())
        FASSERT((*element_list_left)  -> size() +
                (*element_list_right) -> size() == element_id_list.size())
      }
    };

    /**
     * \brief Decides whether a sample should go left or right at a node.
     *
     * \return true if a sample goes left, false otherwise.
     */
    bool decide(const node_id_t &node_id,
                const input_dtype *data,
                const size_t &data_step,
                const std::function<void(void*)> &decision_param_transf = nullptr)
     const {
      // Get the decision parameters.
      const decision_tuple_t *decision_params =&decision_param_map.at(node_id);
      feature_dtype feature;
      if (decision_param_transf != nullptr) {
        decision_tuple_t real_params = *decision_params;
        decision_param_transf(static_cast<void*>(&real_params));
        feature = feature_calculator -> calculate(std::get<0>(real_params),
                                                  std::get<1>(real_params),
                                                  data,
                                                  data_step);
        switch (std::get<2>(real_params)) {
        case EThresholdSelection::less_only:
          return feature < std::get<3>(real_params).first;
        case EThresholdSelection::greater_only:
          return feature > std::get<3>(real_params).second;
        case EThresholdSelection::both:
          return feature < std::get<3>(real_params).first &&
                 feature > std::get<3>(real_params).second;
        default:
          throw Fertilized_Exception("Wrong threshold type used.");
        }
      } else {
        feature = feature_calculator -> calculate(std::get<0>(*decision_params),
                                                  std::get<1>(*decision_params),
                                                  data,
                                                  data_step);
        switch (std::get<2>(*decision_params)) {
        case EThresholdSelection::less_only:
          return feature < std::get<3>(*decision_params).first;
        case EThresholdSelection::greater_only:
          return feature > std::get<3>(*decision_params).second;
        case EThresholdSelection::both:
          return feature < std::get<3>(*decision_params).first &&
                 feature > std::get<3>(*decision_params).second;
        default:
          throw Fertilized_Exception("Wrong threshold type used.");
        }
      }
    };

    /**
     * \brief Returns true if the threshold optimizer supports weights.
     */
    bool supports_weights() const {
     return threshold_optimizer -> supports_weights();
    };

    /** Gets the IFeatureSelectionProvider. */
    std::shared_ptr<const IFeatureSelectionProvider> get_selection_provider() const {
      return selection_provider;
    }
    
    /**
     * \brief Computes a feature importance vector.
     * 
     * The vector is normalized to sum to 1.0. It contains the relative
     * frequencies of the feature occurences. Its length is the number
     * of available features.
     * 
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * -----
     */
    Array<double, 1, 1> compute_feature_importances() const {
        if (decision_param_map.size() == 0) {
            throw Fertilized_Exception("This decider has no decision rules "
              "stored! This can happen if the training was not run yet, or "
              "if the decision tree only has one leaf (the root node). To "
              "solve the problem, either run the training, or call "
              "forest -> compute_feature_importances() to have it "
              "handle this case automatically by using the importances "
              "of other trees.");
        }
        // Get the total number of features.
        const size_t total = selection_provider -> get_n_available_features();
        // Allocate and initialize the array to return.
        Array<double, 1, 1> result = allocate(total);
        result.deep() = 0.;
        // Calculate the total usage numbers of each feature.
        for (const auto &id_param_pair : decision_param_map) {
            // The node id is irrelevant, just get the parameter tuple.
            const decision_tuple_t &param_tpl = id_param_pair.second;
            // This is the vector of used feature dimensions.
            const std::vector<size_t> dimvec = std::get<0>(param_tpl);
            // Add up the counts.
            for (const size_t &dimind : dimvec) {
                result[ dimind ] += 1.;
            }
        }
        // Normalize to get the relative frequencies.
        result.deep() /= static_cast<double>(decision_param_map.size());
        return result;
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
    bool operator==(const IDecider<input_dtype,
                    feature_dtype,
                    annotation_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<ThresholdDecider<input_dtype,
                                                           feature_dtype,
                                                           annotation_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_surf = (typeid(*feature_calculator) == typeid(*(rhs_c -> feature_calculator)) ||
                (typeid(*feature_calculator) == typeid(DirectPatchDifferenceSurfCalculator<input_dtype, feature_dtype, annotation_dtype>) &&
                 typeid(*(rhs_c -> feature_calculator)) == typeid(DifferenceSurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>)) ||
                (typeid(*feature_calculator) == typeid(DifferenceSurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>) &&
                 typeid(*(rhs_c -> feature_calculator)) == typeid(DirectPatchDifferenceSurfCalculator<input_dtype, feature_dtype, annotation_dtype>)));
        bool eq_valid = n_valids_to_use == rhs_c -> n_valids_to_use;
        bool eq_map = decision_param_map == rhs_c -> decision_param_map;
        bool app_equiv = eq_surf &&
                         eq_map &&
                         eq_valid;
        bool eq_sel = *selection_provider == *(rhs_c -> selection_provider);
        bool eq_opt = *threshold_optimizer == *(rhs_c -> threshold_optimizer);
        bool eq_heur = use_heuristic == rhs_c -> use_heuristic;
        bool eq_heur_r = heuristic_ratio == rhs_c -> heuristic_ratio;
        bool eq_heur_d = heuristic_maxd == rhs_c -> heuristic_maxd;
        bool eq_ear = allow_early_stopping == rhs_c -> allow_early_stopping;
        bool train_equiv = eq_sel &&
                           eq_opt &&
                           eq_heur &&
                           eq_heur_r &&
                           eq_heur_d &&
                           eq_valid &&
                           eq_ear;
        //std::cout << eq_surf << std::endl;
        //std::cout << eq_valid << std::endl;
        //std::cout << eq_map << std::endl;
        //std::cout << eq_sel << std::endl;
        //std::cout << eq_opt << std::endl;
        //std::cout << eq_heur << std::endl;
        //std::cout << eq_heur_r << std::endl;
        //std::cout << eq_heur_d << std::endl;
        //std::cout << eq_ear << std::endl;
        if (decision_param_map.size() == 0) {
          return app_equiv && train_equiv;
        } else {
          return app_equiv;
        }
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<iclassifier_manager_t>(*this);
      ar & selection_provider;
      ar & feature_calculator;
      ar & threshold_optimizer;
      ar & n_valids_to_use;
      ar & decision_param_map;
      ar & num_threads;
      ar & use_heuristic;
      ar & heuristic_ratio;
      ar & heuristic_maxd;
      ar & allow_early_stopping;
    }
#endif

    // cppcheck-suppress uninitVar
    ThresholdDecider() {}

   private:
    std::shared_ptr<IFeatureSelectionProvider> selection_provider;
    std::shared_ptr<feat_calc_t> feature_calculator;
    std::shared_ptr<thresh_opt_t> threshold_optimizer;
    size_t n_valids_to_use;
    std::unordered_map<node_id_t, decision_tuple_t> decision_param_map;
    int num_threads;
    bool use_heuristic;
    float heuristic_ratio;
    uint heuristic_maxd;
    bool compat_SurfCalc_DProv_checked;
    bool allow_early_stopping;
  };
};  // namespace fertilized
#endif  // FERTILIZED_DECIDERS_THRESHOLDDECIDER_H_
