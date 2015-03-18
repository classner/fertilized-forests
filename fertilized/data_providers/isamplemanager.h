/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_ISAMPLEMANAGER_H_
#define FERTILIZED_DATA_PROVIDERS_ISAMPLEMANAGER_H_

#include <vector>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/sampling.h"
#include "./sample.h"

namespace fertilized {
  /**
   * \brief Interface for a sample manager that loads samples when required
   * and frees memory on demand.
   *
   *
   * \ingroup fertilizeddata_providersGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * Instantiations:
   * - uint8_t; int16_t
   * - uint8_t; uint
   * .
   *
   * -----
   */
  template <typename input_dtype, typename annotation_dtype>
  class ISampleManager {
  public:
    typedef Sample<input_dtype, annotation_dtype> sample_t;
    typedef std::vector<sample_t> sample_vec_t;

    ISampleManager(const size_t &n_samples,
                   const size_t &sample_size,
                   const size_t &annot_size)
      : n_samples(n_samples),
        sample_size(sample_size),
        annot_size(annot_size),
        last_reserved_elem(0),
        max_elements(0),
        reserve_space(true) {
      if (sample_size == 0)
        throw Fertilized_Exception("Tried to create a sample manager for "
                                    "0 samples.");
      if (sample_size == 0)
        throw Fertilized_Exception("Tried to create a sample manager for "
                                    "sample size 0.");
      if (annot_size == 0)
        throw Fertilized_Exception("Tried to create a sample manager for "
                                    "annotation size 0.");
    }

    /**
     * \brief Initializes this sample manager.
     *
     * May only be called once, otherwise raises an exception!
     *
     * \param samples The sample vector. It may contain empty samples (the data
     *   pointer is a null pointer) and it will be populated on demand.
     * \param max_elements The maximum number of elements to keep
     *   simultaneously in memory.
     * \param sample_size How many elements per sample vector.
     * \param annot_size How many elements per annotation vector.
     */
    virtual void register_dprov(std::shared_ptr<sample_vec_t> samples,
                                const size_t &max_elements) {
      if (this -> samples.get() != nullptr) {
        throw Fertilized_Exception("Tried to reuse a sample manager!");
      } else {
        if (max_elements == 0) {
          throw Fertilized_Exception(
            "Need strictly positive amount of max_elements.");
        }
        this -> samples = samples;
        this -> max_elements = max_elements;
      }
      reserve_space = true;
      last_reserved_elem = 0;
    }

    /**
     * \brief Ensures that data and annotations for all samples with the
     *    given element_ids is loaded.
     *
     * If necessary, overwrites other, non-required sample data. If the
     * number of \ref element_ids is larger than \ref max_elements,
     * nevertheless all required elements are loaded (this enables to load
     * all elements to create a leaf).
     */
    void ensure_available(const elem_id_vec_t &element_ids) {
      // It is allowed to temporarily use more samples than max_elements
      // (when a leaf must be created). When calling this method, these
      // additional elements are deleted again.
      if (last_reserved_elem > max_elements) {
        // Free the space.
        if (reserve_space) {
          data_ptrs.erase(data_ptrs.begin() + max_elements,
                          data_ptrs.end());
          annot_ptrs.erase(annot_ptrs.begin() + max_elements,
                           annot_ptrs.end());
        }
        samples_available.erase(samples_available.begin() + max_elements,
                                samples_available.end());
      }
      // Reset the last_reserved_elem pointer.
      last_reserved_elem = 0;
      // Load the samples.
      for (const auto &elem_id : element_ids) {
        ensure_available(elem_id);
      }
    };

    /**
     * \brief Loads the sample with the provided \ref elem_id if required.
     */
    void ensure_available(const element_id_t &elem_id) {
      if (samples_available.size() < last_reserved_elem + 1) {
        if (reserve_space) {
        // Load the element.
        data_ptrs.emplace_back(new input_dtype[sample_size],
                               [](input_dtype *p){ delete[] p; });
        annot_ptrs.emplace_back(new annotation_dtype[annot_size],
                                [](annotation_dtype *p) { delete[] p; });
        load_sample(elem_id,
                    &((*samples)[elem_id]),
                    data_ptrs.back().get(),
                    annot_ptrs.back().get());
        } else {
          load_sample(elem_id,
                      &((*samples)[elem_id]),
                      nullptr,
                      nullptr);
        }
        samples_available.emplace_back(elem_id);
      } else {
        if (reserve_space) {
          load_sample(elem_id,
                      &((*samples)[elem_id]),
                      data_ptrs[last_reserved_elem].get(),
                      annot_ptrs[last_reserved_elem].get());
        } else {
          load_sample(elem_id,
                      &((*samples)[elem_id]),
                      nullptr,
                      nullptr);
        }
        samples_available[last_reserved_elem] = elem_id;
      }
      last_reserved_elem++;
    };

    /**
     * \brief Loads a sample and gets is leaf using the provided \ref pfunc.
     *
     * \param sample_id The samples id.
     * \param pfunc Leaf predictions function working in the current tree.
     * \param start_id If it is known that the sample reaches a certain node,
     *    the search for the leaf can start from that node. Set it to 0, if no
     *    further information is available (start from root node).
     */
    virtual node_id_t get_leaf(const node_id_t &sample_id,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)> &pfunc,
      node_id_t start_id = 0) VIRTUAL(node_id_t);

    /**
     * \brief Loads a sample into the specified \ref data_storage and
     *    \ref annot_storage.
     *
     * \param elem_id The sample id.
     * \param sample The sample object.
     * \param data_storage The memory area to use for the data.
     * \param annot_storage The memory area to use for the annotation.
     */
    virtual void load_sample(const element_id_t &elem_id,
                             sample_t *sample,
                             input_dtype *data_storage,
                             annotation_dtype *annot_storage) VIRTUAL_VOID;

    /**
     * \brief Returns the coordinate transformation function for the provided
     *    sample.
     *
     * The function is applied to the requested coordinates before getting the
     * data from the positions. This is helpful for e.g. get pixel values in
     * patches, but having a pointer to the image data as sample data. Then,
     * the coordinate transformation function can transform the coordinates
     * from patch- to image-coordinates.
     *
     * For an example, see \ref PatchToImageCoordinateTransformer.
     */
    virtual std::function<void(void*)> get_decision_transf_func(
                                                      const element_id_t &) {
      return nullptr;
    }

    const size_t n_samples;
    const size_t sample_size;
    const size_t annot_size;

  protected:
    /** The data storage pointers.
     *
     * This should be unique_ptrs. Unfortunately, C++ 11 did not specify
     * a constructor accepting a custom deleter, making it impossible to
     * use a plain memory range there (delete[] and free cannot be used, only
     * delete). Until there is a better solution, use shared_ptrs here with
     * unfortunately a little overhead. :(
     */
    std::vector<std::shared_ptr<input_dtype>> data_ptrs;
    /** The annotation storage pointers. */
    std::vector<std::shared_ptr<annotation_dtype>> annot_ptrs;
    std::shared_ptr<sample_vec_t> samples;
    /** Stores which samples are currently loaded. */
    elem_id_vec_t samples_available;
    /** The index of the last loaded element. */
    size_t last_reserved_elem;
    /** The maximum of loadable elements at the same time (may be violated!).*/
    size_t max_elements;
    /** Whether to create storage space for samples. */
    bool reserve_space;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_ISAMPLEMANAGER_H_
