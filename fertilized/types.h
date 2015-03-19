/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_TYPES_H_
#define FERTILIZED_TYPES_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <unordered_set>
#include <utility>
#include <vector>
#include <map>
#include <memory>
#include <numeric>

namespace fertilized {
  /**
   * \brief Specifies the completion level for one training step.
   *
   * -----
   * Available in:
   * - C++
   * .
   *
   * -----
   */
  enum class CompletionLevel {
    /** Train one node only. */
    Node,
    /** Train one level of the tree (i.e. one depth level for BFS, one
      * branch for DFS). */
    Level,
    /** Complete the training for the entire tree. */
    Complete
  };

  /** \brief Node id type. Is size_t because it is used for array acces. */
  typedef size_t node_id_t;

  /** \brief Sample id type. Is size_t for fast array access. */
  typedef size_t element_id_t;

  /** \brief Feature id type. Is size_t for fast array access. */
  typedef size_t feature_id_t;

  /** \brief Feature id type. Is size_t for fast array access. */
  typedef size_t tree_id_t;

  /** \brief Convenience typedef for unsigned int. */
  typedef unsigned int uint;

  /** \brief Specifies which thresholds should be used for a decision. */
  enum class EThresholdSelection { less_only, greater_only, both };

  /** \brief Denotes an element list container. */
  typedef std::vector<element_id_t> elem_id_vec_t;

  /**
   * \brief Stores the parameters for one marked tree node.
   *
   * Contains the following elements:
   *  -# A pointer to an \ref elem_id_vec_t.
   *  -# A node id (\ref node_id_t).
   *  -# The node's depth (uint).
   */
  typedef std::tuple<std::shared_ptr<elem_id_vec_t>,
                     node_id_t,
                     unsigned int> node_todo_tuple_t;

  /** \brief A pair containing the two child ids for a decision node. */
  typedef std::pair<node_id_t, node_id_t> node_id_pair_t;

  /** Specifies the action to do for one sample for a sample manager. */
  enum class SampleAction { add_to_training, remove_from_training,
    add_to_validation, remove_from_validation };

  /** \brief Describes how each sample is used for each tree. */
  typedef std::vector<
             std::pair<
               std::shared_ptr<std::vector<size_t>>,
                 std::shared_ptr<std::vector<size_t>>>> usage_map_t;

  typedef std::map<tree_id_t, std::map<SampleAction, std::vector<element_id_t>>>
    sample_action_map_t;

  /**
   * \brief A pair containing information about newly included samples.
   *
   * The content is the following:
   *   -# A pointer to a vector of assigned sample ids.
   *   -# The threshold of already existing sample ids to new ones
   *      (old are up to excluding this value).
   */
  typedef std::pair<std::shared_ptr<std::vector<element_id_t>>,
                    element_id_t> include_pair_t;

  /** Specifies the type of tree search. */
  enum class action_type { DFS, BFS };

  /**
   * \brief Quick and easy implementation of 64-bit FNV 1a hash.
   *
   * The FNV 1a is easy to implement and has still good enough characteristics
   * to be used for this application.
   *
   * See http://www.isthe.com/chongo/tech/comp/fnv/index.html and for
   * comparisons and more information
   * http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx and
   * http://burtleburtle.net/bob.
   */
  static size_t hash_fnv_1a(const unsigned char *key, const size_t &len) {
    // hash = offset_basis
    size_t h = 14695981039346656037ULL;
    // for each octet_of_data to be hashed
    for (size_t i = 0; i < len; ++i) {
      // hash = hash xor octet_of_data
      // hash = hash * FNV_prime
      h = (h ^ key[ i ]) * 1099511628211;
    }
    // return hash
    return h;
  };

  /** \brief A simple vector<size_t> hasher. */
  struct vector_hasher {
    /** Hash function. */
    size_t operator()(const std::vector<size_t> &t) const {
      if (t.empty()) return 0;
      return hash_fnv_1a(reinterpret_cast<const unsigned char *>(&t[0]),
                         t.size() * sizeof(size_t) / sizeof(unsigned char));
    };
  };

  /** \brief The type of a set of dimension selections. */
  typedef std::unordered_set<std::vector<size_t>, vector_hasher>
      proposal_set_t;

};  // namespace fertilized
#endif  // FERTILIZED_TYPES_H_
