
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "./export_module_functions.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)

#include "../global.h"
#include <fertilized/standard_forests.h>

namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  void __export_module_function_8() {
    py::def("construct_fast_regression_forest_f",
            &fertilized::construct_fast_regression_forest<
              float
                         >);
  };
}  // namespace pyfertilized