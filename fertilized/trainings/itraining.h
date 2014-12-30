/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_TRAININGS_ITRAINING_H_
#define FERTILIZED_TRAININGS_ITRAINING_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <memory>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"

namespace fertilized {
  /**
   * \brief The training interface class.
   *
   * A training encapsulates the steps to produce a decision forest from
   * untrained decision trees. It is specified high-level, yet gives detailed
   * control. For example, a training can specify the bagging of samples,
   * and then do one BFS step for each tree, updating sample weights in
   * between.
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
  class ITraining {
   public:
    typedef Tree<input_dtype, feature_dtype, annotation_dtype,
                 leaf_return_dtype, forest_return_dtype> tree_t;
    typedef Forest<input_dtype, feature_dtype, annotation_dtype,
                   leaf_return_dtype, forest_return_dtype> forest_t;
    typedef IDecider<input_dtype, feature_dtype,
                     annotation_dtype> idec_t;
    typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;
    typedef std::shared_ptr<tree_t> tree_ptr_t;
    typedef std::vector<tree_ptr_t> tree_ptr_vec_t;
    typedef IExecutionStrategy<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> exec_strat_t;

    virtual ~ITraining() {}

    /**
     * \brief Checks the compatibility with a given \ref IForestDataProvider.
     */
    virtual bool check_compatibility(const fdprov_t &prov) const
      VIRTUAL(bool);

    /**
     * \brief Checks the compatibility with a given \ref IDecider.
     */
    virtual bool check_compatibility(
      const idec_t &decider) const
      VIRTUAL(bool);

    /**
     * \brief Performs the training with the trees, data and execution strategy.
     *
     * Returns after the training is complete.
     */
    virtual void perform(
      const tree_ptr_vec_t &trees,
      fdprov_t *fdata_provider,
      exec_strat_t *exec_strategy)
      VIRTUAL_VOID;

    /**
     * \brief Includes additional sample information into the training process.
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
    virtual void include_samples(
      const size_t &originating_tree_id,
      const include_pair_t &include_pair,
      const fdprov_t &fdprov)
      VIRTUAL_VOID;

    // TODO(Christoph): qprune?

    virtual bool operator==(const ITraining<input_dtype, feature_dtype, annotation_dtype,
                                      leaf_return_dtype, forest_return_dtype> &rhs)
      const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    ITraining() {}
  };
};  // namespace fertilized
#endif  // FERTILIZED_TRAININGS_ITRAINING_H_