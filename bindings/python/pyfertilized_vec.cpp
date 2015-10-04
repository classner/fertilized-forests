
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

BOOST_PYTHON_MODULE(pyfertilized_vec) {
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

  py::scope().attr("__doc__") = "Fertilized Python Vectors\n";

  // Vectors of C++ types.
  __export_vectors_0();
  __export_vectors_1();
  __export_vectors_2();
  __export_vectors_3();
  __export_vectors_4();
  __export_vectors_5();
  __export_vectors_6();
  __export_vectors_7();
  __export_vectors_8();
  __export_vectors_9();
  __export_vectors_10();
  __export_vectors_11();
  __export_vectors_12();
  __export_vectors_13();
  __export_vectors_14();
  __export_vectors_15();
  __export_vectors_16();
  __export_vectors_17();
  __export_vectors_18();
  __export_vectors_19();
  __export_vectors_20();
  __export_vectors_21();
  __export_vectors_22();
  __export_vectors_23();
  __export_vectors_24();
  __export_vectors_25();
  __export_vectors_26();
};