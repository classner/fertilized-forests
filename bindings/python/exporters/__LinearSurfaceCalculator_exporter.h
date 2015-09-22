
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___LINEARSURFACECALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___LINEARSURFACECALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/linearsurfacecalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename annotation_dtype>
  std::shared_ptr<LinearSurfaceCalculator<input_dtype,annotation_dtype>> __construct_LinearSurfaceCalculator() {
    auto *ptr = (LinearSurfaceCalculator<input_dtype,annotation_dtype>*) malloc(sizeof(LinearSurfaceCalculator<input_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<LinearSurfaceCalculator<input_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename annotation_dtype>
  void export_LinearSurfaceCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>::*ptr_LinearSurfaceCalculator_0)
    (

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
) const =
      &fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_LinearSurfaceCalculator_1)
    (

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
,
     

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
) =
    &ne_from_eq<fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype>>;
    py::class_<LinearSurfaceCalculator<input_dtype,annotation_dtype>,
               std::shared_ptr<LinearSurfaceCalculator<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ISurfaceCalculator<input_dtype, float, annotation_dtype> >>
               (("LinearSurfaceCalculator" + type_short).c_str(),
                "Calculates a feature as linear combination of inputs.\n\
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
- int; uint\n\
- uint8_t; uint\n\
- float; uint\n\
- float; float\n\
- double; double\n\
- double; uint\n\
\n\
\n\
-----\n\
",
                 py::init<

        const size_t &,
        py::optional<const size_t &,
        const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_LinearSurfaceCalculator<input_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<LinearSurfaceCalculator<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_LinearSurfaceCalculator_0, "-----\n\
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
    .def("__ne__", ptr_LinearSurfaceCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<LinearSurfaceCalculator<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ISurfaceCalculator<input_dtype, float, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___LINEARSURFACECALCULATOR_EXPORTER_H_