
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IDECIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IDECIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/deciders/idecider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_IDecider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IDecider<input_dtype,feature_dtype,annotation_dtype>,
               boost::noncopyable>
               (("IDecider" + type_short).c_str(),
                "Interface for the decider. It does the\n\
optimization of the deciding classifier for each node and stores the\n\
parameters.\n\
\n\
Parameters\n\
==========\n\
\n\
input_dtype : The datatype of the data to classify.\n\
\n\
annotation_dtype : The datatype of the annotations.\n\
\n\
feature_dtype : The datatype in which features are calculated.\n\
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
- uint8_t; uint8_t; uint\n\
- uint8_t; int16_t; uint\n\
- float; float; uint\n\
- double; double; uint\n\
- uint8_t; int16_t; int16_t\n\
- float; float; float\n\
- double; double; double\n\
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

#endif  // PYFERTILIZED_EXPORTERS___IDECIDER_EXPORTER_H_