/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_LINEARSURFACECALCULATOR_H_
#define FERTILIZED_FEATURES_LINEARSURFACECALCULATOR_H_

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
   * \brief Calculates a feature as linear combination of inputs.
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
   * - double; double
   * - double; uint
   * .
   *
   * -----
   */
  template <typename input_dtype, typename annotation_dtype>
  class LinearSurfaceCalculator
    : public ISurfaceCalculator<input_dtype, float, annotation_dtype> {
   public:
    using typename ISurfaceCalculator<input_dtype, float, annotation_dtype>::sample_vec_t;
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
     * \param n_params_per_feat_sel size_t>0
     *   The number of linear configurations to evaluate per feature selection.
     * \param n_comb_dims size_t>0
     *   The dimensionality of the linear surface. Default: 2.
     * \param random_seed uint>0
     *   Seed for the RNG. Default: 1.
     */
    LinearSurfaceCalculator(const size_t &n_params_per_feat_sel,
                                    const size_t &n_comb_dims=2,
                                    const uint &random_seed=1)
      : random_engine(std::make_shared<std::mt19937>(random_seed)),
        n_dims(n_comb_dims),
        n_params_per_feature_sel(n_params_per_feat_sel),
        weight_dist(std::uniform_real_distribution<float>(-1.f, 1.f))  {
      if (n_comb_dims < 2 || n_comb_dims > 3)
        throw Fertilized_Exception("Need more than one dimension for a "
        "linear feature, and only 3 are allowed at max.");
    }

    /** Get the next set of parameters. */
    std::vector<FeatCalcParamSet> propose_params() {
      std::vector<FeatCalcParamSet> ret_vec;
      ret_vec.reserve(n_params_per_feature_sel);
      for (size_t i = 0; i < n_params_per_feature_sel; ++i) {
        ret_vec.emplace(ret_vec.end());
        float magnitude = 0.f;
        while (magnitude == 0.f) {
          for (size_t j = 0; j < n_dims; ++j) {
            float val = weight_dist(*random_engine);
            ret_vec[i].weights[j] = val;
            magnitude += val * val;
          }
        }
        magnitude = sqrtf(magnitude);
#ifdef __INTEL_COMPILER
        #pragma simd
#endif
        for (size_t j = 0; j < n_dims; ++j) {
          ret_vec[i].weights[j] /= magnitude;
        }
      }
      return ret_vec;
    };

    /** Gets n_comb_dims as specified in the constructor. */
    size_t required_num_features() const { return n_dims; }

    /** Calculate a surface value (training). */
    std::shared_ptr<const float> calculate(
      const input_dtype *data,
      const size_t &length,
      const std::vector<size_t> &feature_selection,
      const elem_id_vec_t &element_ids,
      const std::shared_ptr<const sample_vec_t> &samples,
      const FeatCalcParamSet &parameter_set) const {
      FASSERT(length % n_dims == 0);
      size_t n_samples = length / n_dims;
      float *results = new float[n_samples];
      for (size_t i = 0; i < n_samples; ++i) {
        results[i] = 0.f;
        for (size_t j = 0; j < n_dims; ++j) {
          results[i] += static_cast<float>(data[i + j * n_samples]) * parameter_set.weights[j]; 
        }
      }
      return std::shared_ptr<const float>(results, [](const float *p){delete[] p;});
    };

    /** Calculate a surface value (testing). */
    float calculate(
      const std::vector<size_t> &feature_selection,
      const FeatCalcParamSet &parameter_set,
      const input_dtype *data, const size_t data_step) const {
      float result = 0.f;
      for (size_t j = 0; j < n_dims; ++j) {
        result += static_cast<float>(data[ data_step * feature_selection[j] ]) * parameter_set.weights[j]; 
      }
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
    bool operator==(const ISurfaceCalculator<input_dtype, float, annotation_dtype> &rhs)
      const {
      const auto *rhs_c = dynamic_cast<LinearSurfaceCalculator const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return *random_engine == *(rhs_c -> random_engine) &&
               n_dims == rhs_c -> n_dims &&
               n_params_per_feature_sel == rhs_c -> n_params_per_feature_sel;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<
       ISurfaceCalculator<input_dtype, float, annotation_dtype>>(*this);
      ar & random_engine;
      ar & n_dims;
      ar & n_params_per_feature_sel;
    }
#endif
  protected:
    LinearSurfaceCalculator()
      : weight_dist(std::uniform_real_distribution<float>(-1.f, 1.f)) {}

  private:
    std::shared_ptr<std::mt19937> random_engine;
    size_t n_dims;
    size_t n_params_per_feature_sel;
    std::uniform_real_distribution<float> weight_dist;
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_LINEARSURFACECALCULATOR_H_
