/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_SUBSAMPLINGDATAPROVIDER_H_
#define FERTILIZED_DATA_PROVIDERS_SUBSAMPLINGDATAPROVIDER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <unordered_map>
#include <limits>
#include <memory>
#include <vector>
#include <list>
#include <iterator>
#include <utility>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/sampling.h"
#include "./idataprovider.h"
#include "./isamplemanager.h"

namespace fertilized {
  /**
   * \brief Uses at maximum a certain amount of samples for node optimization.
   *
   * Tracks the loaded samples during training and adds new samples if possible.
   * For leafs, all samples are loaded, even if its more than the maximum
   * number of samples for split optimization.
   *
   * \ingroup fertilizeddata_providersGroup
   *
   * Can only be used for DFS (!!) for efficiency reasons.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - uint8_t; int16_t
   * - uint8_t; uint
   * .
   *
   * -----
   */
  template<typename input_dtype, typename annotation_dtype>
  class SubsamplingDataProvider :
    public IDataProvider<input_dtype, annotation_dtype> {
   public:
    typedef IDataProvider<input_dtype, annotation_dtype> data_prov_t;
    using typename data_prov_t::sample_t;
    using typename data_prov_t::sample_list_t;

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
     * \param max_samples_per_node size_t>0
     *   The maximum number of samples to use for split optimization.
     * \param sample_manager shared(ISampleManager)
     *   The ISampleManager to use to handle the samples.
     * \param random_seed uint>0
     *   The seed for the RNG.
     */
    SubsamplingDataProvider(
      const size_t &max_samples_per_node,
      std::shared_ptr<ISampleManager<input_dtype, annotation_dtype>> sample_manager,
      const unsigned int &random_seed = 1)
      : samples(std::make_shared<sample_list_t>()),
        training_ids(std::make_shared<elem_id_vec_t>()),
        validation_ids(std::make_shared<elem_id_vec_t>()),  
        random_engine(std::make_shared<std::mt19937>(random_seed)),
        sample_manager(sample_manager),
        n_samples(sample_manager -> n_samples),
        max_samples_per_node(max_samples_per_node),
        node_flag(std::unordered_map<node_id_t, bool>()),
        unused_sample_pool(std::unordered_map<node_id_t, std::pair<node_id_t, std::list<node_id_t>>>()),
        data_prov_t(sample_manager -> sample_size,
                    sample_manager -> annot_size) {
      // Checks.
      if (max_samples_per_node == 0)
        throw Fertilized_Exception("Max samples per node must be > 0.");
      if (n_samples == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                    "0 samples.");
      if (random_seed == 0) {
        throw Fertilized_Exception("The random seed must be >0.");
      }
      // Generate the weights, data and annotation pointers, and step sizes.
      for (size_t i = 0; i < n_samples; ++i) {
        samples -> push_back(sample_t(nullptr,
                                      0,
                                      nullptr,
                                      1.f));
        training_ids -> push_back(i);
      }
      // Check that the weights are setup ok (wrt to numeric limits).
      FASSERT(check_sample_weights_ok(*samples, *training_ids));
      // Add the root node to the map.
      node_flag.emplace(0, false);
      unused_sample_pool[ 0 ] = std::make_pair(0, std::list<node_id_t>(0));
      sample_manager -> register_dprov(samples,
                                       max_samples_per_node);
    };

    /** Checks how many samples reach a node and add new samples if there are
     * unused ones left and the maximum number of samples has not been
     * reached yet.
     */
    void optimize_set_for_node(
      const node_id_t &node_id,
      const uint &depth,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)>
                                        node_predictor,
      std::shared_ptr<elem_id_vec_t> &element_list) {
      FASSERT(node_id != 0 ? element_list -> size() <= max_samples_per_node : true);
      if (element_list -> size() > max_samples_per_node && node_id == 0) {
        std::shuffle(element_list -> begin(),
                     element_list -> end(),
                     *random_engine);
        // Use the first elements, put the rest on the unused list.
        unused_sample_pool[ node_id ].second.insert(
          unused_sample_pool[ node_id ].second.begin(),
          element_list -> begin() + max_samples_per_node,
          element_list-> end());
        element_list -> erase(element_list -> begin() + max_samples_per_node,
                              element_list -> end());
        sample_manager -> ensure_available(*element_list);
        FASSERT(element_list -> size() == max_samples_per_node);
        node_flag[ node_id ] = true;
      } else {
        // Check the node flag.
        if (node_flag[ node_id ]) {
          // The parent node was subject to subsampling, so search again
          // for samples that might arrive here until the maximum number
          // of samples is reached.
          sample_manager -> ensure_available(*element_list);
          node_id_t last_search_node_id = std::numeric_limits<node_id_t>::max();
          node_id_t pnode_id;
          for (node_id_t search_node_id = node_id;
               last_search_node_id != unused_sample_pool[ search_node_id ].first;
               last_search_node_id = search_node_id,
               search_node_id = unused_sample_pool[ search_node_id ].first) {
            // Get the unused sample list.
            std::list<node_id_t> &unused_sample_list =
                                unused_sample_pool[ search_node_id ].second;
            for (auto unused_sample_it = unused_sample_list.begin();
                   unused_sample_it != unused_sample_list.end() &&
                   element_list -> size() < max_samples_per_node; ) {
              // Find out to which node this sample would get.
              if (search_node_id == node_id) {
                // We know that it arrives at this node already.
                pnode_id = node_id;
              } else {
                // Predict the node.
                pnode_id = sample_manager -> get_leaf(*unused_sample_it,
                                                      node_predictor,
                                                      search_node_id);
              }
              if (pnode_id == node_id) {
                // The sample reaches this node.
                // Load the sample without giving up a required sample.
                sample_manager -> ensure_available(*unused_sample_it);
                element_list -> emplace_back(*unused_sample_it);
                unused_sample_it = unused_sample_list.erase(unused_sample_it);
              } else if (pnode_id != search_node_id) {
                unused_sample_pool[ pnode_id ].second.push_back(*unused_sample_it);
                unused_sample_it = unused_sample_list.erase(unused_sample_it);
              } else {
                // The predicted node id is the same as the one of th
                // list and it can not be used.
                unused_sample_it++;
              }
            }
            // If there are enough samples, end the search.
            if (element_list -> size() == max_samples_per_node)
              break;
          }
          // If search at the root node was completed.
          if (last_search_node_id == 0) {
            node_flag[node_id] = false;
            FASSERT(element_list -> size() <= max_samples_per_node);
          } else {
            FASSERT(element_list -> size() == max_samples_per_node);
          }
        } else {
          // If this was the root node, the flag is set to false (the
          // -nonexistent- parent was not subsampled) but still all samples
          // must be loaded.
          if (node_id == 0) {
            sample_manager -> ensure_available(*element_list);
          }
        }
      }
    }

