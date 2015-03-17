/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_IDATAPROVIDER_H_
#define FERTILIZED_DATA_PROVIDERS_IDATAPROVIDER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <functional>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "./sample.h"

namespace fertilized {
  /**
   * \brief The data provider for the training of one tree.
   *
   * \ingroup fertilizeddata_providersGroup
   *
   * Data providers work with \ref Samples and sample ids. They are allowed to
   * add additional samples during training on the fly. The method
   * \ref optimize_set_for_node is called before a classifier is fitted for
   * a decision node, so that the data provider can alter the set of samples
   * that are used.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float; uint
   * - int; uint
   * - uint8_t; uint
   * - uint8_t; int16_t
   * - double; uint
   * - double; double
   * - float; float
   * .
   * 
   * -----
   */
  template <typename input_dtype, typename annotation_dtype>
  class IDataProvider {
   public:
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_list_t;

    virtual ~IDataProvider() {};

    /**
      * \brief Optimizes a sample set.
      *
      * This method is called before classifier optimization at every node.
      *
      * \param node_id The current nodes id.
      * \param depth The node's depth.
      * \param element_list The id list of all elements that arrive at the
      *                     node.
      * \param node_predictor A function that takes a sample and returns the
      *                       node id of the node in the current tree at which
      *                       the sample would arrive.
      *                       
      */
    virtual void optimize_set_for_node(
      const node_id_t &node_id,
      const uint &depth,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)>
                                      node_predictor,
      std::shared_ptr<elem_id_vec_t> &element_list) VIRTUAL_VOID;

    /**
      * \brief Get a sample id list of samples for the root node.
      */
    virtual std::shared_ptr<const elem_id_vec_t> get_initial_sample_list() const
      VIRTUAL_PTR;

    /**
      * \brief Get all samples.
      */
    virtual std::shared_ptr<const sample_list_t> get_samples() const
      VIRTUAL_PTR;

     /**
      * \brief Get the validation set sample ids.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual std::shared_ptr<const elem_id_vec_t> get_validation_sample_list()
      const VIRTUAL_PTR;

    /**
      * \brief Get a list of all samples added to the sample pool since this
      * method was last called.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual const std::vector<sample_t> get_added_samples()
      VIRTUAL(std::vector<sample_t>);

    /**
      * \brief Add the specified samples to the training set.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual void add_to_training_set(const std::vector<sample_t> &samples)
      VIRTUAL_VOID;

    /**
      * \brief Remove the specified samples from the training set.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual void remove_from_training_set(
      const std::vector<element_id_t> &sample_ids)
      VIRTUAL_VOID;

    /**
      * \brief Add the specified samples to the validation set.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual void add_to_validation_set(const std::vector<sample_t> &samples)
      VIRTUAL_VOID;

    /**
      * \brief Remove the specified samples from the validation set.
      *
      * This is an interface function for a planned functionality that is not
      * yet implemented.
      */
    virtual void remove_from_validation_set(
      const std::vector<element_id_t> &sample_ids)
      VIRTUAL_VOID;

    /**
     * \brief Some data providers might need this method to do cleanup actions
     * for efficient sample data management.
     */
    virtual void track_child_nodes(node_id_t node_id,
      node_id_t left_id, node_id_t right_id) VIRTUAL_VOID;

    /**
     * \brief Returns one feature vector dimension.
     */
    const size_t get_feat_vec_dim() const { return feat_vec_dim; }

    /**
     * \brief Returns one annotation vector dimension.
     */
    const size_t get_annot_vec_dim() const {return annot_vec_dim; }

    /** 
     * \brief Returns a coordinate transformation function for the dimension
     * selectors.
     *
     * The transformation is applied to the positions before the data is
     * extracted and passed to the IFeatureCalculator. If not overridden,
     * returns the nullptr (no transformation).
     */
    virtual std::function<void(void*)> get_decision_transf_func(
                                                         const element_id_t &)
      const {
      return nullptr;
    }

    /**
     * \brief Gives the data provider the opportunity to load all samples
     * to construct a leaf.
     *
     * This method is especially important for the subsampling data providers:
     * only a certain amount of samples is used to find a good split, but
     * if the result is a leaf node, ALL samples should be used to create
     * a good leaf estimate.
     */
    virtual void load_samples_for_leaf(const node_id_t &node_id,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)>
                                        node_predictor,
        elem_id_vec_t *element_list) {}

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & feat_vec_dim;
      ar & annot_vec_dim;
    }
#endif

   protected:
    explicit IDataProvider(const size_t &feature_dimension,
                           const size_t &annotation_dimension)
      : feat_vec_dim(feature_dimension), annot_vec_dim(annotation_dimension) {}
    // cppcheck-suppress uninitVar
    IDataProvider() {}

    /** \brief The dimension of one sample vector. */
    size_t feat_vec_dim;
    size_t annot_vec_dim;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_IDATAPROVIDER_H_
