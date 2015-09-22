/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_DIFFERENCESURFACECALCULATOR_H_
#define FERTILIZED_FEATURES_DIFFERENCESURFACECALCULATOR_H_

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
   * \brief Calculates a feature as the difference between two data dimensions
   * of inputs.
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
   * - int; int; uint
   * - uint8_t; int16_t; uint
   * - float; float; uint
   * - float; float; float
   * - double; double; uint
   * - double; double; double
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DifferenceSurfaceCalculator
    : public ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> {
   public:
    using typename ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>::sample_vec_t;

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
    DifferenceSurfaceCalculator() {}

    /** Always returns a one-element vector with unspecified content. */
    std::vector<FeatCalcParamSet> propose_params() {
      return std::vector<FeatCalcParamSet>(1);
    };

    /** Always returns 2. */
    size_t required_num_features() const { return 2; }

    /** Calculates the surface value (training). */
    std::shared_ptr<const feature_dtype> calculate(
      const input_dtype *data,
      const size_t &length,
      const std::vector<size_t> &feature_selection,
      const elem_id_vec_t &element_ids,
      const std::shared_ptr<const sample_vec_t> &samples,
      const FeatCalcParamSet &parameter_set) const {
      FASSERT(length % 2 == 0);
      size_t n_samples = length / 2;
      feature_dtype *results = new feature_dtype[n_samples];
#ifdef __INTEL_COMPILER
      #pragma simd
#endif
      for (size_t i = 0; i < n_samples; ++i) {
        results[i] = data[i + n_samples] - data[i];
      }
      return std::shared_ptr<const feature_dtype>(results, [](const feature_dtype *p){delete[] p;});
    };

    /** Calculates the surface value (testing). */
    feature_dtype calculate(
      const std::vector<size_t> &feature_selection,
      const FeatCalcParamSet &parameter_set,
      const input_dtype *data, const size_t data_step) const {
      feature_dtype result = data[ data_step * feature_selection[1] ] -
                             data[ data_step * feature_selection[0] ];
      return result;
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
                     feature_dtype,
                     annotation_dtype> &rhs)
      const {
      const auto *rhs_c = dynamic_cast<DifferenceSurfaceCalculator const *>(&rhs);
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
       ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>>(*this);
    }
#endif
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_DIFFERENCESURFACECALCULATOR_H_
