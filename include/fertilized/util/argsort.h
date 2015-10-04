/* Author: Christoph Lassner */
#pragma once
#ifndef FERTILIZED_UTIL_ARGSORT_H_
#define FERTILIZED_UTIL_ARGSORT_H_

#include <vector>
#include <random>
#include <type_traits>
#include <algorithm>

#include "../global.h"

namespace fertilized {
  /**
   * \brief Highly efficient argsort realized with few STL commands.
   *
   * Inspired by http://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes.
   *
   * \param v Vector to sort.
   * \param n Number of vector elements.
   * \return Sorting permutation.
   */
  template <typename T>
  static std::vector<size_t> argsort(const T *v, const size_t n) {
    // Initialize original index vector.
    std::vector<size_t> idx(n);
    std::iota(idx.begin(), idx.end(), 0);

    // Sort the indexes based on values in v.
    std::sort(idx.begin(), idx.end(),
      [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });

    return idx;
  };

  /**
   * \brief Highly efficient argsort realized with few STL commands.
   *
   * Inspired by http://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes.
   *
   * \param v Vector to sort.
   * \return Sorting permutation.
   */
  template <typename T>
  static std::vector<size_t> argsort(const std::vector<T> &v) {
    return argsort(&v[0], v.size());
  };
};  // namespace fertilized
#endif  // FERTILIZED_UTIL_ARGSORT_H_
