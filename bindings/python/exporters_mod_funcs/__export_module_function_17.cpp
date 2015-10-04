
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "./export_module_functions.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)

#include "../global.h"
#include <../include/fertilized/feature_extraction/feature_extraction.h>

namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  void __export_module_function_17() {
    py::def("extract_hough_forest_features", &fertilized::extract_hough_forest_features);
  };
}  // namespace pyfertilized