/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_LEAFS_ILEAFMANAGER_H_
#define FERTILIZED_LEAFS_ILEAFMANAGER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <numeric>
#include <unordered_map>
#include <vector>

#include "../data_providers/idataprovider.h"
#include "../global.h"
#include "../types.h"
#include "../ndarray.h"

namespace fertilized {
  using ndarray::Array;
  using ndarray::ArrayRef;
  /**
   * \brief Stores and returns leaf values, and combines them to forest
   * results.
   *
   * \ingroup fertilizedleafsGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * Instantiations:
   * - int; uint; std::vector<float>; std::vector<float>
   * - float; uint; std::vector<float>; std::vector<float>
   * - double; uint; std::vector<float>; std::vector<float>
   * - uint8_t; uint; std::vector<float>; std::vector<float>
   * - uint8_t; int16_t; std::vector<float>; std::vector<float>
   * - uint8_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
   * - float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
   * - double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
   * .
   * 
   * -----
   */
  template<typename input_dtype, typename annotation_dtype,typename leaf_return_dtype, typename forest_return_dtype>
  class ILeafManager {
   public:
    virtual ~ILeafManager() {}

    typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;
    typedef std::vector<std::pair<leaf_return_dtype, float>> wlresult_list_t;

    /**
     * \brief Checks compatibility with a certain \ref IDataProvider.
     *
     * This method is guaranteed to be called at the beginning of a training.
     */
    virtual bool IsCompatibleWith(const dprov_t &data_provider) const
      VIRTUAL(bool);

    /**
     * \brief Creates a leaf with the specified node_id and data.
     */
    virtual void make_leaf(
      const node_id_t &node_id,
      const elem_id_vec_t &element_list,
      const dprov_t &data_provider) VIRTUAL_VOID;

    /**
     * \brief Gets the leaf data for the leaf with the given id.
     */
    virtual leaf_return_dtype get_result(const node_id_t &node_id,
                                         const input_dtype *data,
                                         const size_t &data_step=1,
                                         const std::function<void(void*)> &dptf = nullptr) const VIRTUAL(leaf_return_dtype);


    virtual forest_return_dtype get_combined_result(
      const wlresult_list_t &leaf_results)
      VIRTUAL(forest_return_dtype);

    virtual bool operator==(const ILeafManager<input_dtype,
                                         annotation_dtype,
                                         leaf_return_dtype,
                                         forest_return_dtype> &rhs)
      const VIRTUAL(bool);

    /** Gets the number of summary dimensions per sample. */
    virtual size_t get_summary_dimensions(const size_t &n_trees) const
      VIRTUAL(size_t);

    /** Creates a summarized result vector from a tree result. */
    // cppcheck-suppress clarifyCondition
    virtual void summarize_tree_result(const leaf_return_dtype &tree_result,
                                       const ArrayRef<double, 1, 1> &result_row)
      const VIRTUAL_VOID;

    /** Creates a summarized vector of summarized results from a forest result. */
    virtual void summarize_forest_result(const forest_return_dtype &forest_result,
                                         const ArrayRef<double, 1, 1> &result_row)
      const VIRTUAL_VOID;

    /** Adds a tree prediction to an image, if supported. */
    // cppcheck-suppress clarifyCondition
    virtual void add_tree_prediction_to_image(const leaf_return_dtype &tree_result,
                                              const Array<float, 2, 2> &result,
                                              const size_t &write_x,
                                              const size_t &write_y,
                                              const float *ratio_parameters)
     const VIRTUAL_VOID;

    /** Adds a forest prediction to a result image, if supported/ */
    virtual void add_forest_prediction_to_image(
      const std::vector<float> &tree_weights,
      const forest_return_dtype &forest_result,
      const Array<float, 2, 2> &result,
      const size_t &write_x,
      const size_t &write_y,
      const float *ratio_parameters)
      const VIRTUAL_VOID;

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    ILeafManager() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(ILeafManager);
  };
};  // namespace fertilized
#endif  // FERTILIZED_LEAFS_ILEAFMANAGER_H_
