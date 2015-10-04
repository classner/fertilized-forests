
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ISAMPLEMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ISAMPLEMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/isamplemanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_ISampleManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<ISampleManager<input_dtype,annotation_dtype>,
               boost::noncopyable>
               (("ISampleManager" + type_short).c_str(),
                "Interface for a sample manager that loads samples when required\n\
and frees memory on demand.\n\
\n\
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
- uint8_t; int16_t\n\
- uint8_t; uint\n\
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

#endif  // PYFERTILIZED_EXPORTERS___ISAMPLEMANAGER_EXPORTER_H_