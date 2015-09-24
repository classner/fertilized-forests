// Author: Christoph Lassner.
#include <fertilized/global.h>

#include <random>
#include "boost/test/unit_test.hpp"
#include "timeit.h"
#include "setup.h"

#include <fertilized/fertilized.h>

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_Trees);

BOOST_AUTO_TEST_CASE(Correctness_Trees_Basic) {
  auto s = Soil<>();
  auto tf = s.StandardClassificationForest(2, 3);
  Array<float, 2, 2> data = allocate(10, 3);
  data.deep() = 1.f;
  Array<uint, 2, 2> annotation = allocate(10, 1);
  annotation.deep() = 1;
  annotation[view(0,5)] = 0;
  tf -> fit(data, annotation);
#ifdef SERIALIZATION_ENABLED
  tf -> save("tmp.txt");
  auto rtf = s.ForestFromFile("tmp.txt");
  BOOST_REQUIRE(*(tf.get()) == *(rtf.get()));
  auto tt = s.StandardClassificationTree(2, 10, 5, 2, 2);
  tt -> save("tmp.txt");
  auto rtt = s.TreeFromFile("tmp.txt");
  BOOST_REQUIRE(*(tt.get()) == *(rtt.get()));
#endif
};

#ifdef _OPENMP
BOOST_AUTO_TEST_CASE(Correctness_Trees_threaded_prediction) {
  std::mt19937 rng;
  rng.seed(1);
  auto dist_float = std::normal_distribution<float>(0., 1.);
  auto dist_uint = std::uniform_int_distribution<uint>(0, 1);
  auto s = Soil<>();
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
  for (int rep = 0; rep < 100; ++rep) {
      auto tf = s.StandardClassificationTree(2, 3);
      tf -> fit(data, annotation);
      // Get results serially.
      auto res_serial = tf -> predict(data);
      // Get results in parallel.
      auto res_parallel = tf -> predict(data, 2);
      BOOST_CHECK(all(equal(res_serial, res_parallel)));
  }
};
#endif

BOOST_AUTO_TEST_CASE(Correctness_Tree_depth) {
  auto s = Soil<>();
  auto tree = s.StandardClassificationTree(2, 1);
  size_t depth = tree -> depth();
  BOOST_CHECK_EQUAL(depth, 0);
  Array<float, 2, 2> data = allocate(2, 1);
  data[0][0] = 0.f;
  data[1][0] = 1.f;
  Array<unsigned int, 2, 2> annotations = allocate(2, 1);
  annotations[0][0] = 0;
  annotations[1][0] = 1;
  tree -> fit(data, annotations);
  depth = tree -> depth();
  BOOST_CHECK_EQUAL(depth, 1);
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
  tree = s.StandardClassificationTree(2, 1);
  tree -> fit(data, annotations);
  depth = tree -> depth();
  BOOST_CHECK_EQUAL(depth, 3);
}

BOOST_AUTO_TEST_SUITE_END();
