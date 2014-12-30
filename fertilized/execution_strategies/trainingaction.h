/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_EXECUTION_STRATEGIES_TRAININGACTION_H_
#define FERTILIZED_EXECUTION_STRATEGIES_TRAININGACTION_H_

#include <memory>

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"

namespace fertilized {
  /**
   * Represents one training action.
   *
   * -----
   * Available in:
   * - C++
   * .
   * Instantiations:
   * - int; uint
   * - float; uint
   * - double; uint
   * - uint8_t; uint
   * - uint8_t; int16_t
   * - float; float
   * - double; double
   * .
   *
   * -----
   */
  template<typename input_dtype, typename annotation_dtype>
  struct TrainingAction {
    typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;
    const size_t tree_id;
    const CompletionLevel completion_level;
    const action_type action;
    const std::shared_ptr<dprov_t> data_provider;

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
     * \param tree_id size_t
     *   The tree to execute the action on.
     * \param completeness CompletionLevel
     *   How complete the action should be executed.
     * \param action action_type
     *   The action type.
     * \param data_provider shared(IDataProvider)
     *   The data provider to use.
     */
    TrainingAction(const size_t &tree_id,
                   const CompletionLevel &completeness,
                   const action_type &action,
                   const std::shared_ptr<dprov_t> &data_provider)
     : tree_id(tree_id), completion_level(completeness), action(action),
       data_provider(data_provider) {
    };
  };
}  // namespace fertilized
#endif  // FERTILIZED_EXECUTION_STRATEGIES_TRAININGACTION_H_