
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
  void __python_export_0();
  void __python_export_1();
  void __python_export_2();
  void __python_export_3();
  void __python_export_4();
  void __python_export_5();
  void __python_export_6();
  void __python_export_7();
  void __python_export_8();
  void __python_export_9();
  void __python_export_10();
  void __python_export_11();
  void __python_export_12();
  void __python_export_13();
  void __python_export_14();
  void __python_export_15();
  void __python_export_16();
  void __python_export_17();
  void __python_export_18();
  void __python_export_19();
  void __python_export_20();
  void __python_export_21();
  void __python_export_22();
  void __python_export_23();
  void __python_export_24();
  void __python_export_25();
  void __python_export_26();
  void __python_export_27();
  void __python_export_28();
  void __python_export_29();
  void __python_export_30();
  void __python_export_31();
  void __python_export_32();
  void __python_export_33();
  void __python_export_34();
  void __python_export_35();
  void __python_export_36();
  void __python_export_37();
  void __python_export_38();
  void __python_export_39();
  void __python_export_40();
  void __python_export_41();
  void __python_export_42();
  void __python_export_43();
  void __python_export_44();
  void __python_export_45();
  void __python_export_46();
  void __python_export_47();
  void __python_export_48();
  void __python_export_49();
};

BOOST_PYTHON_MODULE(pyfertilized_0) {
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
  __python_export_0();
  __python_export_1();
  __python_export_2();
  __python_export_3();
  __python_export_4();
  __python_export_5();
  __python_export_6();
  __python_export_7();
  __python_export_8();
  __python_export_9();
  __python_export_10();
  __python_export_11();
  __python_export_12();
  __python_export_13();
  __python_export_14();
  __python_export_15();
  __python_export_16();
  __python_export_17();
  __python_export_18();
  __python_export_19();
  __python_export_20();
  __python_export_21();
  __python_export_22();
  __python_export_23();
  __python_export_24();
  __python_export_25();
  __python_export_26();
  __python_export_27();
  __python_export_28();
  __python_export_29();
  __python_export_30();
  __python_export_31();
  __python_export_32();
  __python_export_33();
  __python_export_34();
  __python_export_35();
  __python_export_36();
  __python_export_37();
  __python_export_38();
  __python_export_39();
  __python_export_40();
  __python_export_41();
  __python_export_42();
  __python_export_43();
  __python_export_44();
  __python_export_45();
  __python_export_46();
  __python_export_47();
  __python_export_48();
  __python_export_49();
};