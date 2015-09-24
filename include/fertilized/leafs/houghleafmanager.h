/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_LEAFS_HOUGHLEAFMANAGER_H_
#define FERTILIZED_LEAFS_HOUGHLEAFMANAGER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <numeric>
#include <unordered_map>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../features/isurfacecalculator.h"
#include "./ileafmanager.h"

namespace fertilized {
  /** Utility function for adding Hough forest result vectors to an image. */
  template <typename annotation_dtype>
  inline void __add_hough_offs(const std::shared_ptr<std::vector<annotation_dtype>> offs,
                               const float &proba,
                               float *result,
                               const size_t &pos_x,
                               const size_t &pos_y,
                               const size_t &shape_y,
                               const size_t &shape_x,
                               const float *ratios) {
    if (offs -> size() == 0)
      return;
    FASSERT(offs -> size() % 2 == 0);
    const float &ratio = (ratios ? ratios[0] : 1.f);
    const float &ratio_x = (ratios ? ratios[2] : 1.f);
    const float &ratio_y = (ratios ? ratios[3] : 1.f);
    size_t py, px;
    const annotation_dtype *off_ptr = &(*offs)[0];
    // Add the offset vectors to the image.
    for (size_t offset_index = 0; offset_index < offs -> size() / 2; ++offset_index){
      px = pos_x + static_cast<size_t>(static_cast<float>(*(off_ptr++)) * ratio * ratio_x + 0.5f);
      py = pos_y + static_cast<size_t>(static_cast<float>(*(off_ptr++)) * ratio_y + 0.5f);
      if (py >= 0 && py < shape_y &&
          px >= 0 && px < shape_x)
        result[ py * shape_x +
                px ] += proba;
    }
  };

