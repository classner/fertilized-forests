/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_PATCHSAMPLEMANAGER_H_
#define FERTILIZED_DATA_PROVIDERS_PATCHSAMPLEMANAGER_H_

#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <type_traits>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/sampling.h"
#include "../ndarray.h"
#include "./isamplemanager.h"
#include "./patchtoimagecoordinatetransformer.h"

namespace fertilized {
  /**
   * \brief Manages patch samples for the \ref SubsamlingDataProvider.
   *
   * Loads patches from the images on-demand and always has only
   * the maximum allowed number of patches in memory. This exception
   * might only be violated at leafs.
   *
   * \ingroup fertilizeddata_providersGroup
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
  template <typename input_dtype, typename annotation_dtype>
  class PatchSampleManager : public ISampleManager<input_dtype,
                                                   annotation_dtype> {
  public:
    using typename ISampleManager<input_dtype, annotation_dtype>::sample_t;
    using ISampleManager<input_dtype, annotation_dtype>::n_samples;

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
     * \param images vector(Array<input_dtype>, 3D, row-major contiguous)
     *   Images of shape (n_features, height, width).
     * \param patch_descs Array<annotation_dtype, 3D, row-major contiguous)
     *   2D array in row major format with
     *   the patch descriptions. A patch description consists of 5 values:
     *   image id, position x, y, offset x, y (from the object to detect,
     *   so that position x + offset x = object x).
     * \param n_positives size_t>0
     *   The first n_positive examples are interpreted as
     *   positives, the rest as negatives (they get an according annotation).
     * \param patch_size_z size_t>0
     *   Patch depth.
     * \param patch_size_y size_t>0
     *   Patch height.
     * \param patch_size_x size_t>0
     *   Patch width.
     * \param patches_luc bool
     *   If true, it is assumed that the patch descriptions
     *   contain the _L_eft _U_pper _C_orners of the patches. Otherwise, it
     *   it assumed they contain the center points. In the luc case, the patch
     *   goes from (including) position{x,y} to (excluding)
     *   position{x,y}+{width, height}. In the center case, the patch goes
     *   from (including) position{x,y}-{width//2, height//2} up to (excluding)
     *   position{x,y}-{(width//2-width), (height//2-height)}. Default: false.
     */
    PatchSampleManager(
              const std::vector<Array<const input_dtype, 3, 3>> &images,
              const Array<const annotation_dtype, 2, 2> &patch_descs,
              const size_t &n_positives,
              const size_t &patch_size_z,
              const size_t &patch_size_y,
              const size_t &patch_size_x,
              const bool &patches_luc = false)
    : patches_luc(patches_luc),
      images(images),
      patch_descs(patch_descs),
      trans_funcs(),
      patch_size_x(patch_size_x),
      patch_size_y(patch_size_y),
      patch_size_z(patch_size_z),
      n_positives(n_positives),
      ISampleManager<input_dtype, annotation_dtype>(
                     patch_descs.TPLMETH getSize<0>(),
                     patch_size_z * patch_size_y * patch_size_x,
                     patch_descs.TPLMETH getSize<1>() - 2) {
      // Checks.
      if (n_positives == 0) {
        throw Fertilized_Exception("At least one positive example is needed!");
      }
      if (n_positives >= patch_descs.TPLMETH getSize<0>()) {
        throw Fertilized_Exception("Too many positive samples!");
      }
      if (patch_size_x == 0 || patch_size_y == 0 || patch_size_z == 0) {
        throw Fertilized_Exception("A patch size >= 1 is required in all "
          "dimensions!");
      }
      if (patch_descs.TPLMETH getSize<1>() != 5) {
        throw Fertilized_Exception("A hough annotation dimension of 2 is required.");
      }
      static_assert(std::is_integral<annotation_dtype>::value,
        "The PatchSampleManagers are only defined for integral annotation!");
      // Check the patch descriptions.
      std::set<size_t> images_used;
      for (size_t sidx = 0; sidx < n_samples; ++sidx) {
        if (patch_descs[sidx][0] < 0 ||
            patch_descs[sidx][0] >= images.size()) {
          throw Fertilized_Exception("Invalid image id in patch description " +
            std::to_string(sidx));
        }
        size_t im_id = static_cast<size_t>(patch_descs[sidx][0]);
        images_used.insert(im_id);
        int correction_y = 0;
        int correction_x = 0;
        if (!patches_luc) {
          correction_y = static_cast<int>(patch_size_y / 2);
          correction_x = static_cast<int>(patch_size_x / 2);
        }
        int position_y = static_cast<int>(patch_descs[sidx][2]);
        int position_x = static_cast<int>(patch_descs[sidx][1]);
        int offset_y = static_cast<int>(patch_descs[sidx][4]);
        int offset_x = static_cast<int>(patch_descs[sidx][3]);
        size_t im_height = images[im_id].TPLMETH getSize<1>();
        size_t im_width = images[im_id].TPLMETH getSize<2>();
        if (im_height == 0 || im_width == 0) {
          throw Fertilized_Exception("Image size is 0 for image " +
                                     std::to_string(im_id));
        }
        // Check patch position.
        if (position_y-correction_y < 0 ||
            position_y-correction_y+patch_size_y > im_height ||
            position_x-correction_x < 0 ||
            position_x-correction_x+patch_size_x > im_width) {
          throw Fertilized_Exception("Invalid patch location for patch " +
            std::to_string(sidx) + ": position " + std::to_string(position_x) +
            ", " + std::to_string(position_y) + " (x, y) for image size " +
            std::to_string(im_width) + ", " + std::to_string(im_height) +
            " (width, height) for patch size " + std::to_string(patch_size_x) +
            ", " + std::to_string(patch_size_y) + " (width, height).");
        }
        if (patches_luc) {
          correction_y = static_cast<int>(patch_size_y / 2);
          correction_x = static_cast<int>(patch_size_x / 2);
        } else {
          correction_y = 0;
          correction_x = 0;
        }
        // Check offset for plausibility.
        if (position_y+correction_y+offset_y < 0 ||
            position_y+correction_y+offset_y > im_height ||
            position_x+correction_x+offset_x < 0 ||
            position_x+correction_x+offset_x > im_width) {
          throw Fertilized_Exception("Invalid object location for patch " +
                                     std::to_string(sidx));
        }
      }
      std::vector<size_t> full_range = std::vector<size_t>(images.size());
      std::iota(full_range.begin(), full_range.end(), 0);
      std::vector<size_t> unused_ids = std::vector<size_t>(images.size());
      auto last_diff = std::set_difference(full_range.begin(), full_range.end(),
                                           images_used.begin(), images_used.end(),
                                           unused_ids.begin());
      if (last_diff - unused_ids.begin() > 0) {
        std::cout << "Warning: there are " << (last_diff - unused_ids.begin())
          << " unused images!";
      }
      // Initialize the transformation functions.
      for (size_t i = 0; i < images.size(); ++i) {
        trans_funcs.emplace_back(
          PatchToImageCoordinateTransformer(patch_size_x,
                                            patch_size_y,
                                            patch_size_z,
                                            images[i].TPLMETH getSize<1>(),
                                            images[i].TPLMETH getSize<2>(),
                                            patches_luc));
      }
    }

