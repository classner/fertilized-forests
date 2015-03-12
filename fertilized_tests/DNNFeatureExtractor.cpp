// Author: Christoph Lassner.
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
#include <fertilized/fertilized.h>

#include <vector>

#include "boost/test/unit_test.hpp"
// If you need the `timeit` function to do time measurements.
#include "timeit.h"
// Provides convenience data-creators for tests.
#include "setup.h"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_DNNFeatureExtractor);

BOOST_AUTO_TEST_CASE(Correctness_Constructor) {
  auto soil = Soil<>();
  auto feature_extractor = soil.DNNFeatureExtractor(true); // Use CPU!
  // Create a dummy 'image'.
  Array<float, 3, 3> testimage = allocate(300, 300, 3);
  std::vector<Array<float, 3, 3>> images;
  images.push_back(testimage);
  auto extraction_result = feature_extractor -> extract(images);
  std::cout << extraction_result[0][100][3][3] << std::endl;
};

#ifndef CAFFE_CPU_ONLY
BOOST_AUTO_TEST_CASE(Correctness_CPU_eq_GPU) {
  auto soil = Soil<>();
  auto feature_extractor_cpu = soil.DNNFeatureExtractor(true);
  auto feature_extractor_gpu = soil.DNNFeatureExtractor();
  Array<float, 3, 3> testimage = allocate(300, 300, 3);
  testimage.deep() = 200.f;
  std::vector<Array<float, 3, 3>> images;
  images.push_back(testimage);
  auto extraction_result_cpu = feature_extractor_cpu -> extract(images);
  auto extraction_result_gpu = feature_extractor_gpu -> extract(images);
  BOOST_CHECK(all(equal(extraction_result_cpu, extraction_result_gpu)));
};
#endif

BOOST_AUTO_TEST_SUITE_END();
#endif // CAFFE_FEATURE_EXTRACTION_ENABLED
