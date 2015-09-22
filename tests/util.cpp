/* Author: Christoph Lassner. */
#include <fertilized/global.h>
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <functional>
#include <string>
#include <vector>
#include <type_traits>
#include <random>

#include <fertilized/util/sampling.h>

#include "./setup.h"
#include "./timeit.h"

// Required objects.

// Test objects.
using fertilized::unique_indices;


BOOST_AUTO_TEST_SUITE(Correctness_ThresholdOptimizers);

//---------------------------------------------------------------------------//
// Unique index generation.
BOOST_AUTO_TEST_CASE(Correctness_UniqueIndicesComplete) {
  auto re = std::make_shared<std::mt19937>(1);
  auto resved = unique_indices(11, 10, 20, re.get());
  for (size_t i = 10; i < 21; ++i) {
    BOOST_CHECK(std::find(resved.begin(), resved.end(), i) != resved.end());
  }
};

BOOST_AUTO_TEST_CASE(Correctness_UniqueIndicesDiffMean) {
  auto re = std::make_shared<std::mt19937>(1);

  for (int i = 0; i < 10; ++i) {
    auto resved = unique_indices<int>(1000, 0, 9999, re.get(), true);
    float mean = 0.f;
    float n_vals = 0.f;
    for (size_t i = 0; i < resved.size() - 1; ++i) {
      int val = resved[i];
      int nval = resved[i+1];
      BOOST_CHECK(val >= 0 && val <= 9999);
      if (n_vals > 0.f) {
        mean += 1.f / (n_vals + 1.f) * (static_cast<float>(nval - val) - mean);
      } else {
        mean = static_cast<float>(nval - val);
      }
      n_vals++;
    }
    BOOST_CHECK_SMALL(static_cast<float>(abs(mean + 10.f)), .7f);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_UniqueIndicesSortedUnsortedEqual) {
  for (int i = 0; i < 10; ++i) {
    auto re = std::make_shared<std::mt19937>(i+1);
    auto resved_sorted = unique_indices<int>(1000, 0, 9999, re.get(), true);
    re = std::make_shared<std::mt19937>(i+1);
    auto resved_shuffled = unique_indices<int>(1000, 0, 9999, re.get(), false);

    std::sort(resved_shuffled.begin(), resved_shuffled.end());
    std::sort(resved_sorted.begin(), resved_sorted.end());
    BOOST_CHECK(resved_shuffled == resved_sorted);
  }
};

BOOST_AUTO_TEST_SUITE_END();