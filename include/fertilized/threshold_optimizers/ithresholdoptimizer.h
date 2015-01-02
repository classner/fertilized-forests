/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_ITHRESHOLDOPTIMIZER_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_ITHRESHOLDOPTIMIZER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <tuple>
#include <utility>

#include "../global.h"
#include "../types.h"
#include "../fertilized_fwd.h"

namespace fertilized {
  // Forward declaration.
  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ThresholdClassifier;

  /**
   * \brief Finds an optimal threshold.
   *
   * Is classically used by the \ref ThresholdClassifier to optimize the
   * thresholds (\f$\tau\f$).
   *
   * \ingroup fertilizedthreshold_optimizersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
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
  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IThresholdOptimizer {
   public:
    virtual ~IThresholdOptimizer() {}

    typedef IDataProvider<input_dtype, annotation_dtype> data_prov_t;

    /**
     * \brief Tuple containing the optimization results.
     *
     * The order of elements is the following:
     *  -# Pair of thresholds for 'less_than' and 'greater_than' criterion.
     *  -# Types of thresholds used.
     *  -# Number of elements going to 'left'.
     *  -# Number of elements going to 'right'.
     *  -# The calculated gain value.
     */
    typedef std::tuple<std::pair<feature_dtype, feature_dtype>,
                       EThresholdSelection,
                       unsigned int, unsigned int, float>
                       optimization_tuple_t;

    /** Optimizes a threshold decider for one node. */
    virtual optimization_tuple_t optimize(
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
                    bool *valid)
      VIRTUAL(optimization_tuple_t);

    /**
     * \brief Prepares for the optimization routine of a specific node.
     */
    virtual void prepare_for_optimizing(const size_t &node_id,
                                        const int &num_threads) {};

    /**
     * \brief Whether this optimizer needs negative examples (annot[0] == 0).
     */
    virtual bool needs_negatives(const size_t &node_id) { return true; };

    /**
     * \brief Returns the gain threshold to use for this node.
     */
    virtual float get_gain_threshold_for(const size_t &node_id) VIRTUAL(float);

    /**
     * \brief Whether this threshold optimizer can take into account weights
     * during the optimization.
     */
    virtual bool supports_weights() const VIRTUAL(bool);

    /**
     * \brief Check for early stopping.
     *
     * If true is returned, a leaf is created without searching for a threshold.
     */
    virtual bool check_for_early_stop(const annotation_dtype * annotations,
                                      const size_t &annot_dim,
                                      const size_t &n_samples,
                                      const node_id_t &node_id) {
      return false;
    };

    /**
     * Deep equality check.
     */
    virtual bool operator==(const IThresholdOptimizer<input_dtype,
                    feature_dtype,
                    annotation_dtype> &rhs) const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    IThresholdOptimizer() {}
  };
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_ITHRESHOLDOPTIMIZER_H_