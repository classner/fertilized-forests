
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/threshold_optimizers/varianceclassificationthresholdoptimizer.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  std::shared_ptr<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>> __construct_VarianceClassificationThresholdOptimizer() {
    auto *ptr = (VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>*) malloc(sizeof(VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_VarianceClassificationThresholdOptimizer(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>::*ptr_VarianceClassificationThresholdOptimizer_0)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
) const =
      &fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>::operator==;
    bool (*ptr_VarianceClassificationThresholdOptimizer_1)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
,
     

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>;
    py::class_<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>,
               std::shared_ptr<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>>
               (("VarianceClassificationThresholdOptimizer" + type_short).c_str(),
                "Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.\n\
\n\
The annotations are assumed to be a class label followed by its offset\n\
values. Since all these values must be of the same datatype, the only supported type\n\
is (signed) int in this case (to allow for negative offsets). The class labels\n\
must still be in [0; n_classes - 1].\n\
\n\
This threshold optimizer draws n_thresholds random values between\n\
the minimum and maximum observed feature value and returns the best\n\
one.\n\
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
- int; float; uint\n\
- float; int; uint\n\
- uint8_t; int; uint\n\
- uint8_t; uint8_t; uint\n\
- uint8_t; float; uint\n\
- uint8_t; int16_t; uint\n\
- float; float; uint\n\
- double; double; uint\n\
- uint8_t; int16_t; int16_t\n\
\n\
\n\
-----\n\
",
                 py::init<

        const size_t &,
        py::optional<const size_t &,
        const size_t &,
        const float &,
        const unsigned int &>
                         >())
    // Constructors.
    .def(py::init<

        const size_t &,
        const size_t &,
        const size_t &,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > &,
        py::optional<const float &,
        const unsigned int &>
                 >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_VarianceClassificationThresholdOptimizer_0, "-----\n\
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
    .def("__ne__", ptr_VarianceClassificationThresholdOptimizer_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>,
                               std::shared_ptr<IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>> >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___VARIANCECLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_