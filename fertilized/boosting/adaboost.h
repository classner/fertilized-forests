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

namespace fertilized {
   /**
    * \brief AdaBoost.M2 boosting algorithm implementation
    *
    * Implements the original AdaBoost algorithm proposed by Freund and Schapire
    * See "A decision-theoretic generalization of on-line learning and an application to boosting". Journal of Computer and System Sciences 55. 1997
    * To support multi-class classification, the AdaBoost.M2 algorithm is used
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
    *
    * -----
    */
    template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
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
        void perform(const tree_ptr_vec_t& trees, fdprov_t* fdata_provider, exec_strat_t* exec_strategy, uint n_classes) {
            if(n_classes != 2) throw Fertilized_Exception("The AdaBoost boosting algorithm does not work with more than two classes");
            //Get samples
            auto samples = std::const_pointer_cast<sample_list_t>(fdata_provider->get_samples());

            std::vector<float> initial_weights(n_classes); //Initial weights for the different classes
            float normalizeBase = 1.f; //The base value for weight normalization

            for(int i = 0; i < samples->size(); ++i)
                initial_weights[*samples->at(i).annotation]++; //Count sample amount for each class
            for(int i = 0; i < n_classes; ++i)
                initial_weights[i] = 1.0/(n_classes*initial_weights[i]); //Calculate inital weights
            for(int i = 0; i < samples->size(); ++i)
                samples->at(i).weight = initial_weights[*samples->at(i).annotation]; //Initialize sample weights

            for (size_t treeIndex = 0; treeIndex < trees.size(); ++treeIndex) {
                //1. Normalize the weights
                for(int i = 0; i < samples->size(); ++i) samples->at(i).weight /= normalizeBase;
                normalizeBase = 0.f;

                //2. Train the current tree
                train_act_t current_train_act(treeIndex, CompletionLevel::Complete, action_type::DFS, fdata_provider->dproviders[treeIndex]);
                exec_strategy->execute_step(current_train_act);

                //3. Update sample weights
                float weightAccu = 0.f;
                float errorAccu = 0.f;
                float singleError = 0.f;
                for(int sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    std::vector<float> result = trees[treeIndex]->predict_leaf_result(samples->at(sampleIndex).data);
                    singleError = *std::max_element(result.begin(), result.end()) == *samples->at(sampleIndex).annotation ? 0.f : 1.f;
                    errorAccu += samples->at(sampleIndex).weight*singleError;
                    weightAccu += samples->at(sampleIndex).weight;
                }
                float error = errorAccu / weightAccu;
                std::cout << "errorAccu is " << errorAccu << std::endl;
                for(int sampleIndex = 0; sampleIndex < samples->size(); ++sampleIndex) {
                    float alpha = std::log((1.f-error)/(error));
                    samples->at(sampleIndex).weight *= std::exp(alpha*singleError);
                    normalizeBase += samples->at(sampleIndex).weight;
                }

                //4. Update tree weight
                trees[treeIndex]->set_weight(std::log(1.0f/error));
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
            const auto *rhs_c = dynamic_cast<AdaBoost<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> const *>(&rhs);
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
