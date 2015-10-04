
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___UNCHANGEDFDATAPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___UNCHANGEDFDATAPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/unchangedfdataprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_UnchangedFDataProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<UnchangedFDataProvider<input_dtype,annotation_dtype>,
               std::shared_ptr<UnchangedFDataProvider<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IForestDataProvider<input_dtype, annotation_dtype> >>
               (("UnchangedFDataProvider" + type_short).c_str(),
                "Uses unchanged data providers for each tree.\n\
\n\
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
                 py::init<

        const fertilized::Array<const input_dtype, 2, 2> &,
        const fertilized::Array<const annotation_dtype, 2, 2> &
                         >())
#ifdef SERIALIZATION_ENABLED
#endif
    ;

    py::implicitly_convertible<std::shared_ptr<UnchangedFDataProvider<input_dtype,annotation_dtype>>,
                               std::shared_ptr<IForestDataProvider<input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___UNCHANGEDFDATAPROVIDER_EXPORTER_H_