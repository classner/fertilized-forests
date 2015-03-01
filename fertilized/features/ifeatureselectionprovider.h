/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_IFEATURESELECTIONPROVIDER_H_
#define FERTILIZED_FEATURES_IFEATURESELECTIONPROVIDER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <unordered_set>
#include <random>
#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../util/sampling.h"
#include "./ifeatureselectiongenerator.h"

namespace fertilized {
  /**
   * \brief The selection provider generates index combination of data
   * dimensions.
   *
   * During the optimization, \f$\phi\f$ may select only a subset of the
   * provided data dimensions. The selection provider may "suggest" many
   * possible such selections during the optimization process.
   *
   * The method \ref register_used must be used after having selected a
   * proposed selection, so that it can be taken into account for the
   * generation of future proposals.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * 
   * -----
   */
  class IFeatureSelectionProvider {
   public:
    virtual ~IFeatureSelectionProvider() {}

    /** \brief Get the dimension of one selection proposal. */
    virtual size_t get_selection_dimension() const VIRTUAL(size_t);

    /** \brief Get a set of all proposals. */
    virtual proposal_set_t get_proposals() VIRTUAL(proposal_set_t);

    /** \brief Get a proposal generator to generate proposals on demand. */
    virtual std::shared_ptr<IFeatureSelectionGenerator> get_proposal_generator()
      VIRTUAL_PTR;

    /** \brief Register a set of proposal vectors as used. Each proposal must
     *  be unique in the set. */
    virtual void register_used(const proposal_set_t &proposals) VIRTUAL_VOID;

    /** Gets the required input dimension. */
    virtual size_t get_input_dimension() const VIRTUAL(size_t);

    /** Deep comparison. */
    virtual bool operator==(const IFeatureSelectionProvider &rhs)
      const VIRTUAL(bool);
      
    /**
     * Get the total number of of available features.
     */
    virtual size_t get_n_available_features() const VIRTUAL(size_t);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    /** \brief Empty constructor. */
    IFeatureSelectionProvider() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(IFeatureSelectionProvider);
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_IFEATURESELECTIONPROVIDER_H_
