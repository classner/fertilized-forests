/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_DIRECTPATCHDIFFERENCESURFCALCULATOR_H_
#define FERTILIZED_FEATURES_DIRECTPATCHDIFFERENCESURFCALCULATOR_H_

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
#include "../data_providers/patchtoimagecoordinatetransformer.h"
#include "../util/sampling.h"
#include "./isurfacecalculator.h"
#include "./featcalcparamset.h"
#include "./_issubsdprov_dpdsc.h"

namespace fertilized {
  /**
   * \brief Calculates a feature as the difference between two data dimensions
   * of inputs.
   *
   * In contrast to the \ref DifferenceSurfaceCalculator, works with patches
   * in images directly. It only works together with a \ref SubsamplingDataProvider
   * with a \ref NoCopyPatchSampleManager, because they provide the images
   * in the correct format.
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
   * - uint8_t; int16_t; uint
   * - uint8_t; int16_t; int16_t
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DirectPatchDifferenceSurfCalculator
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
     *
     * \param psx size_t>0
     *   Horizontal patch size.
     * \param psy size_t>0
     *   Vertical patch size.
     * \param psz size_t>0
     *   Patch depth.
     * \param luc bool
     *   Whether the Left Upper Corner of a patch is used when specifying
     *   positions or its center.
     */
    DirectPatchDifferenceSurfCalculator(const size_t &psx,
                                        const size_t &psy,
                                        const size_t &psz,
                                        const bool &luc)
      : transformer(PatchToImageCoordinateTransformer(psx, psy, psz, 0, 0, luc)) {
      if (psx == 0 || psy == 0 || psz == 0) {
        throw Fertilized_Exception("Need values >0 for patch dimensions!");
      }
    }

    /** Always proposes a one-element vector with unspecified content. */
    std::vector<FeatCalcParamSet> propose_params() {
      return std::vector<FeatCalcParamSet>(1);
    };

    /** Returns false. */
    bool needs_elements_prepared() const {
      return false;
    };

    /**
     * \brief Checks compatibility to a specific data provider.
     */
    bool is_compatible_to(const IDataProvider<input_dtype, annotation_dtype> * const dprov) const {
      return _IsSubsDprov_DPDSC<input_dtype, annotation_dtype>::check(dprov);
    }

    /** Returns 2. */
    size_t required_num_features() const { return 2; }

    /** Calculates the surface value (training). */
    std::shared_ptr<const feature_dtype> calculate(
      const input_dtype *data,
      const size_t &length,
      const std::vector<size_t> &feature_selection,
      const elem_id_vec_t &element_ids,
      const std::shared_ptr<const sample_vec_t> &samples,
      const FeatCalcParamSet &parameter_set) const {
      feature_dtype *results = new feature_dtype[element_ids.size()];
      // TODO: Maybe speedup using SIMD?
      for (size_t i = 0; i < element_ids.size(); ++i) {
        const Sample<input_dtype, annotation_dtype> &sample =
                                              samples -> at(element_ids[i]);
        size_t tpos1 = transformer.patch_to_image(feature_selection[1],
                                                      sample.im_size[0],
                                                      sample.im_size[1],
                                                      sample.coords[0],
                                                      sample.coords[1],
                                                      transformer.luc);
        size_t tpos0 = transformer.patch_to_image(feature_selection[0],
                                                      sample.im_size[0],
                                                      sample.im_size[1],
                                                      sample.coords[0],
                                                      sample.coords[1],
                                                      transformer.luc);
        results[i] = sample.data[ tpos1 ] - sample.data[ tpos0 ];
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
      const auto *rhs_c = dynamic_cast<DirectPatchDifferenceSurfCalculator const *>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return transformer == rhs_c -> transformer;
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<
       ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>>(*this);
      ar & transformer;
    }
#endif
   protected:
    DirectPatchDifferenceSurfCalculator() {};

   private:
    PatchToImageCoordinateTransformer transformer;
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_DIRECTPATCHDIFFERENCESURFCALCULATOR_H_