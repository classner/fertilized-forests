
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___QUADRATICSURFACECALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___QUADRATICSURFACECALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/quadraticsurfacecalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename annotation_dtype>
  std::shared_ptr<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>> __construct_QuadraticSurfaceCalculator() {
    auto *ptr = (QuadraticSurfaceCalculator<input_dtype,annotation_dtype>*) malloc(sizeof(QuadraticSurfaceCalculator<input_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename annotation_dtype>
  void export_QuadraticSurfaceCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>::*ptr_QuadraticSurfaceCalculator_0)
    (

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
) const =
      &fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_QuadraticSurfaceCalculator_1)
    (

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
,
     

        const fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype> &
) =
    &ne_from_eq<fertilized::ISurfaceCalculator<input_dtype, float, annotation_dtype>>;
    py::class_<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>,
               std::shared_ptr<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ISurfaceCalculator<input_dtype, float, annotation_dtype> >>
               (("QuadraticSurfaceCalculator" + type_short).c_str(),
                "Calculates a feature as the response value of a quadratic\n\
surface (see CriminisiShotton 2013, p. 15). Currently only supports two\n\
feature dimensions.\n\
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
- double; uint\n\
- double; double\n\
\n\
\n\
-----\n\
",
                 py::init<

        const size_t &,
        const std::vector<float> &,
        py::optional<const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_QuadraticSurfaceCalculator<input_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_QuadraticSurfaceCalculator_0, "-----\n\
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
    .def("__ne__", ptr_QuadraticSurfaceCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ISurfaceCalculator<input_dtype, float, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___QUADRATICSURFACECALCULATOR_EXPORTER_H_