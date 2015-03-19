/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONPROVIDER_H_
#define FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONPROVIDER_H_

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
#include "./ifeatureselectionprovider.h"
#include "./ifeatureselectiongenerator.h"
#include "./volumefeatureselectiongenerator.h"

namespace fertilized {
  /**
   * \brief This selection provider generates random selection combinations
   * from a 3D feature volume.
   *
   * It may be seeded for reproducible results.
   *
   *
   * \ingroup fertilizedfeaturesGroup
   *   
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   *
   * -----
   */
  class VolumeFeatureSelectionProvider
    : public IFeatureSelectionProvider {
   public:
    /**
     * \brief Standard constructor.
     *
     * Additional constraints on the methods arguments apply to guarantee good
     * random selection speed:
     * \f[{{how\_many\_available}\choose{selection\_dimension}}\ge
     * n\_selections\_per\_node\cdot 2,\f]
     * \f[{{max\_to\_use}\choose{selection\_dimension}}\ge
     * n\_selections\_per\_node\cdot 2.\f]
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param selection_dimension size_t>0
     *   How many data dimensions are selected per
     *   proposal. Must be > 0 and <= size_x*size_y*size_z.
     * \param size_x size_t>0
     *   Horizontal patch size.
     * \param size_y size_t>0
     *   Vertical patch size.
     * \param size_z size_t>0
     *   Patch depth.
     * \param how_many_per_node size_t>0
     *   How many selection proposals are created for each node.
     * \param random_seed A random seed for the random number generator. Must
     *            be greater than 0.
     */
    VolumeFeatureSelectionProvider(
          const size_t &selection_dimension,
          const size_t &size_x,
          const size_t &size_y,
          const size_t &size_z,
          const size_t &how_many_per_node,
          const uint &random_seed = 1)
      : dimension(selection_dimension),
        how_many_per_node(how_many_per_node),
        size_x(size_x), size_y(size_y), size_z(size_z),
        random_engine(std::make_shared<std::mt19937>(random_seed)) {
      // TODO(Christoph): Remove max_to_use option for large speed gain.
      // Sanity checks.
      if (dimension == 0)
        throw Fertilized_Exception("The number of selected dimensions per "
         "proposal by the features selector must be greater 0!");
      if (dimension > size_x * size_y * size_z)
        throw Fertilized_Exception("The number of available features must "
         "be greater than the number of features to select for one proposal!");
      int64_t combinations = ibinom(
        static_cast<int>(size_x * size_y * size_z),
        static_cast<int>(dimension));
      if ((combinations < static_cast<int64_t>(how_many_per_node) * 2 &&
           combinations != -1) &&  // -1: Overflow detected: a LOT of comb.s ;)
          dimension != 1 ||
          dimension == 1 && how_many_per_node > size_x * size_y * size_z) {
        throw Fertilized_Exception("The standard feature selection "
          "provider has been initialized wrongly. In the "
          "case of n data features and k to choose per node being less "
          "than how many samples per node to provide / 2, "
          "the provided algorithm might be very slow!");
      }
      if (how_many_per_node == 0) {
        throw Fertilized_Exception("The number of selections per node must be>0.");
      }
    };

    /** Returns size_x*size_y*size_z. */
    size_t get_input_dimension() const {
      return size_x * size_y * size_z;
    };

    /** \brief See \ref IFeatureSelectionProvider::get_selection_dimension. */
    size_t get_selection_dimension() const {
      return dimension;
    };

    /** Returns the \ref VolumeFeatureSelectionGenerator used. */
    std::shared_ptr<IFeatureSelectionGenerator> get_proposal_generator() {
      return std::shared_ptr<VolumeFeatureSelectionGenerator>(
        new VolumeFeatureSelectionGenerator(
          dimension, size_x, size_y, size_z,
          how_many_per_node, random_engine));
    };

    /**
     * \brief Generate a set of proposals.
     *
     * The generation is done by randomly creating new proposal sets. Each
     * proposed selection is unique in its set.
     */
    proposal_set_t get_proposals() {
      auto gen = get_proposal_generator();
      // Generate the selections.
      auto ret_set = proposal_set_t();
      ret_set.reserve(how_many_per_node);

      for (uint i = 0; i < how_many_per_node; ++i) {
        ret_set.emplace(gen -> get_next());
      }

      return ret_set;
    };

    /**
     * \brief Registers the given proposals as used.
     */
    void register_used(const proposal_set_t &proposals) {}

    /**
     * ----- 
     * Available in:
     * - C+_
     * - Python
     * - Matlab
     * .
     * 
     * -----
     */
    bool operator==(const IFeatureSelectionProvider &rhs)
      const {
      const auto *rhs_c = dynamic_cast<VolumeFeatureSelectionProvider const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return dimension == rhs_c -> dimension &&
               how_many_per_node == rhs_c -> how_many_per_node &&
               size_x == rhs_c -> size_x &&
               size_y == rhs_c -> size_y &&
               size_z == rhs_c -> size_z &&
               *random_engine == *(rhs_c -> random_engine);
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint &file_version) {
      ar & boost::serialization::base_object<IFeatureSelectionProvider>(*this);
      ar & dimension;
      ar & how_many_per_node;
      ar & size_x;
      ar & size_y;
      ar & size_z;
      ar & random_engine;
    }
#endif

    /**
     * Get the horizontal patch size.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * 
     * ----- 
     */
    size_t get_size_x() const { return size_x; }
    /**
     *  Get the vertical patch size.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * 
     * ----- 
     */
    size_t get_size_y() const { return size_y; }
    /**
     * Get the patch depth.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * 
     * ----- 
     */
    size_t get_size_z() const { return size_z; }

    /**
     * Get the total number of of available features.
     * 
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * 
     * -----
     */
    size_t get_n_available_features() const {
        // No overflows.
        FASSERT(std::numeric_limits<size_t>::max() / size_y <= size_x);
        FASSERT(std::numeric_limits<size_t>::max() / (size_x*size_y) <= size_z);
        return size_x * size_y * size_z;
    };

   protected:
    // cppcheck-suppress uninitVar
    VolumeFeatureSelectionProvider() {}

   private:
    size_t dimension;
    size_t how_many_per_node;
    size_t size_x, size_y, size_z;
    std::shared_ptr<std::mt19937> random_engine;

    DISALLOW_COPY_AND_ASSIGN(VolumeFeatureSelectionProvider);
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONPROVIDER_H_
