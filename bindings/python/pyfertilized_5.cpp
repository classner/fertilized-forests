
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
  void __python_export_250();
  void __python_export_251();
  void __python_export_252();
  void __python_export_253();
  void __python_export_254();
  void __python_export_255();
  void __python_export_256();
  void __python_export_257();
  void __python_export_258();
  void __python_export_259();
  void __python_export_260();
  void __python_export_261();
  void __python_export_262();
  void __python_export_263();
  void __python_export_264();
  void __python_export_265();
  void __python_export_266();
  void __python_export_267();
  void __python_export_268();
  void __python_export_269();
  void __python_export_270();
  void __python_export_271();
  void __python_export_272();
  void __python_export_273();
  void __python_export_274();
  void __python_export_275();
  void __python_export_276();
  void __python_export_277();
  void __python_export_278();
  void __python_export_279();
  void __python_export_280();
  void __python_export_281();
  void __python_export_282();
  void __python_export_283();
  void __python_export_284();
  void __python_export_285();
  void __python_export_286();
  void __python_export_287();
  void __python_export_288();
  void __python_export_289();
  void __python_export_290();
  void __python_export_291();
  void __python_export_292();
  void __python_export_293();
  void __python_export_294();
  void __python_export_295();
  void __python_export_296();
  void __python_export_297();
  void __python_export_298();
  void __python_export_299();
};

BOOST_PYTHON_MODULE(pyfertilized_5) {
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
  __python_export_250();
  __python_export_251();
  __python_export_252();
  __python_export_253();
  __python_export_254();
  __python_export_255();
  __python_export_256();
  __python_export_257();
  __python_export_258();
  __python_export_259();
  __python_export_260();
  __python_export_261();
  __python_export_262();
  __python_export_263();
  __python_export_264();
  __python_export_265();
  __python_export_266();
  __python_export_267();
  __python_export_268();
  __python_export_269();
  __python_export_270();
  __python_export_271();
  __python_export_272();
  __python_export_273();
  __python_export_274();
  __python_export_275();
  __python_export_276();
  __python_export_277();
  __python_export_278();
  __python_export_279();
  __python_export_280();
  __python_export_281();
  __python_export_282();
  __python_export_283();
  __python_export_284();
  __python_export_285();
  __python_export_286();
  __python_export_287();
  __python_export_288();
  __python_export_289();
  __python_export_290();
  __python_export_291();
  __python_export_292();
  __python_export_293();
  __python_export_294();
  __python_export_295();
  __python_export_296();
  __python_export_297();
  __python_export_298();
  __python_export_299();
};