/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_UNCHANGEDFDATAPROVIDER_H_
#define FERTILIZED_DATA_PROVIDERS_UNCHANGEDFDATAPROVIDER_H_

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../ndarray.h"
#include "./iforestdataprovider.h"
#include "./unchangeddataprovider.h"

namespace fertilized {
  /**
   * \brief Uses unchanged data providers for each tree.
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
   * - float; uint
   * - int; uint
   * - uint8_t; uint
   * - uint8_t; int16_t
   * - double; uint
   * - double; double
   * - float; float
   * .
   * 
   * -----
   */
  template<typename input_dtype, typename annotation_dtype>
  class UnchangedFDataProvider
  : public IForestDataProvider<input_dtype, annotation_dtype> {
   public:
    typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;
    using typename fdprov_t::dprov_t;
    using typename fdprov_t::sample_t;
    using typename fdprov_t::sample_list_t;
    typedef UnchangedDataProvider<input_dtype, annotation_dtype> udprov_t;

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * Instantiations:
     * - float; uint
     * - uint8_t; uint
     * - uint8_t; int16_t
     * - double; uint
     * - double; double
     * - float; float
     * .
     * 
     * -----
     *
     * \param data_array Array<input_dtype>, 2D, row-major contiguous.
     *   The data to use, with one data sample per row.
     * \param annotation_array Array<annotation_dtype>, 2D, row-major contiguous.
     *   The annotations to use, with one annotation per row.
     */
    UnchangedFDataProvider(
                  const Array<const input_dtype, 2, 2> &data_array,
                  const Array<const annotation_dtype, 2, 2> &annotation_array)
      : data(data_array.getData()),
        annotations(annotation_array.getData()),
        data_array(data_array),
        annotation_array(annotation_array),
        samples(std::make_shared<sample_list_t>()),
        dimension(data_array.TPLMETH getSize<1>()),
        annot_dimension(annotation_array.TPLMETH getSize<1>()),
        n_samples(data_array.TPLMETH getSize<0>()),
        column_wise(false),
        step(1) {
      // Checks.
      if (data_array.TPLMETH getSize<1>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                    "feature dimension 0.");
      if (data_array.TPLMETH getSize<0>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                    "0 samples.");
      if (data_array.TPLMETH getSize<0>() != annotation_array.TPLMETH getSize<0>())
        throw Fertilized_Exception("Data and annotation counts don't match!");
      if (annotation_array.TPLMETH getSize<1>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                   "annotation dimension 0!");
      // Generate the weights, data and annotation pointers, and step sizes.
      for (size_t i = 0; i < n_samples; ++i) {
        samples -> push_back(sample_t(this -> data + i * data_array.TPLMETH getSize<1>(),
                                      this -> step,
                                      this -> annotations +
                                              i * annotation_array.TPLMETH getSize<1>(),
                                      1.f));
      }
    };

    /** Throws. */
    include_pair_t include_additional_samples(
      const sample_list_t &added_samples) {
      throw Fertilized_Exception("The unchanged (forest) data provider "
        "does not support adding additional samples.");
      //  auto assigned_ids = std::make_shared<std::vector<element_id_t>>();
      //  element_id_t max_old_id = samples -> size();

      //  for (const auto& sample : added_samples) {
      //    assigned_ids -> push_back(samples -> size());
      //    samples -> push_back(sample);
      //  }
      //  return std::make_pair(assigned_ids, max_old_id);
    };

    /** Creates the \ref UnchangedDataProvider s for each tree. */
    void create_tree_providers(
      const size_t &n,
      const usage_map_t &usage_map) {
      FASSERT(usage_map.size() == n);
      for (tree_id_t i = 0; i < static_cast<tree_id_t>(n); ++i) {
        FASSERT(check_elem_ids_ok(n_samples, *usage_map[i].first));
        FASSERT(check_elem_ids_ok(n_samples, *usage_map[i].second));
        dproviders.push_back(std::shared_ptr<dprov_t>(
          new udprov_t(
                data_array,
                annotation_array,
                samples,
                usage_map[i].first,
                usage_map[i].second)));
      }
    };

    /** Gets the sample vector. */
    std::shared_ptr<const sample_list_t> get_samples() const {
      return samples;
    };

    using fdprov_t::dproviders;
    using fdprov_t::sample_ids;

   private:
    input_dtype const *data;
    annotation_dtype const *annotations;
    Array<input_dtype const, 2, 2> data_array;
    Array<annotation_dtype const, 2, 2> annotation_array;
    const std::shared_ptr<sample_list_t> samples;

    const size_t dimension;
    const size_t annot_dimension;
    const size_t n_samples;
    const bool column_wise;
    const size_t step;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_UNCHANGEDFDATAPROVIDER_H_
