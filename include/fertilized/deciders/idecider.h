/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DECIDERS_IDECIDER_H_
#define FERTILIZED_DECIDERS_IDECIDER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <unordered_map>
#include <mutex>
#include <utility>
#include <vector>
#include <limits>
#include <typeinfo>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../ndarray.h"

namespace fertilized {
  /**
   * \brief Interface for the decider. It does the
   * optimization of the deciding classifier for each node and stores the
   * parameters.
   *
   * \param input_dtype The datatype of the data to classify.
   * \param annotation_dtype The datatype of the annotations.
   * \param feature_dtype The datatype in which features are calculated.
   *
   * \ingroup fertilizeddecidersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * Instantiations:
   * - int; int; uint
   * - uint8_t; uint8_t; uint
   * - uint8_t; int16_t; uint
   * - float; float; uint
   * - double; double; uint
   * - uint8_t; int16_t; int16_t
   * - float; float; float
   * - double; double; double
   * .
   * 
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IDecider {
   public:
    /** \brief Standard virtual interface destructor. */
    virtual ~IDecider() {};

    typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;

    /**
     * \brief Optimizes a classifier for the given data and stores the params.
     *
     * This method must either set make_to_leaf to true or assure that at least
     * the minimum amount of samples per leaf is contained in each of
     * element_list_left and element_list_right. In the case that make_leaf
     * is true, the list pointers may even be returned uninitialized.
     *
     * If it is necessary to enforce additional growing constraints for the
     * tree, this is the right place (e.g. have a minimum number of samples
     * per node). The classifier manager can take these constraints into
     * account and may return make_to_leaf accordingly.
     *
     * \param node_id The node id of the node for which the classifier should
     *                be optimized. The parameters must be stored for the id.
     * \param node_depth The depth of the node in the tree. The root has
     *                depth 0.
     * \param min_samples_at_leaf The minimum number of samples at a leaf.
     *                This information can be used during the optimization.
     * \param element_id_list The ids of the samples arriving at this node.
     * \param data_provider The data provider from which the samples can be
     *                      loaded.
     * \param make_to_leaf If the optimization does not find a sufficiently
     *                     good split that all growing criteria are fulfilled,
     *                     the node must be converted to a leaf by the caller.
     * \param element_list_left The ids of the elements the classifier
     *                          sends to the left. Only must be initialized if
     *                          make_to_leaf is false.
     * \param element_list_right The ids of the elements the classifier sends
     *                           to the right. Only must be initialized if
     *                           make_to_leaf is false.
     */
    virtual void optimize_and_set_for_node(
      const node_id_t &node_id,
      const uint &node_depth,
      const uint &min_samples_at_leaf,
      const elem_id_vec_t &element_id_list,
      const dprov_t &data_provider,
      bool *make_to_leaf,
      std::shared_ptr<elem_id_vec_t> *element_list_left,
      std::shared_ptr<elem_id_vec_t> *element_list_right) VIRTUAL_VOID;

    /**
     * \brief Makes a decision for a node with already optimized parameters.
     *
     * The classifier parameters must have been optimized for the node_id
     * before this method is called.
     *
     * \param node_id The node id of the node for which the decision should
     *                be made.
     * \param data The input data.
     * \return true, if the decision goes to left, false otherwise.
     */
    virtual bool decide(
      const node_id_t &node_id,
      const input_dtype *data,
      const size_t &data_step,
      const std::function<void(void*)> &decision_param_transf = nullptr)
     const VIRTUAL(bool);

    /**
     * \brief Whether this classifier manager supports sample weights
     * during training.
     */
    virtual bool supports_weights() const VIRTUAL(bool);

    /** Gets the input dimension of the feature selection provider. */
    virtual size_t get_required_num_data_dim() const VIRTUAL(size_t);
    
    /**
     * \brief Computes a feature importance vector.
     * 
     * The vector is normalized to sum to 1.0. It contains the relative
     * frequencies of the feature occurences. Its length is the number
     * of available features.
     */
    virtual Array<double, 1, 1> compute_feature_importances() const = 0;

    virtual bool operator==(const IDecider &rhs) const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    /** 
     * \brief Empty constructor to allow inheritance though
     * DISALLOW_COPY_AND_ASSIGN is applied.
     */
    IDecider() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(IDecider);
  };

}  // namespace fertilized
#endif  // FERTILIZED_DECIDERS_IDECIDER_H_
