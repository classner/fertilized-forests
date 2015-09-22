
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
  void __export_module_function_13() {
    py::def("construct_regression_forest_f",
            &fertilized::construct_regression_forest<
              float
                         >);
  };
}  // namespace pyfertilized