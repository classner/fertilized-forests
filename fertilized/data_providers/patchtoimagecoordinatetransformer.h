/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_PATCHTOIMAGECOORDINATETRANSFORMER_H_
#define FERTILIZED_DATA_PROVIDERS_PATCHTOIMAGECOORDINATETRANSFORMER_H_

#include <utility>
#include <vector>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../features/featcalcparamset.h"

namespace fertilized {
  /**
   * \brief Transforms local patch coordinates to image coordinates.
   */
  struct PatchToImageCoordinateTransformer {
    /**
     * \param psx Patch size in x-direction (must be a multiple of 2).
     * \param psy Patch size in y-direction (must be a multiple of 2).
     * \param psz Patch size in z-direction.
     * \param imh Image height.
     * \param imw Image width (Image depth must be \ref psz).
     * \param luc Left Upper Corner, whether to assume that the patch
     *    coordinate is specified by its left upper corner or its center.
     * \param posx The patch position (x) in the image (the position of the
     *    first patch pixel in image coordinates).
     * \param posy The patch position (y) in the image (the position of the
     *    first patch pixel in image coordinates).
     */
    inline PatchToImageCoordinateTransformer(const size_t &psx,
                                             const size_t &psy,
                                             const size_t &psz,
                                             const size_t &imh,
                                             const size_t &imw,
                                             const bool &luc,
                                             const size_t &posx = 0,
                                             const size_t &posy = 0)
    : psx(psx), psy(psy), psz(psz), psxh(psx/2), psyh(psy/2),
      imw(imw), imh(imh), posx(posx), posy(posy), luc(luc) {
      FASSERT(psx % 2 == 0);
      FASSERT(psy % 2 == 0);
    }

    typedef std::tuple<std::vector<size_t>, FeatCalcParamSet,
      EThresholdSelection, std::pair<int16_t, int16_t>>
      decision_tuple_t;

    /**
     * \brief Transforms all indices in the given decision parameters from
     *   patch to image coordinates.
     */
    inline void operator()(void* decision_param_p) const {
      decision_tuple_t *decision_params =
                        reinterpret_cast<decision_tuple_t*>(decision_param_p);
      std::vector<size_t> &ind_vec = std::get<0>(*decision_params);
      for (auto &index : ind_vec) {
        index = patch_to_image(index, imh, imw, posx, posy, luc);
      }
    }

    /**
     * \brief Transforms patch coordinates for one patch to image coordinates.
     *
     * \param raveled_coord The position within the patch in 1D coordinates.
     * \param imh image height.
     * \param imw image width.
     * \param posx x position of the patch; if \ref luc, then of the left
     *    upper corner of the patch, otherwise of its center.
     * \param posy y position of the patch; if \ref luc, then of the left
     *    upper corner of the patch, otherwise of its center.
     * \param luc Whether to assume that the patch coordinate is given by
     *    Left Upper Corner or center.
     */
    inline size_t patch_to_image(const size_t &raveled_coord,
                                 const size_t &imh,
                                 const size_t &imw,
                                 const size_t &posx,
                                 const size_t &posy,
                                 const bool &luc) const {
      size_t tx, ty, tz;
      unravel_index(raveled_coord, psy, psx, &tx, &ty, &tz);
      if (luc) {
        tx += posx;
        ty += posy;
        FASSERT(tx < imw && ty < imh);
      } else {
        FASSERT(posx >= psxh && posy >= psyh);
        tx += posx - psxh;
        ty += posy - psyh;
        FASSERT(tx < imw && ty < imh);
      }
      return ravel_indices(tx, ty, tz, imh, imw);
    };

    /**
     * \brief Calculates the raveled coordinate of the provided 3D point.
     */
    static inline size_t ravel_indices(const size_t &x,
                                       const size_t &y,
                                       const size_t &z,
                                       const size_t &h,
                                       const size_t &w) {
      FASSERT(h > 0);
      FASSERT(w > 0);
      FASSERT(x < w);
      FASSERT(y < h);
      return z * h * w + y * w + x;
    }

    /**
     * \brief Calculates the unraveled 3D coordinate from the provided 1D
     *    point.
     */
    static inline void unravel_index(const size_t &index,
                                     const size_t &h,
                                     const size_t &w,
                                     size_t *x,
                                     size_t *y,
                                     size_t *z) {
      FASSERT(h > 0);
      FASSERT(w > 0);
      // The result of division and modulo operation are automatically
      // cached and reused by the compiler. So each two lines only need
      // one division operation.
      *z = index / (w * h);
      size_t tx = index % (w * h);
      *y = tx / w;
      *x = tx % w;
    }

    /** patch size x, y, z; half patch size x, y; image width, image height. */
    size_t psx, psy, psz, psxh, psyh, imw, imh;
    /** position x, y. */
    size_t posx, posy;
    /** whether to assume patch coordinate with Left Upper Corner or center. */
    bool luc;

    /** Deep comparison. */
    inline bool operator==(PatchToImageCoordinateTransformer const &rhs)
      const {
        return psx == rhs.psx &&
               psy == rhs.psy &&
               psz == rhs.psz &&
               psxh == rhs.psxh &&
               psyh == rhs.psyh &&
               imw == rhs.imw &&
               imh == rhs.imh &&
               posx == rhs.posx &&
               posy == rhs.posy &&
               luc == rhs.luc;
    };

    #ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    inline void serialize(Archive & ar, const uint file_version) {
      ar & psx;
      ar & psxh;
      ar & psyh;
      ar & psy;
      ar & psz;
      ar & imw;
      ar & imh;
      ar & posx;
      ar & posy;
      ar & luc;
    }
    #endif

    /**
     * \brief Do not use this constructor! Required only for persistence
     * compatibility reasons.
     */
    // cppcheck-suppress uninitVar
    inline PatchToImageCoordinateTransformer() {}
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_PATCHTOIMAGECOORDINATETRANSFORMER_H_
