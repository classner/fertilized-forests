/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_EXECUTION_STRATEGIES_IEXECUTIONSTRATEGY_H_
#define FERTILIZED_EXECUTION_STRATEGIES_IEXECUTIONSTRATEGY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <vector>
#include <utility>
#include <memory>
#include <set>

#include "../global.h"
#include "../types.h"
#include "../data_providers/iforestdataprovider.h"
#include "../trainings/itraining.h"
#include "../tree.h"
#include "./trainingaction.h"

namespace fertilized {
  /**
   * Specifies a way of executing \ref TrainingAction s.
   *
   * \ingroup fertilizedexecution_strategiesGroup
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
  class IExecutionStrategy {
   public:
    typedef Forest<input_dtype, feature_dtype, annotation_dtype,
                      leaf_return_dtype, forest_return_dtype> forest_t;
    typedef Tree<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> tree_t;
    typedef ITraining<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> training_t;
    typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;
    typedef typename fdprov_t::dprov_t dprov_t;
    typedef std::shared_ptr<tree_t> tree_ptr_t;
    typedef std::vector<tree_ptr_t> tree_ptr_vec_t;
    typedef TrainingAction<input_dtype, annotation_dtype> train_act_t;

    virtual ~IExecutionStrategy() {}

    /**
     * The abstract method must be called at the end!
     */
    virtual void initialize(
      const std::shared_ptr<fdprov_t> &fdata_provider,
      const std::shared_ptr<tree_ptr_vec_t> &tree_list) {
     forest_dprovider = fdata_provider;
     trees = tree_list;
    };

    virtual void cleanup() VIRTUAL_VOID;

    /**
     * The abstract method must be called at the end!
     */
    virtual void execute_step(const train_act_t &step) {
      handle_added_samples(step.tree_id, step.data_provider.get());
    };

    /**
     * The abstract method must be called at the end!
     */
    virtual void execute_steps(const std::vector<train_act_t> &action_storage){
      handle_added_samples(action_storage);
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & forest_dprovider;
      ar & training;
      ar & trees;
    }
#endif

   protected:
    IExecutionStrategy() {}

    void handle_added_samples(const std::vector<train_act_t> &action_storage) {
      // Collect all data providers that were involved in the training.
      auto dprov_ptr_set = std::set<std::shared_ptr<dprov_t>>();
      auto provider_tree_map = std::map<dprov_t*, size_t>();
      for (const auto& act : action_storage) {
        dprov_ptr_set.insert(act.data_provider);
        provider_tree_map[ act.data_provider.get() ] = act.tree_id;
      }
      for (const auto& dprov_ptr : dprov_ptr_set) {
        handle_added_samples(provider_tree_map[ dprov_ptr.get() ], dprov_ptr.get());
      }
    };

    void handle_added_samples(const size_t &tree_id,
                              dprov_t *data_provider) {
      auto added_samples = data_provider -> get_added_samples();
      // Save some time if no steps need to be taken.
      if (added_samples.size() == 0) return;
      auto include_pair = forest_dprovider ->
        include_additional_samples(added_samples);
      training -> include_samples(tree_id, include_pair, *forest_dprovider);
    }

    std::shared_ptr<fdprov_t> forest_dprovider;
    std::shared_ptr<training_t> training;
    std::shared_ptr<tree_ptr_vec_t> trees;
  };

}  // namespace fertilized
#endif  // FERTILIZED_EXECUTION_STRATEGIES_IEXECUTIONSTRATEGY_H_