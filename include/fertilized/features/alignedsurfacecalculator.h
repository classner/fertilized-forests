/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_ALIGNEDSURFACECALCULATOR_H_
#define FERTILIZED_FEATURES_ALIGNEDSURFACECALCULATOR_H_

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
#include "./isurfacecalculator.h"
#include "./featcalcparamset.h"

namespace fertilized {
  /**
   * \brief Forwards the data as features.
   *
   * Does not require any parameters.
   *
   * \ingroup fertilizedfeaturesGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int; uint
   * - uint8_t; uint
   * - float; uint
   * - float; float
   * - double; uint
   * - double; double
   * .
   *
   * -----
   */
  template <typename input_dtype, typename annotation_dtype>
  class AlignedSurfaceCalculator
    : public ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> {
   public:
    using typename ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype>::sample_vec_t;
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
    AlignedSurfaceCalculator() {}

    /** \brief Returns a one-element empty set for the optimization process. */
    std::vector<FeatCalcParamSet> propose_params() {
      return std::vector<FeatCalcParamSet>(1);
    };

    /** \brief Returns 1. */
    size_t required_num_features() const { return 1; }

    /** \brief Returns the selected data elements. */
    std::shared_ptr<const input_dtype> calculate(
      const input_dtype *data,
      const size_t &length,
      const std::vector<size_t> &feature_selection,
      const elem_id_vec_t &element_ids,
      const std::shared_ptr<const sample_vec_t> &samples,
      const FeatCalcParamSet &parameter_set) const {
        auto del = [](void * p) { };
        return std::shared_ptr<const input_dtype>(data, [](const input_dtype *p){});
    };

    /** \brief Returns the selected data element. */
    input_dtype calculate(
      const std::vector<size_t> &feature_selection,
      const FeatCalcParamSet &parameter_set,
      const input_dtype *data, const size_t data_step) const {
      return data[ data_step * feature_selection[0] ];
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
    bool operator==(const ISurfaceCalculator<input_dtype,
                     input_dtype,
                     annotation_dtype> &rhs)
      const {
      const auto *rhs_c = dynamic_cast<AlignedSurfaceCalculator const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return true;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<
        ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype>>(*this);
    }
#endif
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_ALIGNEDSURFACECALCULATOR_H_
