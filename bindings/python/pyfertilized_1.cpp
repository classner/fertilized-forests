
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
  void __python_export_50();
  void __python_export_51();
  void __python_export_52();
  void __python_export_53();
  void __python_export_54();
  void __python_export_55();
  void __python_export_56();
  void __python_export_57();
  void __python_export_58();
  void __python_export_59();
  void __python_export_60();
  void __python_export_61();
  void __python_export_62();
  void __python_export_63();
  void __python_export_64();
  void __python_export_65();
  void __python_export_66();
  void __python_export_67();
  void __python_export_68();
  void __python_export_69();
  void __python_export_70();
  void __python_export_71();
  void __python_export_72();
  void __python_export_73();
  void __python_export_74();
  void __python_export_75();
  void __python_export_76();
  void __python_export_77();
  void __python_export_78();
  void __python_export_79();
  void __python_export_80();
  void __python_export_81();
  void __python_export_82();
  void __python_export_83();
  void __python_export_84();
  void __python_export_85();
  void __python_export_86();
  void __python_export_87();
  void __python_export_88();
  void __python_export_89();
  void __python_export_90();
  void __python_export_91();
  void __python_export_92();
  void __python_export_93();
  void __python_export_94();
  void __python_export_95();
  void __python_export_96();
  void __python_export_97();
  void __python_export_98();
  void __python_export_99();
};

BOOST_PYTHON_MODULE(pyfertilized_1) {
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
  __python_export_50();
  __python_export_51();
  __python_export_52();
  __python_export_53();
  __python_export_54();
  __python_export_55();
  __python_export_56();
  __python_export_57();
  __python_export_58();
  __python_export_59();
  __python_export_60();
  __python_export_61();
  __python_export_62();
  __python_export_63();
  __python_export_64();
  __python_export_65();
  __python_export_66();
  __python_export_67();
  __python_export_68();
  __python_export_69();
  __python_export_70();
  __python_export_71();
  __python_export_72();
  __python_export_73();
  __python_export_74();
  __python_export_75();
  __python_export_76();
  __python_export_77();
  __python_export_78();
  __python_export_79();
  __python_export_80();
  __python_export_81();
  __python_export_82();
  __python_export_83();
  __python_export_84();
  __python_export_85();
  __python_export_86();
  __python_export_87();
  __python_export_88();
  __python_export_89();
  __python_export_90();
  __python_export_91();
  __python_export_92();
  __python_export_93();
  __python_export_94();
  __python_export_95();
  __python_export_96();
  __python_export_97();
  __python_export_98();
  __python_export_99();
};