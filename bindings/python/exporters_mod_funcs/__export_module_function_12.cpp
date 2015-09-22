
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "./export_module_functions.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)

#include "../global.h"
#include <fertilized/standard_trees.h>

namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  void __export_module_function_12() {
    py::def("construct_hough_tree_uint8_int16_int16",
            &fertilized::construct_hough_tree<
              uint8_t,
              int16_t,
              int16_t
                         >);
  };
}  // namespace pyfertilized