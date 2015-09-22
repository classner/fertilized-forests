
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___CLASSIFICATIONERROR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___CLASSIFICATIONERROR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/classificationerror.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype>
  void export_ClassificationError(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::ClassificationError<input_dtype>::*ptr_ClassificationError_0)
    (

        const fertilized::IEntropyFunction<input_dtype> &
) const =
      &fertilized::ClassificationError<input_dtype>::operator==;
    bool (*ptr_ClassificationError_1)
    (

        const fertilized::IEntropyFunction<input_dtype> &
,
     

        const fertilized::IEntropyFunction<input_dtype> &
) =
    &ne_from_eq<fertilized::IEntropyFunction<input_dtype>>;
    py::class_<ClassificationError<input_dtype>,
               std::shared_ptr<ClassificationError<input_dtype>>,
               boost::noncopyable,
               py::bases<IEntropyFunction<input_dtype> >>
               (("ClassificationError" + type_short).c_str(),
                "Computes the classification error as 1-\\max(p_i).\n\
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
                 py::init<

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<ClassificationError<input_dtype>>())
#endif
    .def("__eq__", ptr_ClassificationError_0, "-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
\n\
-----\n\
")
    .def("__ne__", ptr_ClassificationError_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<ClassificationError<input_dtype>>,
                               std::shared_ptr<IEntropyFunction<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___CLASSIFICATIONERROR_EXPORTER_H_