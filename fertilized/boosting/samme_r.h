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

namespace fertilized {
   /**
    * \brief SAMME.R real boosting algorithm implementation
    *
    * Implements the SAMME.R real boosting algorithm proposed by J. Zhu, H. Zou, S. Rosset and T. Hastie
    * See Zhu, H. Zou, S. Rosset, T. Hastie, "Multi-class AdaBoost", 2009
    * One can set the learning rate which specifies the contribution of each classifier
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
    class Samme_R : public IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
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
        Samme_R(float learning_rate=1.f) : learning_rate(learning_rate) {}

        /**
        * \brief Performs the SAMME.R training
        */
        void perform(const tree_ptr_vec_t& trees, fdprov_t* fdata_provider, exec_strat_t* exec_strategy, uint n_classes) {

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
            const auto *rhs_c = dynamic_cast<Samme_R<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> const *>(&rhs);
            return rhs_c != nullptr;
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
