
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
  void __python_export_100();
  void __python_export_101();
  void __python_export_102();
  void __python_export_103();
  void __python_export_104();
  void __python_export_105();
  void __python_export_106();
  void __python_export_107();
  void __python_export_108();
  void __python_export_109();
  void __python_export_110();
  void __python_export_111();
  void __python_export_112();
  void __python_export_113();
  void __python_export_114();
  void __python_export_115();
  void __python_export_116();
  void __python_export_117();
  void __python_export_118();
  void __python_export_119();
  void __python_export_120();
  void __python_export_121();
  void __python_export_122();
  void __python_export_123();
  void __python_export_124();
  void __python_export_125();
  void __python_export_126();
  void __python_export_127();
  void __python_export_128();
  void __python_export_129();
  void __python_export_130();
  void __python_export_131();
  void __python_export_132();
  void __python_export_133();
  void __python_export_134();
  void __python_export_135();
  void __python_export_136();
  void __python_export_137();
  void __python_export_138();
  void __python_export_139();
  void __python_export_140();
  void __python_export_141();
  void __python_export_142();
  void __python_export_143();
  void __python_export_144();
  void __python_export_145();
  void __python_export_146();
  void __python_export_147();
  void __python_export_148();
  void __python_export_149();
};

BOOST_PYTHON_MODULE(pyfertilized_2) {
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
  __python_export_100();
  __python_export_101();
  __python_export_102();
  __python_export_103();
  __python_export_104();
  __python_export_105();
  __python_export_106();
  __python_export_107();
  __python_export_108();
  __python_export_109();
  __python_export_110();
  __python_export_111();
  __python_export_112();
  __python_export_113();
  __python_export_114();
  __python_export_115();
  __python_export_116();
  __python_export_117();
  __python_export_118();
  __python_export_119();
  __python_export_120();
  __python_export_121();
  __python_export_122();
  __python_export_123();
  __python_export_124();
  __python_export_125();
  __python_export_126();
  __python_export_127();
  __python_export_128();
  __python_export_129();
  __python_export_130();
  __python_export_131();
  __python_export_132();
  __python_export_133();
  __python_export_134();
  __python_export_135();
  __python_export_136();
  __python_export_137();
  __python_export_138();
  __python_export_139();
  __python_export_140();
  __python_export_141();
  __python_export_142();
  __python_export_143();
  __python_export_144();
  __python_export_145();
  __python_export_146();
  __python_export_147();
  __python_export_148();
  __python_export_149();
};