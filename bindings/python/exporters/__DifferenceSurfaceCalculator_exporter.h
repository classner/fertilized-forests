
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___DIFFERENCESURFACECALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___DIFFERENCESURFACECALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/differencesurfacecalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_DifferenceSurfaceCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>::*ptr_DifferenceSurfaceCalculator_0)
    (

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
) const =
      &fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>::operator==;
    bool (*ptr_DifferenceSurfaceCalculator_1)
    (

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
,
     

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>>;
    py::class_<DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>,
               std::shared_ptr<DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> >>
               (("DifferenceSurfaceCalculator" + type_short).c_str(),
                "Calculates a feature as the difference between two data dimensions\n\
of inputs.\n\
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
- int; int; uint\n\
- uint8_t; int16_t; uint\n\
- float; float; uint\n\
- float; float; float\n\
- double; double; uint\n\
- double; double; double\n\
\n\
\n\
-----\n\
",
                 py::init<

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_DifferenceSurfaceCalculator_0, "-----\n\
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
    .def("__ne__", ptr_DifferenceSurfaceCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>,
                               std::shared_ptr<ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___DIFFERENCESURFACECALCULATOR_EXPORTER_H_