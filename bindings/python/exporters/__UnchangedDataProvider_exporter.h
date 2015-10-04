
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___UNCHANGEDDATAPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___UNCHANGEDDATAPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/unchangeddataprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_UnchangedDataProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<UnchangedDataProvider<input_dtype,annotation_dtype>,
               std::shared_ptr<UnchangedDataProvider<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IDataProvider<input_dtype, annotation_dtype> >>
               (("UnchangedDataProvider" + type_short).c_str(),
                "Uses the provided data unchanged throughout the training.\n\
\n\
It builds its sample database from two pointer on memory arrays with\n\
data and annotations. Both must be provided in contiguous layout. The\n\
data (but not the annotations!) can be provided row- or column-wise.\n\
Column-wise layout is to be preferred, since it has more locality for\n\
most optimization processes.\n\
\n\
The annotations MUST always be provided in row major order, independent\n\
of the provided value for column_wise.\n\
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

    py::implicitly_convertible<std::shared_ptr<UnchangedDataProvider<input_dtype,annotation_dtype>>,
                               std::shared_ptr<IDataProvider<input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___UNCHANGEDDATAPROVIDER_EXPORTER_H_