  /**
   * \brief Stores the offset vectors for positive samples and their
   * probabilities in the leafs.
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
   * - uint8_t; int16_t
   * .
   *
   * -----
   */
  template<typename input_dtype, typename annotation_dtype>
  class HoughLeafManager
    : public ILeafManager<input_dtype, annotation_dtype,
                          std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                          std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>> {
   public:
    typedef ILeafManager<input_dtype, annotation_dtype,
                         std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                         std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>> leaf_man_t;
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
     *   The number of classes. Currently only 2 are supported. Default: 2.
     * \param annot_dim size_t>0
     *   The number of offset dimensions. Default: 2.
     */
    explicit HoughLeafManager(
      const uint &n_classes=2,
      const size_t &annot_dim=2)
    : n_classes(n_classes), annot_dim(annot_dim)
    , distribution_map(std::unordered_map<node_id_t,
       std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>()) {
      if (n_classes != 2) {
        throw Fertilized_Exception("The HoughLeaf Manager currently only supports "
          "two classes!");
      }
      if (annot_dim == 0) {
        throw Fertilized_Exception("The number of annotation dimensions should "
          "be greater 0!");
      }
    }

    /**
     * \brief Creates and stores the offset vectors and pos probability.
     */
    void make_leaf(
        const node_id_t &node_id,
        const elem_id_vec_t &element_list,
        const dprov_t &data_provider) {
      // Create the probability distribution at this leaf.
      // Currently assume there are only two classes.
      FASSERT(element_list.size() > 0);
      auto offset_coordinates = std::make_shared<std::vector<annotation_dtype>>();
      float total = static_cast<float>(element_list.size());
      auto sample_list_ref = data_provider.get_samples();
      float n_pos = 0.f;
      FASSERT(annot_dim+1 == data_provider.get_annot_vec_dim());
      const annotation_dtype *annot;
      for (const auto &element_id : element_list) {
        annot = (*sample_list_ref)[ element_id ].annotation;
        n_pos += (*annot == 0) ? 0.f : 1.f;
        if (*(annot++) != 0)
          for (size_t i = 0; i < annot_dim; ++i)
            offset_coordinates -> push_back(*(annot++));
      }

      // Note: if this should be implemented for more than one 'positive'
      // class, normalize the probability also by the number of classes
      // (see code by Juergen Gall).
      auto ret_val = distribution_map.emplace(node_id,
                                              std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>(
                                                        n_pos/total,
                                                        offset_coordinates));
      if (!ret_val.second) {
        throw Fertilized_Exception("Tried to create the leaf value for a node "
          "that has already been assigned one.");
      }
    };

    /**
     * \brief Returns true for all \ref IDataProvider s if the annotation
     * dimension is greater than one (offsets are stored).
     */
    bool IsCompatibleWith(const dprov_t &data_provider) const  {
      return (data_provider.get_annot_vec_dim() > 1);
    };

    /** \brief Gets the probability and offset vectors. */
    std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>> get_result(const node_id_t &node_id,
                                                                      const input_dtype *data,
                                                                      const size_t &data_step=1,
                                                                      const std::function<void(void*)> &dptf = nullptr) const {
      return distribution_map.at( node_id );
    };

    /** Returns a vector of pairs with the tree prediction probability and the offset vectors per tree. */
    std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> get_combined_result(
      const wlresult_list_t &leaf_results) {
      std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> comb_vec(0);
      for (size_t resindex = 0; resindex < leaf_results.size(); ++resindex) {
        const std::pair<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>, float> *res_w_pair = &leaf_results[resindex];
        comb_vec.emplace_back(res_w_pair -> first.first,
                              res_w_pair -> first.second);
      }

      return comb_vec;
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
                                 std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                                 std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>> &rhs) const {
      const auto *rhs_c = dynamic_cast<HoughLeafManager<input_dtype,
                                                        annotation_dtype> const*>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else {
        bool vectors_equal = true;
        for (const auto &kvp : distribution_map) {
          if (kvp.second.first != rhs_c -> distribution_map.at(kvp.first).first ||
              (*((kvp.second).second)) != (*((rhs_c -> distribution_map.at(kvp.first)).second))) {
            vectors_equal = false;
            break;
          }
        }
        return n_classes == rhs_c -> n_classes &&
               vectors_equal &&
               annot_dim == rhs_c -> annot_dim;
      }
    };

    /** Throws. */
    size_t get_summary_dimensions(const size_t &n_trees) const {
      throw Fertilized_Exception("Can not get a fixed summary for a hough "
        "forest! This prohibits the use of the standard 'predict' method. "
        "Use the 'predict_image' method instead.");
    };

    /** Throws. */
    void summarize_tree_result(const std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>> &tree_result,
                               const ArrayRef<double, 1, 1> &result_row)
      const {
      throw Fertilized_Exception("Can not get a fixed summary for a hough "
        "forest! This prohibits the use of the standard 'predict' method. "
        "Use the 'predict_image' method instead.");
    };

    /** Throws. */
    void summarize_forest_result(const std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> &forest_result,
                                 const ArrayRef<double, 1, 1> &result_row)
      const {
      throw Fertilized_Exception("Can not get a fixed summary for a hough "
        "forest! This prohibits the use of the standard 'predict' method. "
        "Use the 'predict_image' method instead.");
    };

    /** Adds the hough offsets to an image. */
    void add_tree_prediction_to_image(const std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>> &prediction_pair,
                                      const Array<float, 2, 2> &result,
                                      const size_t &write_x,
                                      const size_t &write_y,
                                      const float *ratio_parameters)
     const {
      if (prediction_pair.first > ratio_parameters[1]) {
        float weight = prediction_pair.first /
              static_cast<float>(prediction_pair.second -> size());
        __add_hough_offs(prediction_pair.second,
                         weight,
                         result.getData(),
                         write_x,
                         write_y,
                         static_cast<size_t>(result.getSize<0>()),
                         static_cast<size_t>(result.getSize<1>()),
                         ratio_parameters);
      }
    };

    /** Adds the hough offsets to an image. */
    void add_forest_prediction_to_image(
      const std::vector<float> &tree_weights,
      const std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> &forest_result,
      const Array<float, 2, 2> &result,
      const size_t &write_x,
      const size_t &write_y,
      const float *ratio_parameters)
      const {
      // Accumulate the probabilities.
      // For each offset vector, add the dirac-measured weight, scaled by the
      // number of trees (see HoughForestPaper-PAMI, p.5).
      const float weight_sum = std::accumulate(tree_weights.begin(),
                                               tree_weights.end(), 0.f);
      size_t tree_index = 0;
      for (const auto &prediction_pair : forest_result) {
        // Do the trick of Juergen Gall to speed up detection and only add
        // vectors for which the determined object probability > min_prob_threshold.
        if (prediction_pair.first > ratio_parameters[1]) {
          float weight = (prediction_pair.first * tree_weights[tree_index]) /
           (static_cast<float>(prediction_pair.second -> size()) * weight_sum);
          __add_hough_offs(prediction_pair.second,
                           weight,
                           result.getData(),
                           write_x,
                           write_y,
                           static_cast<size_t>(result.getSize<0>()),
                           static_cast<size_t>(result.getSize<1>()),
                           ratio_parameters);
        }
        tree_index++;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<leaf_man_t>(*this);
      ar & n_classes;
      ar & distribution_map;
      ar & annot_dim;
    }
#endif

    /** Returns the annotation dimension as set in the constructor. */
    size_t get_annot_dim() const {
      return annot_dim;
    }

   //protected:
    //HoughLeafManager() {}

   private:
    uint n_classes;
    size_t annot_dim;
    std::unordered_map<node_id_t, std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> distribution_map;
  };
};  // namespace fertilized
#endif  // FERTILIZED_LEAFS_HOUGHLEAFMANAGER_H_
