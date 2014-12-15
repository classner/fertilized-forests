/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_TRAININGS_CLASSICTRAINING_H_
#define FERTILIZED_TRAININGS_CLASSICTRAINING_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <memory>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"
#include "../bagging/ibaggingstrategy.h"
#include "../execution_strategies/iexecutionstrategy.h"
#include "../execution_strategies/trainingaction.h"
#include "../data_providers/iforestdataprovider.h"
#include "./itraining.h"

namespace fertilized {
  /**
   * \brief Implements the vanilla decision forest training.
   *
   * Trains all trees independent of each other as allowed by the
   * \ref IExecutionStrategy, possibly exploiting parallelism, etc.
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
   * - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
   * - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
   * - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ClassicTraining
  : public ITraining<input_dtype, feature_dtype, annotation_dtype,
                     leaf_return_dtype, forest_return_dtype> {
   public:
    typedef ITraining<input_dtype, feature_dtype, annotation_dtype,
                      leaf_return_dtype, forest_return_dtype> training_t;
    typedef IBaggingStrategy<input_dtype, feature_dtype, annotation_dtype,
                      leaf_return_dtype, forest_return_dtype> bag_strat_t;
    using typename training_t::forest_t;
    using typename training_t::idec_t;
    using typename training_t::fdprov_t;
    using typename training_t::tree_ptr_vec_t;
    using typename training_t::exec_strat_t;
    typedef TrainingAction<input_dtype, annotation_dtype> train_act_t;
    typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;
    typedef Sample<input_dtype, annotation_dtype> sample_t;

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
    ClassicTraining(const std::shared_ptr<bag_strat_t> &bagging_strategy)
      : bagging_strategy(bagging_strategy) {}

    /** \brief Returns always true. */
    bool check_compatibility(const fdprov_t &prov) const {
      return true;
    };

    /** \brief Returns always true. */
    bool check_compatibility(
      const idec_t &classifier_manager) const {
      return true;
    };

    /**
     * \brief Performs the classical decision tree training.
     *
     * Each tree is trained independent from each other. You can customize
     * the splitting of training data by setting an \ref ISplittingStrategy
     * at construction time.
     */
    void perform(
      const tree_ptr_vec_t &trees,
      fdprov_t *fdata_provider,
      exec_strat_t *exec_strategy) {
      // Create the data providers.
      uint ntrees = static_cast<uint>(trees.size());
      auto usage_map = bagging_strategy ->
        get_initial_split(ntrees, fdata_provider);
      fdata_provider -> create_tree_providers(ntrees, usage_map);

      // Create a list of training actions.
      auto training_steps = std::vector<train_act_t>();
      training_steps.reserve(trees.size());
      for (size_t i = 0; i < trees.size(); ++i) {
        training_steps.push_back(train_act_t(i, CompletionLevel::Complete,
          action_type::DFS, fdata_provider -> dproviders[i]));
      }
      exec_strategy -> execute_steps(training_steps);
    };

    /**
     * \brief Include additional samples according to the selected \ref IBaggingStrategy.
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
    void include_samples(
      const size_t &originating_tree_id,
      const include_pair_t &include_pair,
      const fdprov_t &fdprov) {
      auto action_map = bagging_strategy -> update_data_providers(
        include_pair, originating_tree_id, fdprov, this);
      auto samples = fdprov.get_samples();
      for (const auto &t_aev_pair : action_map) {
        for (const auto &action_ev_pair : t_aev_pair.second) {
          if (action_ev_pair.second.size() == 0) continue;
          switch (action_ev_pair.first) {
          case SampleAction::add_to_training:
            { // Create sample vector.
              std::vector<sample_t> new_samples = std::vector<sample_t>();
              for (const auto &sample_id : action_ev_pair.second) {
                new_samples.push_back((*samples)[ sample_id ]);
              }
              fdprov.dproviders[ t_aev_pair.first ] ->
                add_to_training_set(new_samples);
            }
            break;
          case SampleAction::remove_from_training:
            fdprov.dproviders[ t_aev_pair.first ] -> remove_from_training_set(
              action_ev_pair.second);
            break;
          case SampleAction::add_to_validation:
            { // Create sample vector.
              std::vector<sample_t> new_samples = std::vector<sample_t>();
              for (const auto &sample_id : action_ev_pair.second) {
                new_samples.push_back((*samples)[ sample_id ]);
              }
              fdprov.dproviders[ t_aev_pair.first ] ->
                add_to_validation_set(new_samples);
            }
            break;
          case SampleAction::remove_from_validation:
            fdprov.dproviders[ t_aev_pair.first ] -> remove_from_validation_set(
              action_ev_pair.second);
            break;
          default:
            throw Fertilized_Exception("Unknown dataset modification action.");
          }
        }
      }
    };


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
    bool operator==(const ITraining<input_dtype, feature_dtype, annotation_dtype,
                                      leaf_return_dtype, forest_return_dtype> &rhs)
      const {
      const auto *rhs_c = dynamic_cast<ClassicTraining<input_dtype,
                                                       feature_dtype,
                                                       annotation_dtype,
                                                       leaf_return_dtype,
                                                       forest_return_dtype> const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return *bagging_strategy == *(rhs_c -> bagging_strategy);
    };


#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<training_t>(*this);
      ar & bagging_strategy;
    }
#endif

   protected:
    ClassicTraining() {}

   private:
    std::shared_ptr<bag_strat_t> bagging_strategy;
    // TODO(Christoph): qprune?
  };
};  // namespace fertilized
#endif  // FERTILIZED_TRAININGS_CLASSICTRAINING_H_