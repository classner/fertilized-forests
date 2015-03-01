// Author: Christoph Lassner.
// Leave this as the first import to automatically prevent gcc to
// emit a warning about boost test on older gcc version.
#include <fertilized/fertilized.h>

#include "boost/test/unit_test.hpp"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_compute_feature_importances);

BOOST_AUTO_TEST_CASE(Correctness_Basic) {
  // feature 0 informative, feature 1 not.
  Array<double, 2, 2> X = allocate(10, 2);
  X.deep() = 0.;
  Array<double, 1, 1> range = allocate(10);
  for (int i = 0; i < 10; ++i) {
    range[i] = static_cast<double>(i);
  }
  X[view()(0)] = copy(range);
  Array<unsigned int, 2,2> Y = allocate(10, 1);
  Y[view()(0)] = copy(range);
  auto soil = Soil<double, double, double, Result_Types::probabilities>();
  auto tf = soil.StandardClassificationForest(10, 2);
  tf -> fit(X, Y);
  Array<double, 1, 1> importances = tf -> compute_feature_importances();
  BOOST_CHECK_EQUAL(importances[0], 1.);
  BOOST_CHECK_EQUAL(importances[1], 0.);
  // feature 1 informative, feature 0 not.
  X[view()(0)] = 0.;
  X[view()(1)] = copy(range);
  tf = soil.StandardClassificationForest(10, 2);
  tf -> fit(X, Y);
  importances = tf -> compute_feature_importances();
  BOOST_CHECK_EQUAL(importances[0], 0.);
  BOOST_CHECK_EQUAL(importances[1], 1.);
  // both equally.
  X[view()(0)] = copy(range);
  X[view()(1)] = copy(range);
  tf = soil.StandardClassificationForest(10, 2, 0, 0, 0, 200);
  Array<double, 2, 2> X2 = allocate(10, 2);
  Array<unsigned int, 2, 2> Y2 = allocate(10, 1);
  for (int i = 0; i < 10; ++i) {
    X2[i][0] = static_cast<double>(i);
    X2[i][1] = static_cast<double>(i);
    Y2[i][0] = static_cast<unsigned int>(i);
  }
  tf -> fit(X2, Y2);
  //importances = tf -> compute_feature_importances();
  //BOOST_CHECK(fabs(importances[0] - 0.5) < 0.01);
  //BOOST_CHECK(fabs(importances[1] - 0.5) < 0.01);
};

BOOST_AUTO_TEST_SUITE_END();
