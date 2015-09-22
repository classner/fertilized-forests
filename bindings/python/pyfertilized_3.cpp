
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
  void __python_export_150();
  void __python_export_151();
  void __python_export_152();
  void __python_export_153();
  void __python_export_154();
  void __python_export_155();
  void __python_export_156();
  void __python_export_157();
  void __python_export_158();
  void __python_export_159();
  void __python_export_160();
  void __python_export_161();
  void __python_export_162();
  void __python_export_163();
  void __python_export_164();
  void __python_export_165();
  void __python_export_166();
  void __python_export_167();
  void __python_export_168();
  void __python_export_169();
  void __python_export_170();
  void __python_export_171();
  void __python_export_172();
  void __python_export_173();
  void __python_export_174();
  void __python_export_175();
  void __python_export_176();
  void __python_export_177();
  void __python_export_178();
  void __python_export_179();
  void __python_export_180();
  void __python_export_181();
  void __python_export_182();
  void __python_export_183();
  void __python_export_184();
  void __python_export_185();
  void __python_export_186();
  void __python_export_187();
  void __python_export_188();
  void __python_export_189();
  void __python_export_190();
  void __python_export_191();
  void __python_export_192();
  void __python_export_193();
  void __python_export_194();
  void __python_export_195();
  void __python_export_196();
  void __python_export_197();
  void __python_export_198();
  void __python_export_199();
};

BOOST_PYTHON_MODULE(pyfertilized_3) {
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
  __python_export_150();
  __python_export_151();
  __python_export_152();
  __python_export_153();
  __python_export_154();
  __python_export_155();
  __python_export_156();
  __python_export_157();
  __python_export_158();
  __python_export_159();
  __python_export_160();
  __python_export_161();
  __python_export_162();
  __python_export_163();
  __python_export_164();
  __python_export_165();
  __python_export_166();
  __python_export_167();
  __python_export_168();
  __python_export_169();
  __python_export_170();
  __python_export_171();
  __python_export_172();
  __python_export_173();
  __python_export_174();
  __python_export_175();
  __python_export_176();
  __python_export_177();
  __python_export_178();
  __python_export_179();
  __python_export_180();
  __python_export_181();
  __python_export_182();
  __python_export_183();
  __python_export_184();
  __python_export_185();
  __python_export_186();
  __python_export_187();
  __python_export_188();
  __python_export_189();
  __python_export_190();
  __python_export_191();
  __python_export_192();
  __python_export_193();
  __python_export_194();
  __python_export_195();
  __python_export_196();
  __python_export_197();
  __python_export_198();
  __python_export_199();
};