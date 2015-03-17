/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_ALTERNATINGTHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_ALTERNATINGTHRESHOLDOPTIMIZER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <unordered_map>
#include <vector>
#include <random>

#include "../global.h"
#include "../types.h"
#include "./ithresholdoptimizer.h"

namespace fertilized {
  // Forward declaration.
  template<typename input_dtype, typename feature_dtype,
           typename annotation_dtype>
  class ThresholdDecider;

  /**
   * \brief Uses two other threshold optimizers and randomly selects one of them at each split.
   *
   * \ingroup fertilizedthreshold_optimizersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float; float; float
   * - double; double; double
   * - int; int; uint
   * - int; float; uint
   * - float; int; uint
   * - uint8_t; int; uint
   * - uint8_t; uint8_t; uint
   * - uint8_t; float; uint
   * - uint8_t; int16_t; uint
   * - float; float; uint
   * - double; double; uint
   * - uint8_t; int16_t; int16_t
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class AlternatingThresholdOptimizer
    : public IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> {
   public:
    typedef IThresholdOptimizer<input_dtype, feature_dtype,
                                annotation_dtype> IThresholdOptimizer_t;
    using typename IThresholdOptimizer_t::data_prov_t;
    using typename IThresholdOptimizer_t::optimization_tuple_t;
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_list_t;

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
     * \param opt1 shared(IThresholdOptimizer)
     *   The first threshold optimizer to alternate in between.
     * \param opt2 shared(IThresholdOptimizer)
     *   The second threshold optimizer to alternate in between.
     * \param random_seed uint>0
     *   The random seed for the RNG. Default: 1.
     */
    AlternatingThresholdOptimizer(
      const std::shared_ptr<IThresholdOptimizer_t> &opt1,
      const std::shared_ptr<IThresholdOptimizer_t> &opt2,
      const unsigned int &random_seed=1)
      : random_engine(std::make_shared<std::mt19937>(random_seed)),
        dist(std::uniform_int_distribution<uint>(0, 1)),
        opt1(opt1),
        opt2(opt2),
        opt_sel_map(std::unordered_map<node_id_t, bool>()) {
     if (random_seed == 0) {
        throw Fertilized_Exception("Need a random seed >= 1!");
      }
    }

    /** Selects a threshold optimizer for this node, to enable parallelization. */
    void prepare_for_optimizing(const size_t &node_id,
                                const int &num_threads) {
      auto ret = opt_sel_map.emplace(node_id, (dist(*random_engine)==0?false:true));
      if (!ret.second)
        throw Fertilized_Exception("Tried to reset a node's decision "
          "parameters.");
      opt1 -> prepare_for_optimizing(node_id, num_threads);
      opt2 -> prepare_for_optimizing(node_id, num_threads);
    }

    /**
     * \brief Check for early stopping.
     *
     * If true is returned, a leaf is created without searching for a threshold.
     */
    bool check_for_early_stop(const annotation_dtype * annotations,
                              const size_t &annot_dim,
                              const node_id_t &node_id) {
      if (opt_sel_map.at(node_id))
        return opt1 -> check_for_early_stop(annotations, annot_dim, node_id);
      else
        return opt2 -> check_for_early_stop(annotations, annot_dim, node_id);
    };

    /** 
     * Gets the gain threshold of the threshold optimizer selected for the node. 
     * 
     * This is only valid if the node has been processed already!
     */
    float get_gain_threshold_for(const size_t &node_id) {
      if (opt_sel_map.at(node_id))
        return opt1 -> get_gain_threshold_for(node_id);
      else
        return opt2 -> get_gain_threshold_for(node_id);
    }

    /** Returns true if both threshold optimizers support weights. */
    bool supports_weights() const {
      return opt1 -> supports_weights() &&
             opt2 -> supports_weights();
    }

    /**
     *\brief See \ref IThresholdOptimizer.
     *
     * Additionally, this method has the following constraints:
     *   - The sample weights must be positive.
     *   - The sum of weights of all selected samples must be < FLOAT_MAX
     *   - The annotations must be in the interval [0, n_classes[.
     *   - Any constraints that the selected gain calculator enforces.
     */
    optimization_tuple_t optimize(
              const node_id_t &node_id,
              const int &suggestion_index,
              const size_t &min_samples_at_leaf,
              const size_t &n_samples,
              const input_dtype *selected_data,
              const size_t &data_dimension,
              const annotation_dtype *annotations,
              const size_t &annontation_dimension,
              const float *weights,
              const feature_dtype *feature_values,
              bool *valid) {
      if (opt_sel_map.at(node_id))
        return opt1 -> optimize(node_id,
                                suggestion_index,
                                min_samples_at_leaf,
                                n_samples,
                                selected_data,
                                data_dimension,
                                annotations,
                                annontation_dimension,
                                weights,
                                feature_values,
                                valid);
      else
        return opt2 -> optimize(node_id,
                                suggestion_index,
                                min_samples_at_leaf,
                                n_samples,
                                selected_data,
                                data_dimension,
                                annotations,
                                annontation_dimension,
                                weights,
                                feature_values,
                                valid);
    }


    /**
     * \brief Whether this optimizer needs negative examples (annot[0] == 0).
     */
    bool needs_negatives(const size_t &node_id) {
      if (opt_sel_map.at(node_id))
        return opt1 -> needs_negatives(node_id);
      else
        return opt2 -> needs_negatives(node_id);
    };

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
    bool operator==(const IThresholdOptimizer<input_dtype,
                    feature_dtype,
                    annotation_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<AlternatingThresholdOptimizer<input_dtype,
                                                           feature_dtype,
                                                           annotation_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_re = *random_engine == *(rhs_c -> random_engine);
        bool eq_opt1 = *opt1 == *(rhs_c -> opt1);
        bool eq_opt2 = *opt2 == *(rhs_c -> opt2);
        bool eq_map = opt_sel_map == rhs_c -> opt_sel_map;
        return eq_re && eq_opt1 && eq_opt2 && eq_map;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IThresholdOptimizer_t>(*this);
      ar & random_engine;
      ar & opt1;
      ar & opt2;
      ar & opt_sel_map;
    }
#endif
    friend class ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>;
   protected:
     AlternatingThresholdOptimizer()
       : dist(std::uniform_int_distribution<uint>(0, 1)) {}

   private:
    std::shared_ptr<std::mt19937> random_engine;
    std::uniform_int_distribution<uint> dist;
    std::shared_ptr<IThresholdOptimizer_t> opt1;
    std::shared_ptr<IThresholdOptimizer_t> opt2;
    std::unordered_map<node_id_t, bool> opt_sel_map;

    DISALLOW_COPY_AND_ASSIGN(AlternatingThresholdOptimizer);
  };
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_ALTERNATINGTHRESHOLDOPTIMIZER_H_