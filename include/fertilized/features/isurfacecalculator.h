/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_ISURFACECALCULATOR_H_
#define FERTILIZED_FEATURES_ISURFACECALCULATOR_H_

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
#include "../fertilized_fwd.h"
#include "../features/featcalcparamset.h"
#include "./_issubsdprov_dpdsc.h"

namespace fertilized {
  /**
   * \brief Calculates scalar values from a set of provided data dimensions.
   *
   * Must also propose parameter-sets for a random optimization of itself.
   *
   * \ingroup fertilizedfeaturesGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * Instantiations:
   * - int; int; uint
   * - int; float; uint
   * - uint8_t; uint8_t; uint
   * - uint8_t; int16_t; uint
   * - uint8_t; int16_t; int16_t
   * - uint8_t; float; uint
   * - float; float; uint
   * - float; float; float
   * - double; double; uint
   * - double; float; uint
   * - double; double; double
   * - double; float; double
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ISurfaceCalculator {
   public:
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_vec_t;

    virtual ~ISurfaceCalculator() {}

    /**
     * \brief Propose a set of parameter configurations.
     *
     * Even if the feature calculator has no parameters, this method should
     * return a one-element vector with an empty set for the optimization
     * process.
     */
    virtual std::vector<FeatCalcParamSet> propose_params()
      VIRTUAL(std::vector<FeatCalcParamSet>);

    /**
     * \brief Checks compatibility to a specific data provider.
     */
    virtual bool is_compatible_to(const IDataProvider<input_dtype, annotation_dtype> * const dprov) const {
      return ! _IsSubsDprov_DPDSC<input_dtype, annotation_dtype>::check(dprov);
    }

    /**
     * \brief Whether this data provider needs all inputs contiguously in one
     * array.
     *
     * The direct patch difference surface calculator does not require this.
     */
    virtual bool needs_elements_prepared() const {
      return true;
    };

    /**
      * \brief Get the scalar feature representations for a set of data
      * tuples.
      *
      * \param data_dimension_selection A selection of data dimensions to
      *         calculate the feature on.
      * \param parameter_set A parameter set to use.
      * \param data_provider A data provider that can provide the samples.
      * \param element_ids The ids of the samples of which the features
      *         should be calculated.
      * \return A vector of one float value per sample.
      */
    virtual std::shared_ptr<const feature_dtype> calculate(
      const input_dtype *data,
      const size_t &length,
      const std::vector<size_t> &feature_selection,
      const elem_id_vec_t &element_ids,
      const std::shared_ptr<const sample_vec_t> &samples,
      const FeatCalcParamSet &parameter_set) const
      VIRTUAL_PTR;

    /**
     * \brief Get the scalar feature representation for one sample.
     */
    virtual feature_dtype calculate(
      const std::vector<size_t> &feature_selection,
      const FeatCalcParamSet &parameter_set,
      const input_dtype *data, const size_t data_step) const
      VIRTUAL(feature_dtype);

    /**
     * \brief Get the number of data dimensions required to calculate the
     * the feature.
     */
    virtual size_t required_num_features() const VIRTUAL(size_t);

    virtual bool operator==(const ISurfaceCalculator &rhs) const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    ISurfaceCalculator() {}
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_ISURFACECALCULATOR_H_
