// Author: Christoph Lassner.
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
#include <fertilized/fertilized.h>

#include "boost/test/unit_test.hpp"
// If you need the `timeit` function to do time measurements.
#include "timeit.h"
// Provides convenience data-creators for tests.
#include "setup.h"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_DNNFeatureExtractor);

BOOST_AUTO_TEST_CASE(Correctness_Constructor) {
  auto soil = Soil<>();
  auto feat_extractor = soil.DNNFeatureExtractor();
};

BOOST_AUTO_TEST_SUITE_END();
#endif // CAFFE_FEATURE_EXTRACTION_ENABLED