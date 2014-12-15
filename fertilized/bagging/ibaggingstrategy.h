/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_BAGGING_IBAGGINGSTRATEGY_H_
#define FERTILIZED_BAGGING_IBAGGINGSTRATEGY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"

namespace fertilized {
  /**
   * Specifies how the samples are distributed amongst the trees.
   *
   * \ingroup fertilizedbaggingGroup
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
  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class IBaggingStrategy {
   public:
     typedef ITraining<input_dtype, feature_dtype, annotation_dtype,
                       leaf_return_dtype, forest_return_dtype> training_t;
     typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;

    virtual ~IBaggingStrategy() {}

    virtual bool provides_validation_data() const VIRTUAL(bool);

    /**
     * action map must contain ids in data_provider counting system for remove
     * actions, and canonic element ids for add actions.
     */
    virtual sample_action_map_t update_data_providers(
      const include_pair_t &sample_ids,
      const size_t &originating_tree_index,
      const fdprov_t &fdprov, training_t *training)
      VIRTUAL(sample_action_map_t);

    virtual usage_map_t get_initial_split(
      const size_t &n_trees, fdprov_t *fdprov)
      VIRTUAL(usage_map_t);

    virtual bool operator==(const IBaggingStrategy<input_dtype, feature_dtype, annotation_dtype,
                              leaf_return_dtype, forest_return_dtype> &rhs)
      const VIRTUAL(bool);


#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    IBaggingStrategy() {}
  };
};  // namespace fertilized
#endif  // FERTILIZED_BAGGING_IBAGGINGSTRATEGY_H_
