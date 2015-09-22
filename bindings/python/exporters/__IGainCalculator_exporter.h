
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IGAINCALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IGAINCALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/gains/igaincalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename counting_dtype>
  void export_IGainCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IGainCalculator<counting_dtype>,
               boost::noncopyable>
               (("IGainCalculator" + type_short).c_str(),
                "Interface for a gain calculator class.\n\
\n\
A gain calculator must have an overloaded () operator with the\n\
according parameters and an approx function that returns a fast\n\
approximation of the gain (can return the original gain if no\n\
approximation is available). The approximation is used to find the\n\
best split position and only for that the actual gain is computed.\n\
\n\
Parameters\n\
==========\n\
\n\
counting_dtype : The datatype for counting class members. This might\n\
  be a float if sample weights are used.\n\
\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
Instantiations:\n\
\n\
- float\n\
- uint\n\
\n\
Soil type always:\n\
\n\
- float\n\
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

#endif  // PYFERTILIZED_EXPORTERS___IGAINCALCULATOR_EXPORTER_H_