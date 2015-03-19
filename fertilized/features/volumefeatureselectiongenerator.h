/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONGENERATOR_H_
#define FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONGENERATOR_H_

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
  /** The generator for the \ref VolumeFeatureSelectionProvider.
   *
   * Internal use only.
   */
  class VolumeFeatureSelectionGenerator
    : public IFeatureSelectionGenerator {
   public:
    /** Standard constructor. */
    VolumeFeatureSelectionGenerator(
      const size_t &dimension,
      const size_t &size_x,
      const size_t &size_y,
      const size_t &size_z,
      const size_t &how_many_per_node,
      std::shared_ptr<std::mt19937> random_engine)
    : size_x(size_x),
      size_y(size_y),
      size_z(size_z),
      dimension(dimension),
      max_layer_index(size_x*size_y-1),
      layer_size(size_x * size_y),
      dist_z(std::uniform_int_distribution<size_t>(0, size_z-1)),
      how_many_per_node(how_many_per_node),
      random_engine(random_engine),
      generated(0) { }

    /** Whether there is another value available. */
    bool available() const {
      return generated < how_many_per_node;
    }

    /** Returns how_many_per_node as specified in the constructor. */
    size_t max_count() const {
      return how_many_per_node;
    }

    /** Get the next proposal.*/
    std::vector<size_t> get_next() {
      if (generated >= how_many_per_node)
        throw Fertilized_Exception("Tried to generate more feature comb. "
          "for a node than there are available.");
      generated++;
      std::vector<size_t> selection;
      do {
        // Draw a layer.
        size_t z = dist_z(*random_engine);
        // Draw two x and y coordinates.
        selection = unique_indices<size_t>(dimension,
                                           0,
                                           max_layer_index,
                                           random_engine.get(),
                                           false);
#ifdef __INTEL_COMPILER
        #pragma simd
#endif
        for (size_t j = 0; j < dimension; ++j) {
          selection[j] += z * layer_size;
        }
      } while (already_used.find(selection) != already_used.end());
      already_used.emplace(selection);
      return selection;
    }

    const size_t size_x, size_y, size_z;

  private:
    const size_t dimension;
    const size_t max_layer_index;
    const size_t layer_size;
    std::uniform_int_distribution<size_t> dist_z;
    const size_t how_many_per_node;
    std::shared_ptr<std::mt19937> random_engine;
    size_t generated;
    proposal_set_t already_used;
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_VOLUMEFEATURESELECTIONGENERATOR_H_
