
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ISURFACECALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ISURFACECALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/isurfacecalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_ISurfaceCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<ISurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>,
               boost::noncopyable>
               (("ISurfaceCalculator" + type_short).c_str(),
                "Calculates scalar values from a set of provided data dimensions.\n\
\n\
Must also propose parameter-sets for a random optimization of itself.\n\
\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
\n\
Instantiations:\n\
\n\
- int; int; uint\n\
- int; float; uint\n\
- uint8_t; uint8_t; uint\n\
- uint8_t; int16_t; uint\n\
- uint8_t; int16_t; int16_t\n\
- uint8_t; float; uint\n\
- float; float; uint\n\
- float; float; float\n\
- double; double; uint\n\
- double; float; uint\n\
- double; double; double\n\
- double; float; double\n\
\n\
\n\
-----\n\
",
                 py::no_init)
#ifdef SERIALIZATION_ENABLED
#endif
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___ISURFACECALCULATOR_EXPORTER_H_