    /** Internal utility function to guarantee that all samples are available
     * at a leaf. Their number can be greater than the maximum number of
     * samples for split optimization. */
    void load_samples_for_leaf(const node_id_t &node_id,
        const std::function<node_id_t(const input_dtype*,
                                      const size_t&,
                                      const node_id_t &,
                                      const std::function<void(void*)>&)>
                                          node_predictor,
        elem_id_vec_t *element_list) {
      // Check the node flag.
      if (node_flag[ node_id ]) {
        // The parent node was subject to subsampling, so search again
        // for samples that might arrive here.
        sample_manager -> ensure_available(*element_list);
        node_id_t last_search_node_id = std::numeric_limits<node_id_t>::max();
        node_id_t pnode_id;
        for (node_id_t search_node_id = node_id;
              last_search_node_id != unused_sample_pool[ search_node_id ].first;
              last_search_node_id = search_node_id,
              search_node_id = unused_sample_pool[ search_node_id ].first) {
          // Get the unused sample list.
          std::list<node_id_t> &unused_sample_list =
                              unused_sample_pool[ search_node_id ].second;
          for (auto unused_sample_it = unused_sample_list.begin();
                  unused_sample_it != unused_sample_list.end(); ) {
            // Here, more than the maximum number of samples may arrive at
            // the leaf, because we want to use all available!

            // Find out to which node this sample would get.
            if (search_node_id == node_id) {
              // We know that it arrives at this node already.
              pnode_id = node_id;
            } else {
              // Predict the node.
              pnode_id = sample_manager -> get_leaf(*unused_sample_it,
                                                    node_predictor,
                                                    search_node_id);
            }
            if (pnode_id == node_id) {
              // The sample reaches this node.
              // Load the sample without giving up a required sample.
              sample_manager -> ensure_available(*unused_sample_it);
              element_list -> emplace_back(*unused_sample_it);
              unused_sample_it = unused_sample_list.erase(unused_sample_it);
            } else if (pnode_id != search_node_id) {
              unused_sample_pool[ pnode_id ].second.push_back(*unused_sample_it);
              unused_sample_it = unused_sample_list.erase(unused_sample_it);
            } else {
              // The predicted node id is the same as the one of the
              // list and it can not be used.
              unused_sample_it++;
            }
          }
        }
        node_flag[node_id] = false;
      }
    };

