
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/threshold_optimizers/randomizedclassificationthresholdoptimizer.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>> __construct_RandomizedClassificationThresholdOptimizer() {
    auto *ptr = (RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>*) malloc(sizeof(RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_RandomizedClassificationThresholdOptimizer(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>::*ptr_RandomizedClassificationThresholdOptimizer_0)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
) const =
      &fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>::operator==;
    bool (*ptr_RandomizedClassificationThresholdOptimizer_1)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
,
     

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>;
    py::class_<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>,
               std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> >>
               (("RandomizedClassificationThresholdOptimizer" + type_short).c_str(),
                "Optimizes a threshold by selecting the best of few random values.\n\
\n\
Supports only classification annotations (unsigned int) with annotation\n\
values in [0, ..., n_classes[.\n\
The threshold optimizer draws n_thresholds random values between\n\
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
        const size_t &,
        const std::shared_ptr<fertilized::IGainCalculator<float> > &,
        py::optional<const float &,
        const size_t &,
        const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_RandomizedClassificationThresholdOptimizer_0, "-----\n\
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
    .def("__ne__", ptr_RandomizedClassificationThresholdOptimizer_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>,
                               std::shared_ptr<IThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___RANDOMIZEDCLASSIFICATIONTHRESHOLDOPTIMIZER_EXPORTER_H_