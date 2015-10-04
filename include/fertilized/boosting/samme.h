/* Author: Christian Diller. */
#pragma once
#ifndef FERTILIZED_BOOSTING_SAMME_H_
#define FERTILIZED_BOOSTING_SAMME_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "./iboostingstrategy.h"
#include "../leafs/boostingleafmanager.h"

namespace fertilized {
   /**
    * \brief SAMME boosting algorithm implementation
    *
    * Implements the SAMME boosting algorithm proposed by J. Zhu, H. Zou,
    * S. Rosset and T. Hastie ("Multi-class AdaBoost", 2009).
    *
    * One can set the learning rate which specifies the contribution of each
    * classifier.
    *
    * Output when using BoostingLeafManager is
    * estimator_probability*estimator_weight.
    *
    * \ingroup fertilizedboostingGroup
    *
    * -----
    * Available in:
    * - C++
    * - Python
    * - Matlab
    * .
    * Instantiations:
    * - int; int; uint; std::vector<float>; std::vector<float>
    * - float; float; uint; std::vector<float>; std::vector<float>
    * - double; double; uint; std::vector<float>; std::vector<float>
    * - uint8_t; uint8_t; uint; std::vector<float>; std::vector<float>
    * - uint8_t; int16_t; uint; std::vector<float>; std::vector<float>
    * - uint8_t; int16_t; int16_t; std::vector<float>; std::vector<float>
    * .
    * Serialization generation: 101
    *
    * -----
    */
    template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
    class Samme : public IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
    public:
        typedef IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype,
          leaf_return_dtype, forest_return_dtype> boost_strat_t;
        typedef TrainingAction<input_dtype, annotation_dtype> train_act_t;
        using typename boost_strat_t::fdprov_t;
        using typename boost_strat_t::tree_ptr_vec_t;
        using typename boost_strat_t::exec_strat_t;
        typedef Sample<input_dtype, annotation_dtype> sample_t;
        typedef std::vector<sample_t> sample_list_t;

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
        Samme(float learning_rate=1.f) : learning_rate(learning_rate) {
            if(learning_rate <= 0 || learning_rate > 1.f)
                throw Fertilized_Exception("The learning rate has to be in (0, 1]");
        }

        /**
        * \brief Performs the discrete SAMME training
        */
        void perform(const tree_ptr_vec_t& trees,
                     fdprov_t* fdata_provider,
                     exec_strat_t* exec_strategy,
                     uint n_classes) {
            // Get the samples
            auto samples = std::const_pointer_cast<sample_list_t>(
              fdata_provider->get_samples());
            // Initialize sample weights
            float inital_weight = 1.f / static_cast<float>(samples->size());
            for (size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                samples->at(sampleIndex).weight = inital_weight;
            }

            // Cast boostingleafmanager, will be nullptr if no
            // BoostingLeafManager is used
            auto boostingleafmanager =
              std::const_pointer_cast<BoostingLeafManager<input_dtype,annotation_dtype>>(
                std::dynamic_pointer_cast<
                  const BoostingLeafManager<input_dtype,annotation_dtype>>(
                  trees[0]->get_leaf_manager()));
            for(size_t treeIndex = 0; treeIndex < trees.size(); ++treeIndex) {
                // Train the current tree
                train_act_t current_train_act(
                  treeIndex,
                  CompletionLevel::Complete,
                  action_type::DFS,
                  fdata_provider->dproviders[treeIndex]);
                exec_strategy->execute_step(current_train_act);

                // Check for misclassified samples
                std::vector<bool> misclassified(samples->size());
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    std::vector<float> result =
                      trees[treeIndex]->predict_leaf_result(
                        samples->at(sampleIndex).data);
                    misclassified[sampleIndex] =
                      ((std::max_element(result.begin(),
                                         result.end()) - result.begin()) !=
                       *samples->at(sampleIndex).annotation);
                }

                // Calculate estimator error
                float estimator_error = 0.f;
                float weight_sum = 0.f;
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    estimator_error +=
                      (samples->at(sampleIndex).weight * (misclassified[sampleIndex] ? 1.f : 0.f));
                    weight_sum += samples->at(sampleIndex).weight;
                }
                estimator_error /= weight_sum;
                float estimator_weight = 0.f;

                if(estimator_error <= 0) { // Best result
                    estimator_weight = 1.f;
                } else if(estimator_error >= 1.f - 1.f / n_classes) { // Worst result
                    estimator_weight = 0.f;
                } else { // Calculate estimator weight
                     estimator_weight = learning_rate *
                         std::log((1.f - estimator_error) / estimator_error) +
                       std::log(static_cast<float>(n_classes) - 1.f);
                }

                // Set new sample weights
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    samples->at(sampleIndex).weight *=
                      (samples->at(sampleIndex).weight > 0 || estimator_weight < 0) ?
                      std::exp(estimator_weight * misclassified[sampleIndex]) : 1.f;
                }

                // Normalize sample weights
                float normalize_base = 0.f;
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    normalize_base += samples->at(sampleIndex).weight;
                }
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    samples->at(sampleIndex).weight /= normalize_base;
                }

                // Set tree weight
                if(boostingleafmanager != nullptr) {
                    boostingleafmanager->set_weight_function(
                      treeIndex,
                      [n_classes,estimator_weight](std::vector<float> input)->std::vector<float>{
                        std::vector<float> output(n_classes);
                        for(uint k = 0U; k < n_classes; ++k) output[k] = input[k]*estimator_weight;
                        return output;
                      });
                }
                trees[treeIndex]->set_weight(estimator_weight);
            }
        }

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
        bool operator==(const IBoostingStrategy<input_dtype,
                                                feature_dtype,
                                                annotation_dtype,
                                                leaf_return_dtype,
                                                forest_return_dtype> &rhs) const {
            const auto *rhs_c = dynamic_cast<Samme<input_dtype,
                                                   feature_dtype,
                                                   annotation_dtype,
                                                   leaf_return_dtype,
                                                   forest_return_dtype> const *>(&rhs);
            return rhs_c != nullptr && learning_rate == rhs_c->learning_rate;
        }

    #ifdef SERIALIZATION_ENABLED
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const uint file_version) {
            ar & boost::serialization::base_object<boost_strat_t>(*this);
            ar & learning_rate;
        }
    #endif
    private:
        float learning_rate;
    };
};  // namespace fertilized

#endif  // FERTILIZED_BOOSTING_SAMME_H_
