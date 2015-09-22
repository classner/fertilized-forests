
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
  void __export_module_function_7() {
    py::def("construct_classifier_tree_uint8",
            &fertilized::construct_classifier_tree<
              uint8_t
                         >);
  };
}  // namespace pyfertilized