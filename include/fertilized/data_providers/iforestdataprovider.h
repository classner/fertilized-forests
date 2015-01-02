/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_IFORESTDATAPROVIDER_H_
#define FERTILIZED_DATA_PROVIDERS_IFORESTDATAPROVIDER_H_

#include <memory>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "./idataprovider.h"

namespace fertilized {
  /**
   * \brief The data provider interface for a decision forest.
   *
   *
   * \ingroup fertilizeddata_providersGroup
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
  template<typename input_dtype, typename annotation_dtype>
  class IForestDataProvider {
   public:
    typedef IDataProvider<input_dtype, annotation_dtype> dprov_t;
    typedef typename dprov_t::sample_t sample_t;
    typedef typename dprov_t::sample_list_t sample_list_t;

    virtual ~IForestDataProvider() {}

    /**
     * Include additional sample in the training set.
     *
     * This is an interface function for a planned functionality that is not
     * yet implemented.
     */
    virtual include_pair_t include_additional_samples(
      const sample_list_t &samples)
      VIRTUAL(include_pair_t);

    /**
     * \brief Creates the data providers for each tree from the specified
     *        usage map.
     *
     * \param n How many data providers (trees) are needed.
     * \param usage_map A vector with a pair of sample_id lists. Each vector
     *    element is for one tree. It contains a pair of training ids and
     *    validation ids of the samples to use.
     */
    virtual void create_tree_providers(
      const size_t &n,
      const usage_map_t &usage_map) VIRTUAL_VOID;

    /**
     * Gets all samples.
     */
    virtual std::shared_ptr<const sample_list_t> get_samples() const
      VIRTUAL_PTR;

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & dproviders;
      ar & sample_ids;
    }
#endif

    /**
     * \brief A vector of data providers. 
     *
     * Initialized after \ref create_tree_providers has been used.
     */
    std::vector<std::shared_ptr<dprov_t>> dproviders;
    /** A vector of all sample ids. */
    std::vector<element_id_t> sample_ids;

   protected:
    IForestDataProvider() {}
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_IFORESTDATAPROVIDER_H_
