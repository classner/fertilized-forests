/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_QUADRATICSURFACECALCULATOR_H_
#define FERTILIZED_FEATURES_QUADRATICSURFACECALCULATOR_H_

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
#include "../util/mat.h"
#include "./isurfacecalculator.h"
#include "./featcalcparamset.h"

namespace fertilized {
  /**
   * \brief Calculates a feature as the response value of a quadratic
   * surface (see CriminisiShotton 2013, p. 15). Currently only supports two
   * feature dimensions.
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
  class QuadraticSurfaceCalculator
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
     *   The number of surfaces to evaluate per feature selection.
     * \param min_max_vals vector<float>
     *   The relevant range for each feature dimension.
     * \param random_seed uint>0
     *   Seed for the RNG.
     */
    QuadraticSurfaceCalculator(const size_t &n_params_per_feat_sel,
                               const std::vector<float> &min_max_vals,
                               const uint &random_seed=1)
      : random_engine(std::make_shared<std::mt19937>(random_seed)),
        n_params_per_feature_sel(n_params_per_feat_sel),
        n_dims(2), min_max_vals(min_max_vals),
        min_max_ranges(min_max_vals.size() / 2),
        weight_dist(std::uniform_real_distribution<float>(-1.f, 1.f))  {
      FASSERT(min_max_vals.size() % 2 == 0);
      if (n_params_per_feature_sel == 0) {
        throw Fertilized_Exception("The number of quadratic surface dimensions must be >0!");
      }
      if (min_max_vals.size() % 2 != 0) {
        throw Fertilized_Exception("The min_max_vals must contain an even number of elements!");
      }
      for (size_t i = 0; i < min_max_vals.size() / 2; ++i) {
        min_max_ranges[i] = min_max_vals[ i * 2 + 1 ] -
                            min_max_vals[ i * 2 ];
      }
    }

    /** Propose the next set of parameters. */
    std::vector<FeatCalcParamSet> propose_params() {
      std::vector<FeatCalcParamSet> ret_vec;
      ret_vec.reserve(n_params_per_feature_sel);
      for (size_t i = 0; i < n_params_per_feature_sel; ++i) {
        ret_vec.emplace(ret_vec.end());
        float magnitude = 0.f;
        while (magnitude == 0.f) {
          for (size_t j = 0; j < 9; ++j) {
            float val = weight_dist(*random_engine);
            ret_vec[i].weights[j] = val;
            magnitude += val * val;
          }
        }
        magnitude = sqrtf(magnitude);
#ifdef __INTEL_COMPILER
        #pragma simd
#endif
        for (size_t j = 0; j < 9; ++j) {
          ret_vec[i].weights[j] /= magnitude;
        }
        // Draw offset vectors for each dimension.
        ret_vec[i].offsets[0] = (weight_dist(*random_engine) + 1.f) / 0.5f;
        ret_vec[i].offsets[1] = (weight_dist(*random_engine) + 1.f) / 0.5f;
      }
      return ret_vec;
    };

    /** Get n_dims (currently always 2). */
    size_t required_num_features() const { return n_dims; }

    /** Get the surface value when training. */
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
      std::vector<float> tmp = std::vector<float>(3);
      tmp[2] = 1.f;
      for (size_t i = 0; i < n_samples; ++i) {
        for (size_t j = 0; j < n_dims; ++j) {
          tmp[j] = static_cast<float>(data[i + j * n_samples]) -
                    (min_max_vals[feature_selection[j] * 2] +
                     min_max_ranges[feature_selection[j]] * parameter_set.offsets[j]);
        }
        results[i] = vecvec(tmp, matvec(parameter_set.weights, tmp.data(), 3, 3));
      }
      return std::shared_ptr<const float>(results, [](const float *p){delete[] p;});
    };

    /** Get the surface value (testing). */
    float calculate(
      const std::vector<size_t> &feature_selection,
      const FeatCalcParamSet &parameter_set,
      const input_dtype *data, const size_t data_step) const {
      std::vector<float> tmp = std::vector<float>(3);
      tmp[2] = 1.f;
      for (size_t j = 0; j < n_dims; ++j) {
        tmp[j] = static_cast<float>(data[data_step * feature_selection[j]]) -
                   (min_max_vals[feature_selection[j] * 2] +
                    min_max_ranges[feature_selection[j]] * parameter_set.offsets[j]);
      }
      return vecvec(tmp, matvec(parameter_set.weights, tmp.data(), 3, 3));
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
      const auto *rhs_c = dynamic_cast<QuadraticSurfaceCalculator const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return *random_engine == *(rhs_c -> random_engine) &&
               n_dims == rhs_c -> n_dims &&
               n_params_per_feature_sel == rhs_c -> n_params_per_feature_sel &&
               min_max_vals == rhs_c -> min_max_vals &&
               min_max_ranges == rhs_c -> min_max_ranges;
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
      ar & min_max_vals;
      ar & min_max_ranges;
    }
#endif
  protected:
    QuadraticSurfaceCalculator()
      : weight_dist(std::uniform_real_distribution<float>(-1.f, 1.f)) {}

  private:
    std::shared_ptr<std::mt19937> random_engine;
    std::vector<float> min_max_vals;
    std::vector<float> min_max_ranges;
    size_t n_dims;
    size_t n_params_per_feature_sel;
    std::uniform_real_distribution<float> weight_dist;
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_QUADRATICSURFACECALCULATOR_H_
