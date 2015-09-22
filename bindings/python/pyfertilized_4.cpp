
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
  void __python_export_200();
  void __python_export_201();
  void __python_export_202();
  void __python_export_203();
  void __python_export_204();
  void __python_export_205();
  void __python_export_206();
  void __python_export_207();
  void __python_export_208();
  void __python_export_209();
  void __python_export_210();
  void __python_export_211();
  void __python_export_212();
  void __python_export_213();
  void __python_export_214();
  void __python_export_215();
  void __python_export_216();
  void __python_export_217();
  void __python_export_218();
  void __python_export_219();
  void __python_export_220();
  void __python_export_221();
  void __python_export_222();
  void __python_export_223();
  void __python_export_224();
  void __python_export_225();
  void __python_export_226();
  void __python_export_227();
  void __python_export_228();
  void __python_export_229();
  void __python_export_230();
  void __python_export_231();
  void __python_export_232();
  void __python_export_233();
  void __python_export_234();
  void __python_export_235();
  void __python_export_236();
  void __python_export_237();
  void __python_export_238();
  void __python_export_239();
  void __python_export_240();
  void __python_export_241();
  void __python_export_242();
  void __python_export_243();
  void __python_export_244();
  void __python_export_245();
  void __python_export_246();
  void __python_export_247();
  void __python_export_248();
  void __python_export_249();
};

BOOST_PYTHON_MODULE(pyfertilized_4) {
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
  __python_export_200();
  __python_export_201();
  __python_export_202();
  __python_export_203();
  __python_export_204();
  __python_export_205();
  __python_export_206();
  __python_export_207();
  __python_export_208();
  __python_export_209();
  __python_export_210();
  __python_export_211();
  __python_export_212();
  __python_export_213();
  __python_export_214();
  __python_export_215();
  __python_export_216();
  __python_export_217();
  __python_export_218();
  __python_export_219();
  __python_export_220();
  __python_export_221();
  __python_export_222();
  __python_export_223();
  __python_export_224();
  __python_export_225();
  __python_export_226();
  __python_export_227();
  __python_export_228();
  __python_export_229();
  __python_export_230();
  __python_export_231();
  __python_export_232();
  __python_export_233();
  __python_export_234();
  __python_export_235();
  __python_export_236();
  __python_export_237();
  __python_export_238();
  __python_export_239();
  __python_export_240();
  __python_export_241();
  __python_export_242();
  __python_export_243();
  __python_export_244();
  __python_export_245();
  __python_export_246();
  __python_export_247();
  __python_export_248();
  __python_export_249();
};