/* Author: Christian Diller. */
#pragma once
#ifndef FERTILIZED_BOOSTING_SAMME_R_H_
#define FERTILIZED_BOOSTING_SAMME_R_H_

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
    * \brief SAMME.R real boosting algorithm implementation
    *
    * Implements the SAMME.R real boosting algorithm proposed by J. Zhu,
    * H. Zou, S. Rosset and T. Hastie ("Multi-class AdaBoost", 2009).
    *
    * One can set the learning rate which specifies the contribution of
    * each classifier.
    *
    * Output when using BoostingLeafManager is
    * \f$log(p_k^m(x))-1/K*sum_k(log(p_k^m(x)))\f$.
    *
    * with \f$x\f$ the sample to classify, \f$K\f$ the number of classes,
    * \f$k\f$ the classIndex, \f$m\f$ the estimatorIndex and \f$p\f$ the
    * estimator probability.
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
    class Samme_R : public IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
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
        Samme_R(float learning_rate=1.f) : learning_rate(learning_rate) {
            if(learning_rate <= 0 || learning_rate > 1.f)
                throw Fertilized_Exception("The learning rate has to be in (0, 1]");
        }

        /**
        * \brief Performs the SAMME.R training
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
            for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                samples->at(sampleIndex).weight = inital_weight;
            }

            // Cast boostingleafmanager, will be nullptr if no
            // BoostingLeafManager is used
            auto boostingleafmanager =
              std::const_pointer_cast<BoostingLeafManager<input_dtype,annotation_dtype>>(
                std::dynamic_pointer_cast<const BoostingLeafManager<input_dtype,annotation_dtype>>(
                  trees[0]->get_leaf_manager()));
            for(size_t treeIndex = 0; treeIndex < trees.size(); ++treeIndex) {
                // Train the current tree
                train_act_t current_train_act(
                  treeIndex,
                  CompletionLevel::Complete,
                  action_type::DFS,
                  fdata_provider->dproviders[treeIndex]);
                exec_strategy->execute_step(current_train_act);

                float estimator_weight = 0.f;
                for(size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    std::vector<float> result =
                      trees[treeIndex]->predict_leaf_result(
                        samples->at(sampleIndex).data);
                    float weight = 0.f;
                    annotation_dtype y = *samples->at(sampleIndex).annotation;
                    //Calculate the weight for the current sample
                    for(uint classIndex = 0U; classIndex < result.size(); ++classIndex) {
                        weight += -1.f*((static_cast<float>(n_classes)-1.f)/static_cast<float>(n_classes)) *
                                (classIndex == y ? 1.f : -1.f/(static_cast<float>(n_classes)-1.f)) *
                                (result[classIndex] == 0.f ? std::log(1e-5f) : std::log(result[classIndex]));
                    }
                    samples->at(sampleIndex).weight *= (samples->at(sampleIndex).weight > 0 || estimator_weight < 0) ?
                                std::exp(learning_rate * weight) : 1.f;
                    estimator_weight += weight;
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
                    boostingleafmanager->set_weight_function(treeIndex,
                      [n_classes](std::vector<float> input)->std::vector<float>{
                        std::vector<float> output(n_classes);
                        float mean = 0.f;
                        for (uint k = 0U; k < n_classes; ++k) {
                          mean += (input[k] == 0.f ?
                                    std::log(1e-5f) :
                                    std::log(input[k])/static_cast<float>(n_classes));
                        }
                        for (uint k = 0U; k < n_classes; ++k) {
                          output[k] = (input[k] == 0.f ?
                                        std::log(1e-5f) :
                                        std::log(input[k]))-mean;
                        }
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
            const auto *rhs_c = dynamic_cast<Samme_R<input_dtype,
              feature_dtype, annotation_dtype, leaf_return_dtype,
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

#endif  // FERTILIZED_BOOSTING_SAMME_R_H_
