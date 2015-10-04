// Author: ...
// Leave this as the first import to automatically prevent gcc to
// emit a warning about boost test on older gcc versions.
#include <fertilized/fertilized.h>

#include "boost/test/unit_test.hpp"
// If you need the `timeit` function to do time measurements.
#include "timeit.h"
// Provides convenience data-creators for tests.
#include "setup.h"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(YourTestSuiteName);

BOOST_AUTO_TEST_CASE(YourTest1) {
    BOOST_REQUIRE(true);
};

BOOST_AUTO_TEST_SUITE_END();
