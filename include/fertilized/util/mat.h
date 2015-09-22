/* Author: Christoph Lassner */
#pragma once
#ifndef FERTILIZED_UTIL_MAT_H_
#define FERTILIZED_UTIL_MAT_H_

#include <vector>
#include <random>
#include <type_traits>

#include "../global.h"

namespace fertilized {
  /**
   * \brief Simple replacement for Matrix-Vector multiplication.
   */
  template <typename T>
  std::vector<T> matvec(const T* matrix,
                        const T* vec,
                        const size_t &mat_rows,
                        const size_t &mat_cols) {
    std::vector<T> result = std::vector<T>(mat_rows);
    T sum;
    const T *mat_ptr = matrix;
    for (size_t row = 0; row < mat_rows; ++row) {
      sum = 0;
      for (size_t col = 0; col < mat_cols; ++col) {
        sum += *(mat_ptr++) * vec[ col ];
      }
      result[ row ] = sum;
    }
    return result;
  };


  /**
   * \brief Simple replacement for Vector-Vector multiplication.
   */
  template <typename T>
  T vecvec(const std::vector<T> vec1,
           const std::vector<T> vec2) {
    FASSERT(vec1.size() == vec2.size());
    T sum = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
      sum += vec1[i] * vec2[i];
    }
    return sum;
  }
};  // namespace fertilized
#endif  // FERTILIZED_UTIL_MAT_H_
