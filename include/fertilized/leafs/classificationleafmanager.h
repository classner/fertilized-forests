/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_LEAFS_CLASSIFICATIONLEAFMANAGER_H_
#define FERTILIZED_LEAFS_CLASSIFICATIONLEAFMANAGER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <numeric>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../features/isurfacecalculator.h"
#include "./ileafmanager.h"

namespace fertilized {
  /**
   * \brief Stores the probability distributions for n_classes at a leaf.
   *
   * \ingroup fertilizedleafsGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int; uint
   * - float; uint
   * - double; uint
   * - uint8_t; uint
   * - uint8_t; int16_t
   * .
   * 
   * -----
   */
  template<typename input_dtype, typename annotation_dtype>
  class ClassificationLeafManager
    : public ILeafManager<input_dtype, annotation_dtype,
                          std::vector<float>, std::vector<float>> {
   public:
    typedef ILeafManager<input_dtype, annotation_dtype,
                         std::vector<float>, std::vector<float>> leaf_man_t;
    using typename leaf_man_t::dprov_t;
    using typename leaf_man_t::wlresult_list_t;

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
     * \param n_classes uint>1
     *   The number of classes.
     */
    explicit ClassificationLeafManager(const uint &n_classes)
    : n_classes(n_classes)
    , distribution_map(std::unordered_map<node_id_t, std::vector<float>>()) {
      if (n_classes < 2) {
        throw Fertilized_Exception("The number of classes must be >1!");
      }
    }

    /**
     * \brief Creates and stores a probability distribution over the n_classes
     * at this leaf.
     */
    void make_leaf(
        const node_id_t &node_id,
        const elem_id_vec_t &element_list,
        const dprov_t &data_provider) {
      FASSERT(element_list.size() > 0);
      // Create the probability distribution at this leaf.
      std::vector<float> distribution(n_classes);
      float total = static_cast<float>(element_list.size());
      auto sample_list_ref = data_provider.get_samples();

      for (const auto &element_id : element_list) {
        distribution[ static_cast<const size_t>(*(*sample_list_ref)[ element_id ].annotation) ] += 1.f;
      }
      FASSERT(total > 0.f);
      // Normalize with the total count.
      for (auto &count : distribution) {
        count /= total;
      }

      auto ret_val = distribution_map.emplace(node_id, std::move(distribution));
      if (!ret_val.second) {
        throw Fertilized_Exception("Tried to create the leaf value for a node "
          "that has already been assigned one.");
      }
    };

    /**
     * \brief Returns true for all \ref IDataProvider s with the appropriate
     * type. It DOES NOT check whether all annotations are in the correct
     * range.
     */
    bool IsCompatibleWith(const dprov_t &data_provider) const  {
      auto sample_list_ptr = data_provider.get_samples();
      for (const auto &sample_ptr : *sample_list_ptr) {
        if (! (sample_ptr.annotation[0] >= 0 &&
               sample_ptr.annotation[0] < this -> n_classes)) {
            throw Fertilized_Exception("The annotations for classification "
              "must be in [0; n_classes)!");
        }
      }
      return true;
    };

    /** \brief Gets the class probability distribution. */
    std::vector<float> get_result(const node_id_t &node_id,
                                  const input_dtype *data,
                                  const size_t &data_step=1,
                                  const std::function<void(void*)> &dptf = nullptr) const {
      return distribution_map.at( node_id );
    };

    /** Gets the mean of results. */
    std::vector<float> get_combined_result(
      const wlresult_list_t &leaf_results) {
      float weight_sum = 0.f;
      std::vector<float> combined_result(n_classes);
      for (const auto &res_w_pair : leaf_results) {
        for (size_t binindex = 0;
             binindex < static_cast<size_t>(n_classes); ++binindex) {
          combined_result[binindex] += res_w_pair.first[ binindex ] * res_w_pair.second;
        }
        weight_sum += res_w_pair.second;
      }
      for (size_t binindex = 0;
           binindex < static_cast<size_t>(n_classes); ++binindex)
        combined_result[binindex] /= weight_sum;
      return combined_result;
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
    bool operator==(const ILeafManager<input_dtype,
                                 annotation_dtype,
                                 std::vector<float>,
                                 std::vector<float>> &rhs) const {
      const auto *rhs_c = dynamic_cast<ClassificationLeafManager<input_dtype,
                                                                 annotation_dtype> const*>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return n_classes == rhs_c -> n_classes &&
               distribution_map == rhs_c -> distribution_map;
    };

    /** Returns the number of classes. */
    size_t get_summary_dimensions(const size_t &n_trees) const {
      return static_cast<size_t>(n_classes);
    };

    /** Copies the tree result. */
    void summarize_tree_result(const std::vector<float> &tree_result,
                               const ArrayRef<double, 1, 1> &result_row)
      const {
      std::copy(tree_result.begin(), tree_result.end(), result_row.getData());
    };

    /** Copies the forest result. */
    void summarize_forest_result(const std::vector<float> &forest_result,
                                 const ArrayRef<double, 1, 1> &result_row)
      const {
      std::copy(forest_result.begin(), forest_result.end(), result_row.getData());
    };

    /** Sets the probability for the selected pixel. */
    void add_tree_prediction_to_image(const std::vector<float> &tree_result,
                                      const Array<float, 2, 2> &result,
                                      const size_t &write_x,
                                      const size_t &write_y,
                                      const float *ratio_parameters) const {
      // Interpret as foreground probability.
      result[write_y][write_x] = tree_result[1];
    };

    /** Sets the mean probability for the selected pixel. */
    void add_forest_prediction_to_image(
      const std::vector<float> &tree_weights,
      const std::vector<float> &forest_result,
      const Array<float, 2, 2> &result,
      const size_t &write_x,
      const size_t &write_y,
      const float *ratio_parameters) const {
      // Interpret as foreground probability.
      result[write_y][write_x] = forest_result[1];
    };
    
    /** Gets the number of classes. */
    unsigned int get_n_classes() const {
      return n_classes;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<leaf_man_t>(*this);
      ar & n_classes;
      ar & distribution_map;
    }
#endif

   protected:
    ClassificationLeafManager() {}

   private:
    uint n_classes;
    std::unordered_map<node_id_t, std::vector<float>> distribution_map;
  };
};  // namespace fertilized
#endif  // FERTILIZED_LEAFS_CLASSIFICATIONLEAFMANAGER_H_

