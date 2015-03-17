/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_DATA_PROVIDERS_SAMPLE_H_
#define FERTILIZED_DATA_PROVIDERS_SAMPLE_H_

#include "../global.h"
#include "../types.h"

namespace fertilized {
  /**
   * \brief Stores information about one data sample.
   *
   * This form of storage is mainly important since samples may be generated
   * by data providers on the fly, so it cannot be assumed that data has a 
   * contiguous memory layout.
   *
   * The data vectors can have a \ref data_step, but the annotations cannot and
   * must have a contiguous memory layout.
   *
   * -----
   * Available in:
   * - C++
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
  template <typename input_dtype, typename annotation_dtype>
  struct Sample {
    float weight;
    const input_dtype *data;
    size_t data_step;
    const annotation_dtype *annotation;
    // size_t annotation_step;
    size_t im_size[2];
    size_t coords[2];

    Sample(const input_dtype *data,
           const size_t &data_step,
           const annotation_dtype *annotation,  // const size_t &annotation_step,
           const float &weight)
      : weight(weight),
        data(data),
        data_step(data_step),
        annotation(annotation) {
      im_size[0] = 0;
      im_size[1] = 0;
      coords[0] = 0;
      coords[1] = 0;
    }
  };
}  // namespace fertilized
#endif  // FERTILIZED_DATA_PROVIDERS_SAMPLE_H_
