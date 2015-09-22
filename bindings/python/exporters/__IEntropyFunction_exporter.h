
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IENTROPYFUNCTION_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IENTROPYFUNCTION_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/ientropyfunction.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype>
  void export_IEntropyFunction(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IEntropyFunction<input_dtype>,
               boost::noncopyable>
               (("IEntropyFunction" + type_short).c_str(),
                "Interface for an entropy calculation functor.\n\
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

#endif  // PYFERTILIZED_EXPORTERS___IENTROPYFUNCTION_EXPORTER_H_