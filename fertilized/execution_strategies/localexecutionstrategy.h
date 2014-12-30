/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_EXECUTION_STRATEGIES_LOCALEXECUTIONSTRATEGY_H_
#define FERTILIZED_EXECUTION_STRATEGIES_LOCALEXECUTIONSTRATEGY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <vector>
#include <utility>
#include <memory>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "../global.h"
#include "../types.h"
#include "../trainings/itraining.h"
#include "./iexecutionstrategy.h"
#include "./trainingaction.h"

namespace fertilized {
  /**
   * Executes the training on the local machine.
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
  class LocalExecutionStrategy : public IExecutionStrategy<input_dtype,
    feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> {
   public:
    typedef IExecutionStrategy<input_dtype, feature_dtype, annotation_dtype,
                      leaf_return_dtype, forest_return_dtype> aexec_strat_t;
    using typename aexec_strat_t::forest_t;
    using typename aexec_strat_t::fdprov_t;
    using typename aexec_strat_t::training_t;
    using typename aexec_strat_t::tree_t;
    using typename aexec_strat_t::dprov_t;
    using typename aexec_strat_t::tree_ptr_t;
    using typename aexec_strat_t::tree_ptr_vec_t;
    using typename aexec_strat_t::train_act_t;
    using aexec_strat_t::trees;

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
     * \param num_threads int>0
     *   The number of threads to use for parallelism on forest training level.
     *   Note that this multiplies with the parallelism applied for training
     *   steps, such as for \ref IDecider optimization! Default: 1.
     */
    LocalExecutionStrategy(const int &num_threads=1)
      : num_threads(num_threads) {
      if (num_threads < 1) {
        throw Fertilized_Exception("The number of threads must be >0!");
      }
#ifndef _OPENMP
      if (num_threads > 1) {
        throw Fertilized_Exception("This binary has been built without "
          "OpenMP support! The number of threads must be =1!");
      }
#endif
    }

    /**
     * The abstract method must be called!
     */
    void initialize(
      const std::shared_ptr<fdprov_t> &fdata_provider,
      const std::shared_ptr<tree_ptr_vec_t> &tree_list) {
#ifdef _OPENMP
      // Allow for nested parallelism.
      original_nested_state = omp_get_nested();
      omp_set_nested(true);
#endif

      aexec_strat_t::initialize(fdata_provider, tree_list);
    };

    /** Resets the OpenMP nested state. */
    void cleanup() {
#ifdef _OPENMP
      // Reset OpenMP nested state.
      omp_set_nested(original_nested_state);
#endif
    }

    /**
     * The abstract method must be called at the end!
     */
    void execute_step(const train_act_t &step) {
      switch (step.action) {
      case action_type::BFS:
        if (! (*trees)[ step.tree_id ] -> is_initialized()) {
          (*trees)[ step.tree_id ] -> fit_dprov(step.data_provider.get(), false);
        }
        (*trees)[ step.tree_id ] -> BFS(step.data_provider.get(),
                                        step.completion_level);
        break;
      case action_type::DFS:
        if (! (*trees)[ step.tree_id ] -> is_initialized()) {
          (*trees)[ step.tree_id ] -> fit_dprov(step.data_provider.get(), false);
        }
        (*trees)[ step.tree_id ] -> DFS(step.data_provider.get(),
                                        step.completion_level);
        break;
      default:
        throw Fertilized_Exception("Unknown tree training action.");
      }

      aexec_strat_t::execute_step(step);
    };

    /**
     * The abstract method must be called at the end!
     */
    void execute_steps(const std::vector<train_act_t> &action_storage) {
      #pragma omp parallel for schedule(dynamic) num_threads(num_threads) if(num_threads != 1)
      for (int i = 0; i < action_storage.size(); ++i) {
        const train_act_t &step = action_storage[i];
        switch (step.action) {
        case action_type::BFS:
          if (! (*trees)[ step.tree_id ] -> is_initialized()) {
            (*trees)[ step.tree_id ] -> fit_dprov(step.data_provider.get(), false);
          }
          (*trees)[ step.tree_id ] -> BFS( step.data_provider.get(), step.completion_level);
          break;
        case action_type::DFS:
          if (! (*trees)[ step.tree_id ] -> is_initialized()) {
            (*trees)[ step.tree_id ] -> fit_dprov(step.data_provider.get(), false);
          }
          (*trees)[ step.tree_id ] -> DFS( step.data_provider.get(), step.completion_level);
          break;
        default:
          throw Fertilized_Exception("Unknown tree training action.");
        }
      }

      aexec_strat_t::execute_steps(action_storage);
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<aexec_strat_t>(*this);
      ar & num_threads;
      ar & original_nested_state;
    }
#endif

  private:
    int num_threads;
    int original_nested_state;
  };
}  // namespace fertilized
#endif  // FERTILIZED_EXECUTION_STRATEGIES_LOCALEXECUTIONSTRATEGY_H_