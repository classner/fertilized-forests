/* Author: Christian Diller. */
#pragma once

#ifndef FERTILIZED_TRAININGS_BOOSTEDTRAINING_H_
#define FERTILIZED_TRAININGS_BOOSTEDTRAINING_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <memory>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"
#include "../bagging/nobagging.h"
#include "../boosting/iboostingstrategy.h"
#include "../execution_strategies/iexecutionstrategy.h"
#include "../execution_strategies/trainingaction.h"
#include "../data_providers/iforestdataprovider.h"
#include "../leafs/boostingleafmanager.h"
#include "../leafs/classificationleafmanager.h"
#include "./itraining.h"

namespace fertilized {
    /**
    * \brief Implements a boosted training that uses a boosting implementation defined by an \ref IBoostingStrategy
    *
    * Trains all trees using a given boosting algorithm implementation
    * Use a \ref BoostingLeafManager to let the boosting strategies decide their weight functions
    *
    * \ingroup fertilizedtrainingsGroup
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
    template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
    class BoostedTraining : public ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
    public:
        typedef ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> training_t;
        typedef IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> boost_strat_t;
        using typename training_t::idec_t;
        using typename training_t::fdprov_t;
        using typename training_t::tree_ptr_vec_t;
        using typename training_t::exec_strat_t;
        typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;

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
        * \param bagging_strategy \ref IBagginStrategy
        *   The bagging strategy to use to distribute samples amongst trees.
        */
        BoostedTraining(const std::shared_ptr<boost_strat_t>& boosting_strategy) : boosting_strategy(boosting_strategy) {}

        /** \brief Returns always true. */
        bool check_compatibility(const fdprov_t &prov) const {
            return true;
        }

        /** \brief Returns always true. */
        bool check_compatibility(const idec_t &classifier_manager) const {
            return true;
        }

        /**
        * \brief Performs the boosted training by calling the given \ref IBoostingStrategy
        *
        * For a detailed description of the used algorithm, see the implementations of IBoostingStrategy
        */
        void perform(const tree_ptr_vec_t& trees, fdprov_t* fdata_provider, exec_strat_t* exec_strategy) {
            //Get samples with NoBagging strategy
            auto bagging_strategy = NoBagging<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>();
            auto usage_map = bagging_strategy.get_initial_split(trees.size(), fdata_provider);
            fdata_provider->create_tree_providers(trees.size(), usage_map);

            // Get the leaf manager
            uint n_classes;
            auto leaf_manager = trees[0] -> get_leaf_manager();
            const auto *lm_ptr = dynamic_cast<ClassificationLeafManager<input_dtype,
                                                                        annotation_dtype> const *>(leaf_manager.get());
            if (lm_ptr == nullptr) {
              const auto *blm_ptr = dynamic_cast<BoostingLeafManager<input_dtype,
                                                                     annotation_dtype> const *>(leaf_manager.get());
              if (blm_ptr == nullptr) {
                throw Fertilized_Exception("Neither a ClassificationLeafManager nor a BoostingLeafManager is used."
                  "The boosted training cannot deal with other leaf managers!");
              } else {
                n_classes = blm_ptr -> get_n_classes();
              }
            } else {
              n_classes = lm_ptr -> get_n_classes();
            }
              //Let the chosen boosting strategy perform the training
              boosting_strategy->perform(trees, fdata_provider, exec_strategy, n_classes);
            }

        /**
        * \brief Include additional samples; Boosted training does not support this.
        *
        * \param originating_tree_id size_t
        *    The tree id of the tree that has the data provider with the added
        *    samples or the samples to remove.
        * \param include_pair include_pair_t
        *    See the documentation of \ref include_pair_t . Contains sample ids
        *    to update and a threshold up to which the samples are left unchanged.
        * \param fdprov \ref IForestDataProvider
        *    The forest data provider to use.
        */
        void include_samples(const size_t &originating_tree_id, const include_pair_t &include_pair, const fdprov_t &fdprov) {
            throw Fertilized_Exception("Boosted training does not support including samples.");
        }

        /**
        * Standard comparison operator.
        *
        * -----
        * Available in:
        * - C++
        * - Python
        * - Matlab
        * .
        *
        * -----
        */
        bool operator==(const ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &rhs) const {
            const auto *rhs_c = dynamic_cast<BoostedTraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> const *>(&rhs);
            if (rhs_c == nullptr)
                return false;
            else
                return *boosting_strategy == *(rhs_c -> boosting_strategy);
        }


    #ifdef SERIALIZATION_ENABLED
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const uint file_version) {
            ar & boost::serialization::base_object<training_t>(*this);
            ar & boosting_strategy;
        }
    #endif

    protected:
        BoostedTraining() {}

    private:
        std::shared_ptr<boost_strat_t> boosting_strategy;
    };
}  // namespace fertilized

#endif // FERTILIZED_TRAININGS_BOOSTEDTRAINING_H_

