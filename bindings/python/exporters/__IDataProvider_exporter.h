
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IDATAPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IDATAPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/idataprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_IDataProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IDataProvider<input_dtype,annotation_dtype>,
               boost::noncopyable>
               (("IDataProvider" + type_short).c_str(),
                "The data provider for the training of one tree.\n\
\n\
\n\
Data providers work with Samples and sample ids. They are allowed to\n\
add additional samples during training on the fly. The method\n\
optimize_set_for_node is called before a classifier is fitted for\n\
a decision node, so that the data provider can alter the set of samples\n\
that are used.\n\
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
- float; uint\n\
- int; uint\n\
- uint8_t; uint\n\
- uint8_t; int16_t\n\
- double; uint\n\
- double; double\n\
- float; float\n\
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

#endif  // PYFERTILIZED_EXPORTERS___IDATAPROVIDER_EXPORTER_H_