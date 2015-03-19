/* Author: Christoph Lassner */
#pragma once
#ifndef FERTILIZED_UTIL_CHECKS_H_
#define FERTILIZED_UTIL_CHECKS_H_

#include <type_traits>
#include <vector>
#include <limits>
#include <functional>
//#ifndef __MIC__
#include <algorithm>
//#endif

#include "../global.h"

namespace fertilized {
  template <typename dtype, typename atype>
  struct Sample;

  /**
   * \brief Tests whether the sum of all elements in vec is less than limit.
   */
  template <typename T>
  static bool safe_pos_sum_lessoe_than(const std::vector<T> &vec,
                                       const T &limit) {
    if (!std::is_arithmetic<T>()) { 
      // This case should've been already detected at compile time because
      // of the use of std::numeric_limits in the function later on, but
      // better be safe.
      throw Fertilized_Exception("The safe_pos_sum_lessoe_than function can "
        "only be called for arithmetic type vectors.");
    }
    T sum_so_far = static_cast<T>(0);
    for (size_t i = 0; i < vec.size(); ++i) {
      if (vec[i] < static_cast<T>(0) || limit - vec[i] < sum_so_far) {
        return false;
      } else {
        sum_so_far += vec[i];
      }
    }
    return true;
  };

  /**
   * \brief Tests whether the sum of all elements in vec1 and vec2 is less than limit.
   */
  template <typename T>
  static bool safe_pos_sum_lessoe_than(const std::vector<T> &vec1,
                                       const std::vector<T> &vec2,
                                       const T &limit) {
    std::vector<T> joined;
    joined.insert(joined.end(), vec1.begin(), vec1.end());
    joined.insert(joined.end(), vec2.begin(), vec2.end());
    return safe_pos_sum_lessoe_than(joined, limit);
  };

  /**
   * \brief Tests whether the sum of all elements in vec is less than the numeric limit of its type.
   */
  template <typename T>
  static bool safe_pos_sum_lessoe_than(const std::vector<T> &vec) {
    return safe_pos_sum_lessoe_than(vec, std::numeric_limits<T>::max());
  };

  /**
   * \brief Tests whether the sum of all elements in vec1 and vec2 is less than the numeric limit of their type.
   */
  template <typename T>
  static bool safe_pos_sum_lessoe_than(const std::vector<T> &vec1,
                                       const std::vector<T> &vec2) {
    return safe_pos_sum_lessoe_than(vec1, vec2, std::numeric_limits<T>::max());
  };

  /**
   * \brief Tests whether all element ids are valid.
   */
  static bool check_elem_ids_ok(const size_t &n_samples,
                                const std::vector<size_t> &elem_ids) {
//#ifndef __MIC__
    return elem_ids.end() == std::find_if(elem_ids.begin(), elem_ids.end(),
      std::bind2nd(std::greater_equal<size_t>(), n_samples));
//#else
//    return true;
//#endif
  }

  /**
   * \brief Tests whether the sum of sample weights is less than the numeric limit.
   */
  template <typename I, typename A>
  static bool check_sample_weights_ok(const std::vector<Sample<I, A>> &samples,
                                      const std::vector<size_t> &elem_ids) {
    if (!check_elem_ids_ok(samples.size(), elem_ids))
      return false;
    // Create the weight vector.
    std::vector<float> weights(elem_ids.size());
    for (size_t i = 0; i < elem_ids.size(); ++i) {
      weights[i] = samples[ elem_ids[i] ].weight;
    }
    return safe_pos_sum_lessoe_than(weights);
  }

  /**
   * \brief Tests whether the class annotations of the given samples are in the appropriate range.
   */
  template <typename I, typename A>
  static bool check_sample_classes_ok(const std::vector<Sample<I, A>> &samples,
                                      const std::vector<size_t> &elem_ids,
                                      const size_t &n_classes) {
    if (!check_elem_ids_ok(samples.size(), elem_ids))
      return false;

    for (const size_t &elem_id : elem_ids) {
      if (*samples[ elem_id ].annotation >= n_classes)
        return false;
    }

    return true;
  }

  /**
   * \brief Tests whether the class annotations of the given samples are in the appropriate range.
   */
  template <typename A>
  static bool check_sample_classes_ok(const A *sample_annotations,
                                      const size_t &n_samples,
                                      const size_t &n_classes,
                                      const size_t &annotation_step=1) {
    for (size_t i = 0; i < n_samples; ++i) {
      if (static_cast<size_t>(sample_annotations[i*annotation_step]) >= n_classes ||
          abs(floor(sample_annotations[i*annotation_step])) != sample_annotations[i*annotation_step])
        return false;
    }

    return true;
  }

};  // namespace fertilized
#endif  // FERTILIZED_UTIL_CHECKS_H_