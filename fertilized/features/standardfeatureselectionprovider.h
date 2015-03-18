/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_STANDARDFEATURESELECTIONPROVIDER_H_
#define FERTILIZED_FEATURES_STANDARDFEATURESELECTIONPROVIDER_H_

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
#include "./standardfeatureselectiongenerator.h"
#include "./ifeatureselectionprovider.h"

namespace fertilized {
  /**
   * \brief This selection provider generates random selection combinations.
   *
   * It may be seeded for reproducible results. It can be configured to only
   * use a part of the available data dimensions. It only uses then the first
   * that are registered as used.
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
  class StandardFeatureSelectionProvider
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
     * \param n_selections_per_node size_t>0
     *   How many selection proposals are created for each node.
     * \param selection_dimension size_t>0
     *   How many data dimensions are selected per
     *   proposal. Must be > 0 and < how_many_available.
     * \param how_many_available size_t>0
     *   How many data dimensions are available.
     * \param max_to_use size_t
     *   How many data dimensions may be used. If set to zero, use how_many_available.
     *   Default: 0.
     * \param random_seed uint>0
     *   A random seed for the random number generator. Must
     *   be greater than 0. Default: 1.
     */
    StandardFeatureSelectionProvider(
      const size_t &n_selections_per_node,
      const size_t &selection_dimension,
      const size_t &how_many_available,
      size_t max_to_use=0,
      const uint &random_seed = 1)
      : dimension(selection_dimension),
        how_many_per_node(n_selections_per_node),
        how_many_available(how_many_available),
        max_to_use(max_to_use),
        random_engine(std::make_shared<std::mt19937>(random_seed)) {
      // TODO(Christoph): Remove max_to_use option for large speed gain.
      // Sanity checks.
      if (how_many_per_node == 0) {
        throw Fertilized_Exception("The number of selections per node must be >0!");
      }
      if (how_many_available == 0) {
        throw Fertilized_Exception("The number of available dimensions must be >0!");
      }
      if (dimension == 0)
        throw Fertilized_Exception("The number of selected dimensions per "
         "proposal by the features selector must be greater 0!");
      if (max_to_use == 0) {
        max_to_use = how_many_available;
      }
      if (dimension > how_many_available)
        throw Fertilized_Exception("The number of available features must "
         "be greater than the number of features to select for one proposal!");
      int64_t combinations = ibinom(
        static_cast<int>(std::min(how_many_available, max_to_use)),
        static_cast<int>(dimension));
      if ((combinations < static_cast<int64_t>(how_many_per_node) * 2 &&
           combinations != -1) &&  // -1: Overflow detected: a LOT of comb.s ;)
           dimension != 1 && n_selections_per_node != 1 ||
           dimension == 1 && how_many_per_node > std::min(max_to_use, how_many_available)) {
        throw Fertilized_Exception("The standard feature selection "
          "provider has been initialized wrongly. In the "
          "case of n data features and k to choose per node being less "
          "than how many samples per node to provide / 2, "
          "the provided algorithm might be very slow! Use a different FeatureSelectionProvider.");
      }
      if (random_seed == 0) {
        throw Fertilized_Exception("Choose a random seed >0!");
      }
      used_indices = std::make_shared<std::vector<size_t>>();
      used_index_markers = std::vector<bool>(how_many_available, false);
      available_indices = std::make_shared<std::vector<size_t>>(how_many_available);
      std::iota(available_indices -> begin(), available_indices -> end(), 0);
      std::shuffle(available_indices -> begin(),
                   available_indices -> end(), *random_engine);
    };

    /** Returns how_many_available as specified in the constructor. */
    size_t get_input_dimension() const {
      return how_many_available;
    };

    /** \brief See \ref IFeatureSelectionProvider::get_selection_dimension. */
    size_t get_selection_dimension() const {
      return dimension;
    };

