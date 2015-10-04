/* Author: Christian Diller. */
#pragma once
#ifndef FERTILIZED_BOOSTING_IBOOSTINGSTRATEGY_H_
#define FERTILIZED_BOOSTING_IBOOSTINGSTRATEGY_H_

#include <memory>
#include <vector>

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"
#include "../execution_strategies/iexecutionstrategy.h"
#include "../execution_strategies/trainingaction.h"
#include "../data_providers/iforestdataprovider.h"

namespace fertilized {
   /**
    * \brief Specifies the boosting algorithm that will be used for training
    *
    * Use the IBoostingStrategy in combination with a \ref BoostingLeafManager
    * to allow it to set a custom weight function per tree which may lead to
    * better classification results.
    *
    * \ingroup fertilizedboostingGroup
    *
    * -----
    * Available in:
    * - C++
    * - Python
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
    template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
    class IBoostingStrategy {
    public:
        typedef Tree<input_dtype, feature_dtype, annotation_dtype,
                     leaf_return_dtype, forest_return_dtype> tree_t;
        typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;
        typedef std::shared_ptr<tree_t> tree_ptr_t;
        typedef std::vector<tree_ptr_t> tree_ptr_vec_t;
        typedef IExecutionStrategy<input_dtype, feature_dtype, annotation_dtype,
                      leaf_return_dtype, forest_return_dtype> exec_strat_t;

        virtual ~IBoostingStrategy() {}

        virtual void perform(const tree_ptr_vec_t& trees,
                             fdprov_t* fdata_provider,
                             exec_strat_t* exec_strategy,
                             uint n_classes)
            VIRTUAL_VOID;

        virtual bool operator==(const IBoostingStrategy<input_dtype,
                                                        feature_dtype,
                                                        annotation_dtype,
                                                        leaf_return_dtype,
                                                        forest_return_dtype> &rhs)
            const VIRTUAL(bool);

    #ifdef SERIALIZATION_ENABLED
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const uint file_version) {}
    #endif

    protected:
        IBoostingStrategy() {}
    };
};  // namespace fertilized
#endif // FERTILIZED_BOOSTING_IBOOSTINGSTRATEGY_H_
