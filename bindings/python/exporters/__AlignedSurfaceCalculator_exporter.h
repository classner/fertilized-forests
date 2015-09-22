
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ALIGNEDSURFACECALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ALIGNEDSURFACECALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/alignedsurfacecalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_AlignedSurfaceCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>::*ptr_AlignedSurfaceCalculator_0)
    (

        const fertilized::ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> &
) const =
      &fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_AlignedSurfaceCalculator_1)
    (

        const fertilized::ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> &
,
     

        const fertilized::ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype>>;
    py::class_<AlignedSurfaceCalculator<input_dtype,annotation_dtype>,
               std::shared_ptr<AlignedSurfaceCalculator<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> >>
               (("AlignedSurfaceCalculator" + type_short).c_str(),
                "Forwards the data as features.\n\
\n\
Does not require any parameters.\n\
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

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<AlignedSurfaceCalculator<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_AlignedSurfaceCalculator_0, "-----\n\
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
    .def("__ne__", ptr_AlignedSurfaceCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<AlignedSurfaceCalculator<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ISurfaceCalculator<input_dtype, input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___ALIGNEDSURFACECALCULATOR_EXPORTER_H_