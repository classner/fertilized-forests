/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_NOCOPYPATCHSAMPLEMANAGER_H_
#define FERTILIZED_DATA_PROVIDERS_NOCOPYPATCHSAMPLEMANAGER_H_

#include <vector>
#include <type_traits>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "./patchsamplemanager.h"

namespace fertilized {
  /**
   * \brief A sample manager for Hough forests that limits the number of
   * patches for one node, but does not copy anything but uses direct access
   * tricks.
   *
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
  class NoCopyPatchSampleManager : public PatchSampleManager<input_dtype, annotation_dtype> {
   public:
    using typename ISampleManager<input_dtype, annotation_dtype>::sample_t;
    using typename ISampleManager<input_dtype, annotation_dtype>::sample_vec_t;
    using ISampleManager<input_dtype, annotation_dtype>::annot_size;
    using PatchSampleManager<input_dtype, annotation_dtype>::annot_ptrs;
    using PatchSampleManager<input_dtype, annotation_dtype>::patch_descs;
    using PatchSampleManager<input_dtype, annotation_dtype>::n_positives;
    using PatchSampleManager<input_dtype, annotation_dtype>::images;
    using PatchSampleManager<input_dtype, annotation_dtype>::reserve_space;
    using PatchSampleManager<input_dtype, annotation_dtype>::trans_funcs;
    using PatchSampleManager<input_dtype, annotation_dtype>::samples;

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
    NoCopyPatchSampleManager(
              const std::vector<Array<const input_dtype, 3, 3>> &images,
              const Array<const annotation_dtype, 2, 2> &patch_descs,
              const size_t &n_positives,
              const size_t &patch_size_z,
              const size_t &patch_size_y,
              const size_t &patch_size_x,
              const bool &patches_luc = false)
    : PatchSampleManager<input_dtype, annotation_dtype>(
                         images,
                         patch_descs,
                         n_positives,
                         patch_size_z,
                         patch_size_y,
                         patch_size_x,
                         patches_luc)
    {
      static_assert(std::is_integral<annotation_dtype>::value,
        "The PatchSampleManagers are only defined for integral annotation!");
    }

    /** Registers the data provider. */
    void register_dprov(std::shared_ptr<sample_vec_t> samples,
                        const size_t &max_elements) {
      ISampleManager<input_dtype, annotation_dtype>::register_dprov(samples,
                                                                    max_elements);
      for (size_t elem_id = 0; elem_id < samples -> size(); ++elem_id) {
        annot_ptrs.emplace_back(new annotation_dtype[annot_size]);
        annotation_dtype *annot_storage = annot_ptrs.back().get();
        const auto &sample_info = patch_descs[elem_id];
        const annotation_dtype img_id = sample_info[0];
        const annotation_dtype pos_x = sample_info[1];
        const annotation_dtype pos_y = sample_info[2];
        // Put the annotations in the annotation field.
        annot_storage[0] = static_cast<annotation_dtype>(elem_id < n_positives);
        annot_storage[1] = sample_info[3];
        annot_storage[2] = sample_info[4];
        // Initialize the sample values.
        sample_t *sample = &(samples -> at(elem_id));
        sample -> data = images[img_id].getData();
        sample -> data_step = 1;
        sample -> annotation = annot_storage;
        sample -> im_size[0] = images[img_id].TPLMETH getSize<1>();
        sample -> im_size[1] = images[img_id].TPLMETH getSize<2>();
        sample -> coords[0] = pos_x;
        sample -> coords[1] = pos_y;
      }
      reserve_space = false;
    }

    /** Does nothing. */
    void load_sample(const element_id_t &elem_id,
                     sample_t *sample,
                     input_dtype *data_storage,
                     annotation_dtype *annot_storage) {}

    /** Creates the appropriate decision transfer function to use direct access. */
    std::function<void(void*)> get_decision_transf_func(
                                                const element_id_t &elem_id) {
      PatchToImageCoordinateTransformer &tf = trans_funcs[patch_descs[elem_id][0]];
      tf.posx = (samples -> at(elem_id).coords)[0];
      tf.posy = (samples -> at(elem_id).coords)[1];
      return tf;
    }
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_NOCOPYPATCHSAMPLEMANAGER_H_