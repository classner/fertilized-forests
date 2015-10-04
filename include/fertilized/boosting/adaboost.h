/* Author: Christian Diller. */
#pragma once
#ifndef FERTILIZED_BOOSTING_ADABOOST_H_
#define FERTILIZED_BOOSTING_ADABOOST_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "./iboostingstrategy.h"
#include "../ndarray.h"
#include "../leafs/boostingleafmanager.h"

namespace fertilized {
   /**
    * \brief AdaBoost.M2 boosting algorithm implementation
    *
    * Implements the original AdaBoost algorithm proposed by Freund and Schapire
    *
    * See "A decision-theoretic generalization of on-line learning and an
    * application to boosting". Journal of Computer and System Sciences 55. 1997
    *
    * To support multi-class classification, the AdaBoost.M2 algorithm is used.
    *
    * Output when using BoostingLeafManager is
    * estimator_probability*std::log(1.f/beta).
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
    template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
    class AdaBoost : public IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
    public:
        typedef IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> boost_strat_t;
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
        AdaBoost() {}

        /**
        * \brief Performs the AdaBoost.M2 training
        */
        void perform(const tree_ptr_vec_t& trees,
                     fdprov_t* fdata_provider,
                     exec_strat_t* exec_strategy,
                     uint n_classes) {
            //Get samples
            auto samples = std::const_pointer_cast<sample_list_t>(
              fdata_provider->get_samples());
            size_t n_samples = samples->size();

            //Initialize weight vector
            Array<float, 2, 2> weightVector =
              allocate(makeVector(n_samples, static_cast<size_t>(n_classes)));
            weightVector.deep() = 1.f /
              static_cast<float>((n_samples)*(n_classes-1));
            // Cast boostingleafmanager, will be nullptr if no
            // BoostingLeafManager is used
            auto boostingleafmanager =
             std::const_pointer_cast<BoostingLeafManager<input_dtype, annotation_dtype>>(
                std::dynamic_pointer_cast<const BoostingLeafManager<input_dtype,annotation_dtype>>(
                  trees[0]->get_leaf_manager()));
            for (size_t treeIndex = 0; treeIndex < trees.size(); ++treeIndex) {
                // Calculate sample weight
                float W_sum = 0.f;
                for (size_t sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    annotation_dtype y = *samples->at(sampleIndex).annotation;
                    float W = 0.f;
                    for (uint classIndex = 0U; classIndex < n_classes; ++classIndex) {
                        if (classIndex == y) continue;
                        W += weightVector[sampleIndex][classIndex];
                    }
                    samples->at(sampleIndex).weight = W;
                    W_sum += W;
                }
                for(int sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    samples->at(sampleIndex).weight /= W_sum;
                }

                // Train the current tree
                train_act_t current_train_act(treeIndex,
                                              CompletionLevel::Complete,
                                              action_type::DFS,
                                              fdata_provider->dproviders[treeIndex]);
                exec_strategy->execute_step(current_train_act);

                // Calculate epsilon
                float epsilon = 0.f;
                Array<float,2,2> hypothesis = allocate(
                  makeVector(n_samples, static_cast<size_t>(n_classes)));
                for(int sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    annotation_dtype y = *samples->at(sampleIndex).annotation;
                    std::vector<float> output =
                      trees[treeIndex]->predict_leaf_result(samples->at(sampleIndex).data);
                    for(uint classIndex = 0U; classIndex < n_classes; ++classIndex) {
                        hypothesis[sampleIndex][classIndex] = output[classIndex] *
                         (classIndex == y ? 0.5f : weightVector[sampleIndex][classIndex]);
                    }
                    float questionSum = 0.f;
                    for(uint classIndex = 0U; classIndex < n_classes; ++classIndex) {
                        if(classIndex == y) continue;
                        questionSum += (weightVector[sampleIndex][classIndex] / W_sum) *
                                       hypothesis[sampleIndex][classIndex];
                    }
                    epsilon += samples->at(sampleIndex).weight *
                     (1-hypothesis[sampleIndex][y]+questionSum);
                }
                epsilon /= 2.f;

                //Calculate beta and update the weightVector
                float beta = epsilon/(1.f-epsilon);
                for(int sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    annotation_dtype y = *samples->at(sampleIndex).annotation;
                    for(uint classIndex = 0U; classIndex < n_classes; ++classIndex) {
                        weightVector[classIndex][sampleIndex] *=
                          std::pow(beta,
                                   0.5f * (1.f + hypothesis[sampleIndex][y] -
                                                 hypothesis[sampleIndex][classIndex]));
                    }
                }

                //Set tree weight
                if(boostingleafmanager != nullptr) {
                    boostingleafmanager->set_weight_function(
                      treeIndex,
                      [n_classes,beta](std::vector<float> input)->std::vector<float>{
                        std::vector<float> output(n_classes);
                        for(uint k = 0U; k < n_classes; ++k) output[k] = input[k]*std::log(1.f/beta);
                        return output;
                      });
                }
                trees[treeIndex]->set_weight(beta == 0 ? 0.f : std::log(1.f/beta));
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
        bool operator==(const IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &rhs) const {
            const auto *rhs_c = dynamic_cast<
              AdaBoost<input_dtype,
                       feature_dtype,
                       annotation_dtype,
                       leaf_return_dtype,
                       forest_return_dtype> const *>(&rhs);
            return rhs_c != nullptr;
        }

    #ifdef SERIALIZATION_ENABLED
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const uint file_version) {
            ar & boost::serialization::base_object<boost_strat_t>(*this);
        }
    #endif
    };
};  // namespace fertilized

#endif  // FERTILIZED_BOOSTING_ADABOOST_H_