    /** Loads the specified sample into memory. */
    virtual void load_sample(const element_id_t &elem_id,
                             sample_t *sample,
                             input_dtype *data_storage,
                             annotation_dtype *annot_storage) {
      const annotation_dtype img_id = patch_descs[elem_id][0];
      const annotation_dtype pos_x = patch_descs[elem_id][1];
      const annotation_dtype pos_y = patch_descs[elem_id][2];
      // Store the patch in the data field.
      extract_patch(images[img_id].getData(),
                    data_storage,
                    pos_x - patch_size_x / 2,
                    pos_y - patch_size_y / 2,
                    patch_size_z,
                    patch_size_y,
                    patch_size_x,
                    images[img_id].TPLMETH getSize<1>(),
                    images[img_id].TPLMETH getSize<2>());
      // Put the annotations in the annotation field.
      annot_storage[0] = static_cast<annotation_dtype>(elem_id < n_positives);
      annot_storage[1] = patch_descs[elem_id][3];
      annot_storage[2] = patch_descs[elem_id][4];
      // Initialize the sample values.
      sample -> data = data_storage;
      sample -> data_step = 1;
      sample -> annotation = annot_storage;
    };

    /** Gets the leaf in the current tree for the specified sample. */
    node_id_t get_leaf(const node_id_t &sample_id,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)> &pfunc,
      node_id_t start_id = 0) {
      // Get the image id.
      const auto &sample_info = patch_descs[sample_id];
      const annotation_dtype img_id = sample_info[0];
      const annotation_dtype pos_x = sample_info[1];
      const annotation_dtype pos_y = sample_info[2];
      trans_funcs[ img_id ].posx = static_cast<size_t>(pos_x);
      trans_funcs[ img_id ].posy = static_cast<size_t>(pos_y);
      return pfunc(images[img_id].getData(), 1, start_id, trans_funcs[ img_id ]);
    };

    /**
     * \brief Extracts the specified patch to the \ref target memory.
     *
     * \param img The image to extract the patch from (row major order).
     * \param target The target memmory.
     * \param left_x The left border of the patch.
     * \param left_y The top border of the patch.
     * \param patch_z The patch size in z-coordinates.
     * \param patch_y The patch size in y-coordinates.
     * \param patch_x The patch size in x-coordinates.
     * \param im_size_y Image height.
     * \param im_size_x Image width.
     */
    static void extract_patch(const input_dtype *img,
                              input_dtype *target,
                              const size_t &left_x,
                              const size_t &left_y,
                              const size_t &patch_z,
                              const size_t &patch_y,
                              const size_t &patch_x,
                              const size_t &im_size_y,
                              const size_t &im_size_x) {
      const input_dtype *im_ptr;
      input_dtype *target_ptr = target;
      for (size_t z_index = 0; z_index < patch_z; ++z_index) {
        im_ptr = img + z_index * im_size_y * im_size_x +
                       left_y * im_size_x +
                       left_x;
        for (size_t y_index = 0; y_index < patch_y; ++y_index) {
          std::copy(im_ptr, im_ptr + patch_x, target_ptr);
          target_ptr += patch_x;
          im_ptr += im_size_x;
        }
      }
    };

    const bool patches_luc;

   protected:
    std::vector<Array<const input_dtype, 3, 3>> images;
    Array<const annotation_dtype, 2, 2> patch_descs;
    std::vector<PatchToImageCoordinateTransformer> trans_funcs;
    size_t patch_size_x, patch_size_y, patch_size_z;
    size_t n_positives;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_PATCHSAMPLEMANAGER_H_