    /** \brief Returns a list of all sample ids. */
    std::shared_ptr<const elem_id_vec_t> get_initial_sample_list() const  {
      return training_ids;
    };

    /** Gets the sample vector. */
    std::shared_ptr<const sample_list_t> get_samples() const {
      return samples;
    };

    /** Gets the validation sample vector. */
    std::shared_ptr<const elem_id_vec_t> get_validation_sample_list() const {
      return validation_ids;
    }

    /** \brief Always returns an empty vector. */
    const std::vector<sample_t> get_added_samples() {
      return std::vector<sample_t>();
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void add_to_training_set(const std::vector<sample_t> &samples) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void remove_from_training_set(
      const std::vector<element_id_t> &sample_ids) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void add_to_validation_set(const std::vector<sample_t> &samples) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void remove_from_validation_set(
      const std::vector<element_id_t> &sample_ids) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** Gets the number of samples. */
    size_t get_n_samples() {
      return n_samples;
    };

    /** Tracks where the samples go! */
    void track_child_nodes(node_id_t node_id,
      node_id_t left_id, node_id_t right_id) {
      bool val = node_flag.at(node_id);
      node_flag[left_id] = val;
      unused_sample_pool[ left_id ] = std::make_pair(node_id, std::list<node_id_t>(0));
      node_flag[right_id] = val;
      unused_sample_pool[ right_id ] = std::make_pair(node_id, std::list<node_id_t>(0));
    }
    
    /** Gets the decision transformation function from the sample manager. */
    std::function<void(void*)> get_decision_transf_func(
                                                  const element_id_t &elem_id)
      const {
      return sample_manager -> get_decision_transf_func(elem_id);
    }

    /** Gets the sample manager. */
    std::shared_ptr<const ISampleManager<input_dtype, annotation_dtype>> get_SampleManager() const {
      return sample_manager;
    }

   private:
    std::shared_ptr<sample_list_t> samples;
    std::shared_ptr<elem_id_vec_t> training_ids;
    std::shared_ptr<elem_id_vec_t> validation_ids;
    std::shared_ptr<std::mt19937> random_engine;
    std::shared_ptr<ISampleManager<input_dtype, annotation_dtype>> sample_manager;
    size_t n_samples;
    size_t max_samples_per_node;
    /**
     * The node flag has two uses:
     *  * If the node is visited as child to be constructed, if the node flag
     *    is set to true AND there are less samples observed than there
     *    are allowed by the maximum, a search is started for sample that
     *    arrive at the node to enhance the set. If false, then not.
     *  * If processing the node is finished and the flag is set to true,
     *    then the child-nodes will receive a true flag, otherwise a false
     *    flag.
     */
    std::unordered_map<node_id_t, bool> node_flag;
    std::unordered_map<node_id_t, std::pair<node_id_t, std::list<node_id_t>>> unused_sample_pool;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_SUBSAMPLINGDATAPROVIDER_H_