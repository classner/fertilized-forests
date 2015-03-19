/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_UNCHANGEDDATAPROVIDER_H_
#define FERTILIZED_DATA_PROVIDERS_UNCHANGEDDATAPROVIDER_H_

#include <vector>
#include <functional>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../ndarray.h"
#include "./idataprovider.h"

namespace fertilized {
  using ndarray::Array;

  /**
   * \brief Uses the provided data unchanged throughout the training.
   *
   * It builds its sample database from two pointer on memory arrays with
   * data and annotations. Both must be provided in contiguous layout. The
   * data (but not the annotations!) can be provided row- or column-wise.
   * Column-wise layout is to be preferred, since it has more locality for 
   * most optimization processes.
   *
   * The annotations MUST always be provided in row major order, independent
   * of the provided value for \ref column_wise.
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
  class UnchangedDataProvider :
    public IDataProvider<input_dtype, annotation_dtype> {
   public:
    typedef IDataProvider<input_dtype, annotation_dtype> data_prov_t;
    using typename data_prov_t::sample_t;
    using typename data_prov_t::sample_list_t;
    using data_prov_t::feat_vec_dim;

    /**
     *
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
    UnchangedDataProvider(const Array<const input_dtype, 2, 2> &data,
                          const Array<const annotation_dtype, 2, 2> &annotations) 
      : data_array(data),
        annotation_array(annotations),
        data_prov_t(data.TPLMETH getSize<1>(), annotations.TPLMETH getSize<1>()) {
      // Checks.
      if (data.TPLMETH getSize<1>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                    "feature dimension 0.");
      if (data.TPLMETH getSize<0>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                    "0 samples.");
      if (data.TPLMETH getSize<0>() != annotations.TPLMETH getSize<0>())
        throw Fertilized_Exception("Data and annotation counts don't match!");
      if (annotations.TPLMETH getSize<1>() == 0)
        throw Fertilized_Exception("Tried to create a data provider for "
                                   "annotation dimension 0!");
      this -> data = data.getData();
      this -> annotations = annotations.getData();
      this -> n_samples = data.TPLMETH getSize<0>();
      this -> column_wise = false;
      this -> step = 1;
      this -> samples = std::make_shared<sample_list_t>();
      this -> training_ids = std::make_shared<elem_id_vec_t>();
      this -> validation_ids = std::make_shared<elem_id_vec_t>();
      // Generate the weights, data and annotation pointers, and step sizes.
      for (size_t i = 0; i < n_samples; ++i) {
        samples -> push_back(sample_t(this -> data + i * data.TPLMETH getSize<1>(),
                                      this -> step,
                                      this -> annotations + i * annotations.TPLMETH getSize<1>(),
                                      1.f));
        training_ids -> push_back(i);
      }
      // Check that the weights are setup ok (wrt to numeric limits).
      FASSERT(check_sample_weights_ok(*samples, *training_ids));
    }

    /**
     * \brief Constructor for the \ref UnchangedForestDataProvider.
     *
     * For this constructor, the sample list must already have been
     * constructed. It mainly acts as a proxy object.
     */
    UnchangedDataProvider(
      const Array<const input_dtype, 2, 2> &data_array,
      const Array<const annotation_dtype, 2, 2> &annotation_array,
      const std::shared_ptr<sample_list_t> &loaded_samples,
      const std::shared_ptr<std::vector<element_id_t>> &training_ids,
      const std::shared_ptr<std::vector<element_id_t>> &validation_ids)
      : data(data_array.getData()),
        annotations(annotation_array.getData()),  
        data_array(data_array),
        annotation_array(annotation_array),
        samples(loaded_samples),
        training_ids(training_ids),
        validation_ids(validation_ids),
        n_samples(data_array.TPLMETH getSize<0>()),
        column_wise(false),
        step(1),
        data_prov_t(data_array.TPLMETH getSize<1>(),
                    annotation_array.TPLMETH getSize<1>()) {
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
    };

    /** \brief Does nothing. */
    void optimize_set_for_node(
      const node_id_t &node_id,
      const uint &depth,
      const std::function<node_id_t(const input_dtype*,
                                    const size_t&,
                                    const node_id_t &,
                                    const std::function<void(void*)>&)>
                                      node_predictor,
      std::shared_ptr<elem_id_vec_t> &element_list) {}

    /** \brief Returns a list of all sample ids. */
    std::shared_ptr<const elem_id_vec_t> get_initial_sample_list() const  {
      return training_ids;
    };

    /** Gets the sample vector. */
    std::shared_ptr<const sample_list_t> get_samples() const {
      return samples;
    };

    /** Gets the validation data vector. */
    std::shared_ptr<const elem_id_vec_t> get_validation_sample_list() const {
      return validation_ids;
    }

    /** \brief Always returns an empty vector. */
    const std::vector<sample_t> get_added_samples() {
      return std::vector<sample_t>();
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void add_to_training_set(const std::vector<sample_t> &samples) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void remove_from_training_set(
      const std::vector<element_id_t> &sample_ids) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void add_to_validation_set(const std::vector<sample_t> &samples) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** \brief Can't handle additional samples; throws an exception. */
    void remove_from_validation_set(
      const std::vector<element_id_t> &sample_ids) {
      throw Fertilized_Exception("Feature not implemented.");
    };

    /** Gets the number of samples. */
    size_t get_n_samples() {
      return n_samples;
    };

    /** Gets whether the data is stored column wise. So far, always returns false. */
    bool get_column_wise() {
      return column_wise;
    };

    /** Does nothing. */
    void track_child_nodes(node_id_t node_id,
      node_id_t left_id, node_id_t right_id) {}

   private:
    input_dtype const *data;
    annotation_dtype const *annotations;
    Array<input_dtype const, 2, 2> data_array;
    Array<annotation_dtype const, 2, 2> annotation_array;
    std::shared_ptr<sample_list_t> samples;
    std::shared_ptr<elem_id_vec_t> training_ids;
    std::shared_ptr<elem_id_vec_t> validation_ids;

    size_t n_samples;
    bool column_wise;
    size_t step;
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_UNCHANGEDDATAPROVIDER_H_
