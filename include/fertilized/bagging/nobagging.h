/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_BAGGING_NOBAGGING_H_
#define FERTILIZED_BAGGING_NOBAGGING_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "../data_providers/iforestdataprovider.h"
#include "./ibaggingstrategy.h"

namespace fertilized {
  /**
   * As the name suggests, performs no bagging and uses all samples for all trees.
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
  class NoBagging
  : public IBaggingStrategy <input_dtype, feature_dtype, annotation_dtype,
                               leaf_return_dtype, forest_return_dtype> {
   public:
    typedef IBaggingStrategy <input_dtype, feature_dtype, annotation_dtype,
      leaf_return_dtype, forest_return_dtype> split_strat_t;
    using typename split_strat_t::training_t;
    using typename split_strat_t::fdprov_t;

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
    NoBagging() {}

    /** Returns false. */
    bool provides_validation_data() const { return false; };

    /** Throws. */
    sample_action_map_t update_data_providers(
      const include_pair_t &sample_ids,
      const size_t &originating_tree_index,
      const fdprov_t &fdprov, training_t *training) {
      // TODO(Christoph): complete.
      throw Fertilized_Exception("Not implemented yet.");
    };

    /** Returns all samples for all trees. */
    usage_map_t get_initial_split(const size_t &n_trees, fdprov_t *fdprov) {
      if (n_trees < 2)
        throw Fertilized_Exception("Split must be determined for > 1 tree.");
      auto sample_list_ptr = fdprov -> get_samples();
      size_t n_samples = sample_list_ptr -> size();
      usage_map_t usage_map = usage_map_t();

      for (size_t tree_id = 0 ; tree_id < n_trees; ++tree_id) {
        auto tr_vec = std::make_shared<std::vector<size_t>>();
        auto val_vec = std::make_shared<std::vector<size_t>>();
        usage_map.emplace_back(tr_vec, val_vec);
      }

      for (size_t curr_tree_id = 0; curr_tree_id < n_trees; ++curr_tree_id) {
        usage_map[curr_tree_id].first -> resize(n_samples);
        std::iota(usage_map[curr_tree_id].first -> begin(),
                  usage_map[curr_tree_id].first -> end(), 0);
      }
      return usage_map;
    };

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
    bool operator==(const IBaggingStrategy<input_dtype, feature_dtype, annotation_dtype,
                              leaf_return_dtype, forest_return_dtype> &rhs)
      const {
      const auto *rhs_c = dynamic_cast<NoBagging<input_dtype,
                                                 feature_dtype,
                                                 annotation_dtype,
                                                 leaf_return_dtype,
                                                 forest_return_dtype> const *>(&rhs);
      return rhs_c != nullptr;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<split_strat_t>(*this);
    }
#endif
  };
};  // namespace fertilized
#endif  // FERTILIZED_BAGGING_NOBAGGING_H_