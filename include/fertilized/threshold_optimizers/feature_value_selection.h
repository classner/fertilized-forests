/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_THRESHOLD_OPTIMIZERS_FEATUREVALUESELECTION_H_
#define FERTILIZED_THRESHOLD_OPTIMIZERS_FEATUREVALUESELECTION_H_

#include <type_traits>
#include <random>
#include <set>

#include "../global.h"
#include "../types.h"
#include "../util/sampling.h"

namespace fertilized {
  /**
   * Randomly draws n feature values between min and max (including).
   *
   * Overload for integer datatypes.
   */
  template <typename T>
  void draw_feat_vals(const T &min, const T &max, const size_t &n,
    std::mt19937 *random_engine, std::set<T> *selected_feat_vals,
    std::true_type) {
    if (n <= max - min + 1) {
      // Draw unique indices to always get the expected number of thresholds
      // to test.
      auto unique_drawn = unique_indices<T>(static_cast<T>(n), min, max, random_engine, true);
      selected_feat_vals -> insert(unique_drawn.begin(), unique_drawn.end());
    } else {
      for (size_t i = 0; min + i < max; ++i)
        selected_feat_vals -> emplace(min + static_cast<T>(i));
    }
  }

  /**
   * Randomly draws n feature values between min and max (including).
   *
   * Overload for floating point datatypes.
   */
  template <typename T>
  void draw_feat_vals(const T &min, const T &max, const size_t &n,
    std::mt19937 *random_engine, std::set<T> *selected_feat_vals,
    std::false_type) {
    auto dist = std::uniform_real_distribution<T>(min, max);
    for (size_t i = 0; i < n; ++i)
      selected_feat_vals -> emplace(dist(*random_engine));
  }
}  // namespace fertilized
#endif  // FERTILIZED_THRESHOLD_OPTIMIZERS_FEATUREVALUESELECTION_H_
