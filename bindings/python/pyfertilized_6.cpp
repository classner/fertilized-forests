
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#include "./global.h"

// The INTEL compiler does not have a working solution
// to temporarily disable specific warnings in the code.
// (e.g. see http://software.intel.com/en-us/forums/topic/283633).
// This is why for that compiler this is done using command
// line options (disable #2415 and #2586).
#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)

#include <vector>
#include <memory>
#include <cstddef>

#include "./exporters_vec_types/vec_exporter.h"

namespace np = boost::numpy;

using namespace pyfertilized;

namespace pyfertilized {
  // Forward declarations.
  void __python_export_300();
  void __python_export_301();
  void __python_export_302();
  void __python_export_303();
  void __python_export_304();
  void __python_export_305();
  void __python_export_306();
  void __python_export_307();
  void __python_export_308();
  void __python_export_309();
  void __python_export_310();
  void __python_export_311();
  void __python_export_312();
  void __python_export_313();
  void __python_export_314();
};

BOOST_PYTHON_MODULE(pyfertilized_6) {
  // Allow releasing the GIL.
  PyEval_InitThreads();
  // Boost numpy needs an initialization method call *critical*.
  np::initialize();
  // Set the documentation to python call signatures and user defined
  // documentation strings.
  // The C++ doc is rather cluttered and not very informative.
  py::docstring_options doc_options;
  doc_options.enable_user_defined();
  doc_options.enable_py_signatures();
  doc_options.disable_cpp_signatures();

  py::scope().attr("__doc__") = "Fertilized Python Interface\n";

  // Export classes.
  __python_export_300();
  __python_export_301();
  __python_export_302();
  __python_export_303();
  __python_export_304();
  __python_export_305();
  __python_export_306();
  __python_export_307();
  __python_export_308();
  __python_export_309();
  __python_export_310();
  __python_export_311();
  __python_export_312();
  __python_export_313();
  __python_export_314();
};