// Author: Christoph Lassner.
#include <fertilized/global.h>

#include <random>
#include "boost/test/unit_test.hpp"
#include "timeit.h"
//
#include <fertilized/fertilized.h>

#include "setup.h"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_Forests);

BOOST_AUTO_TEST_CASE(Correctness_Forests_threaded_prediction) {
  std::mt19937 rng;
  rng.seed(1);
  auto dist_float = std::normal_distribution<float>(0., 1.);
  auto dist_uint = std::uniform_int_distribution<uint>(0, 1);
  auto s = Soil<>();
  auto tf = s.StandardClassificationForest(2, 3);
  Array<float, 2, 2> data = allocate(100, 3);
  auto dptr = &data[0][0];
  for (size_t i = 0; i < 300; ++i) {
      *(dptr++) = dist_float(rng);
  }
  Array<uint, 2, 2> annotation = allocate(100, 1);
  auto aptr = &annotation[0][0];
  for (size_t i = 0; i < 100; ++i) {
      *(aptr++) = dist_uint(rng);
  }
  tf -> fit(data, annotation);
  // Get results serially.
  auto res_serial = tf -> predict(data);
  // Get results in parallel.
  auto res_parallel = tf -> predict(data, 1);
  BOOST_CHECK(all(equal(res_serial, res_parallel)));
  //auto timestruct = PredictTimer<Forest<float, float, uint, std::vector<float>, std::vector<float>>, Array<float, 2, 2>>(tf.get(), &data);
  //float time = Utility::timeit<std::chrono::nanoseconds>(&timestruct, false, 3, 2);
  //std::cout << time;
};

BOOST_AUTO_TEST_CASE(Correctness_Forest_depths) {
  auto s = Soil<>();
  auto forest = s.StandardClassificationForest(2, 1);
  auto depths = forest -> depths();
  for (int i = 0; i < 10; ++i) {
    BOOST_CHECK_EQUAL(depths[i], 0);
  }
  auto t1 = s.StandardClassificationTree(2, 1);
  auto t2 = s.StandardClassificationTree(2, 1);
  Array<float, 2, 2> data = allocate(2, 1);
  data[0][0] = 0.f;
  data[1][0] = 1.f;
  Array<unsigned int, 2, 2> annotations = allocate(2, 1);
  annotations[0][0] = 0;
  annotations[1][0] = 1;
  t1 -> fit(data, annotations);
  data = allocate(4, 1);
  data[0][0] = 0.f;
  data[1][0] = 1.f;
  data[2][0] = 2.f;
  data[3][0] = 3.f;
  annotations = allocate(4, 1);
  annotations[0][0] = 0;
  annotations[1][0] = 1;
  annotations[2][0] = 0;
  annotations[3][0] = 1;
  t2 = s.StandardClassificationTree(2, 1);
  t2 -> fit(data, annotations);
  decltype(s.tree_vec_t()) trees;
  trees.push_back(t1);
  trees.push_back(t2);
  forest = s.CombineTrees(trees);
  depths = forest -> depths();
  BOOST_CHECK_EQUAL(depths[0], 1);
  BOOST_CHECK_EQUAL(depths[1], 3);
}

BOOST_AUTO_TEST_SUITE_END();