    /** Gets the associated \ref StandardFeatureSelectionGenerator. */
    std::shared_ptr<IFeatureSelectionGenerator> get_proposal_generator() {
      // The maximum amount of new indices that may be used in the generated
      // selection proposals.
      size_t new_to_include = (max_to_use > 0 ? max_to_use - used_indices -> size() :
                               available_indices -> size() - used_indices -> size());
      size_t index_max = used_indices -> size() +
          std::min<size_t>(new_to_include, available_indices -> size()) - 1;

      return std::shared_ptr<StandardFeatureSelectionGenerator>(
        new StandardFeatureSelectionGenerator(dimension, index_max,
          how_many_per_node, used_indices, available_indices, random_engine));
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
    void register_used(const proposal_set_t &proposals) {
      // Speed optimization: in this case, the features don't have to be
      // tracked.
      if (max_to_use == how_many_available)
        return;

      // The erase operation is not very fast on vectors in general. However,
      // by the design of the two functions get_proposals and register_used,
      // elements are always pretty much at the end of the vector if they
      // are erased, making the operation reasonably fast. A list cannot
      // be used here, since the get_proposals method needs repeated fast
      // random access.
      for (const auto &proposal : proposals) {
        for (const size_t &index : proposal) {
          if (!used_index_markers[ index ]) {
            used_index_markers[ index ] = true;
            used_indices -> push_back(index);
            available_indices -> erase(
              std::find(available_indices -> begin(),
                        available_indices -> end(), index));
          }
        }
      }
    }

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
    bool operator==(const IFeatureSelectionProvider &rhs)
      const {
      const auto *rhs_c = dynamic_cast<StandardFeatureSelectionProvider const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else {
        bool eq_dim = dimension == rhs_c -> dimension;
        bool eq_hmpn = how_many_per_node == rhs_c -> how_many_per_node;
        bool eq_hmav = how_many_available == rhs_c -> how_many_available;
        bool eq_mtu = max_to_use == rhs_c -> max_to_use;
        bool eq_used = *used_indices == *(rhs_c -> used_indices);
        bool eq_mrks = used_index_markers == rhs_c -> used_index_markers;
        bool eq_av = *available_indices == *(rhs_c -> available_indices);
        bool eq_re = *random_engine == *(rhs_c -> random_engine);
        //std::cout << eq_dim << std::endl;
        //std::cout << eq_hmpn << std::endl;
        //std::cout << eq_hmav << std::endl;
        //std::cout << eq_mtu << std::endl;
        //std::cout << eq_used << std::endl;
        //std::cout << eq_mrks << std::endl;
        //std::cout << eq_av << std::endl;
        //std::cout << eq_re << std::endl;
        return eq_dim &&
               eq_hmpn &&
               eq_hmav &&
               eq_mtu &&
               eq_used &&
               eq_mrks &&
               eq_av &&
               eq_re;
      }
    };
    
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
        return how_many_available;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint &file_version) {
      ar & boost::serialization::base_object<IFeatureSelectionProvider>(*this);
      ar & dimension;
      ar & how_many_per_node;
      ar & how_many_available;
      ar & max_to_use;
      ar & used_indices;
      ar & used_index_markers;
      ar & available_indices;
      ar & random_engine;
    }
#endif

   protected:
    // cppcheck-suppress uninitVar
    StandardFeatureSelectionProvider() {}

   private:
    size_t dimension;
    size_t how_many_per_node;
    size_t how_many_available;
    size_t max_to_use;
    std::shared_ptr<std::vector<size_t>> used_indices;
    std::vector<bool> used_index_markers;
    std::shared_ptr<std::vector<size_t>> available_indices;
    std::vector<size_t> ind_shuffle_vec;
    std::shared_ptr<std::mt19937> random_engine;

    DISALLOW_COPY_AND_ASSIGN(StandardFeatureSelectionProvider);
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_STANDARDFEATURESELECTIONPROVIDER_H_
