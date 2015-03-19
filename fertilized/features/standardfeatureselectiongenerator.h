/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_STANDARDFEATURESELECTIONGENERATOR_H_
#define FERTILIZED_FEATURES_STANDARDFEATURESELECTIONGENERATOR_H_

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
  /** The feature generator for the \ref StandardFeatureSelectionProvider. Internal use only. */
  class StandardFeatureSelectionGenerator
    : public IFeatureSelectionGenerator {
  public:
    /** Standard constructor. */
    StandardFeatureSelectionGenerator(
      const size_t &dimension,
      const size_t &index_max,
      const size_t &how_many_per_node,
      std::shared_ptr<std::vector<size_t>> used_indices,
      std::shared_ptr<std::vector<size_t>> available_indices,
      std::shared_ptr<std::mt19937> random_engine)
    : dimension(dimension),
      index_max(index_max),
      how_many_per_node(how_many_per_node),
      used_indices(used_indices),
      available_indices(available_indices),
      random_engine(random_engine),
      generated(0) {
      if (dimension == 1) {
        sampler = std::unique_ptr<SamplingWithoutReplacement<size_t>>(
          new SamplingWithoutReplacement<size_t>(0, index_max, random_engine));
      } else {
        already_used = proposal_set_t();
        already_used.reserve(how_many_per_node);
      }
    };

    /** Whether still values are available. */
    bool available() const {
      return generated < how_many_per_node;
    }

    /** Returns how_many_per_node as specified in the constructor. */
    size_t max_count() const {
      return how_many_per_node;
    }

    /** Gets the next proposal. */
    std::vector<size_t> get_next() {
      // Generate the selection.
      if (dimension == 1) {
        if (generated >= how_many_per_node)
          throw Fertilized_Exception("Tried to generate more feature comb. "
            "for a node than there are available.");
        generated++;
        size_t next_preselection = sampler -> get_next();
        if (next_preselection < used_indices -> size()) {
          return std::vector<size_t>(1, used_indices -> at(next_preselection));
        } else {
          return std::vector<size_t>(1, available_indices -> at(
            available_indices -> size() -
            (next_preselection- used_indices -> size()) - 1));
        }
      } else {
        if (generated >= how_many_per_node)
          throw Fertilized_Exception("Tried to generate more feature comb. "
            "for a node than there are available.");
        generated++;
        std::vector<size_t> selection(dimension), preselection;
          do {
            preselection = unique_indices<size_t>(dimension, 0, index_max, random_engine.get());
            for (size_t j = 0; j < static_cast<size_t>(dimension); ++j) {
                if (preselection[j] < used_indices -> size()) {
                  selection[j] = used_indices -> at(preselection[j]);
                } else {
                  selection[j] = available_indices -> at(
                                   available_indices -> size() -
                                   (preselection[j]- used_indices -> size()) - 1);
                }
              }
          } while (already_used.find(selection) != already_used.end());
          already_used.emplace(selection);
          return selection;
      }
    }

  private:
    const size_t dimension;
    const size_t index_max;
    const size_t how_many_per_node;
    std::shared_ptr<const std::vector<size_t>> used_indices, available_indices;
    std::unique_ptr<SamplingWithoutReplacement<size_t>> sampler;
    std::shared_ptr<std::mt19937> random_engine;
    proposal_set_t already_used;
    size_t generated;
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_STANDARDFEATURESELECTIONGENERATOR_H_
