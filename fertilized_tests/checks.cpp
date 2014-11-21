/* Author: Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

#include <chrono>
#include <functional>
#include <string>
#include <vector>

#include <fertilized/util/checks.h>
#include <fertilized/data_providers/sample.h>

#include "./setup.h"

// Required objects.
using fertilized::Sample;

// Test objects.
using fertilized::safe_pos_sum_lessoe_than;
using fertilized::check_elem_ids_ok;
using fertilized::check_sample_weights_ok;
using fertilized::check_sample_classes_ok;


BOOST_AUTO_TEST_SUITE(Correctness_Checks);
BOOST_AUTO_TEST_CASE(Correctness_PosSumType) {
  // Callable for right types.
  BOOST_CHECK(safe_pos_sum_lessoe_than(std::vector<float>(10, 1.f), 11.f));
  BOOST_CHECK(safe_pos_sum_lessoe_than(std::vector<int>(10, 1), 11));
  // Is uncallable for wrong types. Implicitly compile time check by use of
  // numeric_limits in the function.
};

BOOST_AUTO_TEST_CASE(Correctness_SafePosSumIsTrueForSmaller) {
  for (int i = 0; i < 100; ++i) {
    BOOST_CHECK(safe_pos_sum_lessoe_than(std::vector<int>(1, i), 100));
    BOOST_CHECK(safe_pos_sum_lessoe_than(
      std::vector<float>(1, static_cast<float>(i)), 100.f));
  }
};

BOOST_AUTO_TEST_CASE(Correctness_SafePosSumIsFalseForLarger) {
  for (int i = 11; i < 100; ++i) {
    BOOST_CHECK(!safe_pos_sum_lessoe_than(std::vector<int>(1, i), 10));
    BOOST_CHECK(!safe_pos_sum_lessoe_than(
      std::vector<float>(1, static_cast<float>(i)), 10.f));
  }
};

BOOST_AUTO_TEST_CASE(Correctness_SafePosSumIsFalseForNeg) {
  for (int i = -1; i > -100; --i) {
    BOOST_CHECK(!safe_pos_sum_lessoe_than(std::vector<int>(1, i), 10));
    BOOST_CHECK(!safe_pos_sum_lessoe_than(
      std::vector<float>(1, static_cast<float>(i)), 10.f));
  }
};

BOOST_AUTO_TEST_CASE(Correctness_SafePosSumIsFalseForLimits) {
  BOOST_CHECK(!safe_pos_sum_lessoe_than(
    std::vector<int>(2, std::numeric_limits<int>::max())));
  BOOST_CHECK(!safe_pos_sum_lessoe_than(
    std::vector<float>(2, std::numeric_limits<float>::max())));
};

BOOST_AUTO_TEST_CASE(Correctness_ElemIdsOk) {
  std::vector<size_t> elem_ids(2);

  for (size_t i = 0; i < 100; ++i) {
    elem_ids.push_back(i);
    BOOST_CHECK(check_elem_ids_ok(i + 1, elem_ids));
    BOOST_CHECK(!check_elem_ids_ok(i, elem_ids));
  }
}

BOOST_AUTO_TEST_CASE(Correctness_ElemIdsOkForEmpty) {
  std::vector<size_t> elem_ids(0);
  for (size_t i = 0; i < 100; ++i) {
    BOOST_CHECK(check_elem_ids_ok(i, elem_ids));
  }
}

BOOST_AUTO_TEST_CASE(Correctness_SampleWeightsOk_FalseForNegative) {
  auto svec = std::vector<Sample<int, int>>();
  auto elem_id_vec = std::vector<size_t>();

  svec.push_back(Sample<int, int>(nullptr, 0, nullptr, -5.f));
  elem_id_vec.push_back(0);
  BOOST_CHECK(!check_sample_weights_ok(svec, elem_id_vec));
}

BOOST_AUTO_TEST_CASE(Correctness_SampleWeightsOk_FalseForTooLarge) {
  auto svec = std::vector<Sample<int, int>>();
  auto elem_id_vec = std::vector<size_t>();

  svec.push_back(Sample<int, int>(nullptr, 0, nullptr,
    std::numeric_limits<float>::max()));
  svec.push_back(Sample<int, int>(nullptr, 0, nullptr,
    std::numeric_limits<float>::max()));
  elem_id_vec.push_back(0);
  elem_id_vec.push_back(1);
  BOOST_CHECK(!check_sample_weights_ok(svec, elem_id_vec));
}

BOOST_AUTO_TEST_CASE(Correctness_SampleWeightsOk_TrueForOk) {
  auto svec = std::vector<Sample<int, int>>();
  auto elem_id_vec = std::vector<size_t>();

  svec.push_back(Sample<int, int>(nullptr, 0, nullptr, 5.f));
  svec.push_back(Sample<int, int>(nullptr, 0, nullptr, 10.f));
  elem_id_vec.push_back(0);
  elem_id_vec.push_back(1);
  BOOST_CHECK(check_sample_weights_ok(svec, elem_id_vec));
}

BOOST_AUTO_TEST_CASE(Correctness_SampleClassesOk) {
  auto svec = std::vector<Sample<int, unsigned int>>();
  auto elem_id_vec = std::vector<size_t>();

  std::vector<unsigned int> classes(2);
  std::iota(classes.begin(), classes.end(), 0);

  svec.push_back(Sample<int, unsigned int>(nullptr, 0, &classes[0],
    std::numeric_limits<float>::max()));
  svec.push_back(Sample<int, unsigned int>(nullptr, 0, &classes[1],
    std::numeric_limits<float>::max()));
  elem_id_vec.push_back(0);
  elem_id_vec.push_back(1);
  BOOST_CHECK(!check_sample_classes_ok(svec, elem_id_vec, 1));
  BOOST_CHECK(check_sample_classes_ok(svec, elem_id_vec, 2));
  BOOST_CHECK(check_sample_classes_ok(svec, elem_id_vec, 3));
  BOOST_CHECK(check_sample_classes_ok(svec, elem_id_vec, 4));
}

BOOST_AUTO_TEST_CASE(Correctness_SampleClassesOkForEmpty) {
  auto svec = std::vector<Sample<int, unsigned int>>();
  auto elem_id_vec = std::vector<size_t>();

  BOOST_CHECK(check_sample_classes_ok(svec, elem_id_vec, 2));
}

BOOST_AUTO_TEST_SUITE_END();