
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___DIRECTPATCHDIFFERENCESURFCALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___DIRECTPATCHDIFFERENCESURFCALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/directpatchdifferencesurfcalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  std::shared_ptr<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>> __construct_DirectPatchDifferenceSurfCalculator() {
    auto *ptr = (DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>*) malloc(sizeof(DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_DirectPatchDifferenceSurfCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>::*ptr_DirectPatchDifferenceSurfCalculator_0)
    (

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
) const =
      &fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>::operator==;
    bool (*ptr_DirectPatchDifferenceSurfCalculator_1)
    (

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
,
     

        const fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype>>;
    py::class_<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>,
               std::shared_ptr<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> >>
               (("DirectPatchDifferenceSurfCalculator" + type_short).c_str(),
                "Calculates a feature as the difference between two data dimensions\n\
of inputs.\n\
\n\
In contrast to the DifferenceSurfaceCalculator, works with patches\n\
in images directly. It only works together with a SubsamplingDataProvider\n\
with a NoCopyPatchSampleManager, because they provide the images\n\
in the correct format.\n\
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
- uint8_t; int16_t; uint\n\
- uint8_t; int16_t; int16_t\n\
\n\
\n\
-----\n\
",
                 py::init<

        const size_t &,
        const size_t &,
        const size_t &,
        const bool &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_DirectPatchDifferenceSurfCalculator_0, "-----\n\
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
    .def("__ne__", ptr_DirectPatchDifferenceSurfCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>,
                               std::shared_ptr<ISurfaceCalculator<input_dtype, feature_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___DIRECTPATCHDIFFERENCESURFCALCULATOR_EXPORTER_H_