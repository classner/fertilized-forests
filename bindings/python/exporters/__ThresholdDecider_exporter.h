
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___THRESHOLDDECIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___THRESHOLDDECIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/deciders/thresholddecider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  std::shared_ptr<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>> __construct_ThresholdDecider() {
    auto *ptr = (ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>*) malloc(sizeof(ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype>
  void export_ThresholdDecider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    Array<double , 1 , 1> (fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>::*ptr_ThresholdDecider_0)
    (

) const =
      &fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>::compute_feature_importances;
    bool (fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>::*ptr_ThresholdDecider_1)
    (

        const fertilized::IDecider<input_dtype, feature_dtype, annotation_dtype> &
) const =
      &fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>::operator==;
    bool (*ptr_ThresholdDecider_2)
    (

        const fertilized::IDecider<input_dtype, feature_dtype, annotation_dtype> &
,
     

        const fertilized::IDecider<input_dtype, feature_dtype, annotation_dtype> &
) =
    &ne_from_eq<fertilized::IDecider<input_dtype, feature_dtype, annotation_dtype>>;
    py::class_<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>,
               std::shared_ptr<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IDecider<input_dtype, feature_dtype, annotation_dtype> >>
               (("ThresholdDecider" + type_short).c_str(),
                "A classifier manager for weak classifiers with a filter function,\n\
a feature calculation function and a thresholding.\n\
\n\
The classifier design is heavily inspired by \"Decision Forests for\n\
Classification, Regression, Density Estimation, Manifold Learning and\n\
Semi-Supervised Learning\" (Criminisi, Shotton and Konukoglu, 2011).\n\
With their definition, node classifier parameters :math:`\\theta` can\n\
be split into three parts:\n\
\n\
- :math:`\\phi`: a filter function that selects relevant features,\n\
- :math:`\\psi`: parameters of a function that combines the feature values\n\
to a single scalar,\n\
- :math:`\\tau`: thresholding parameters for the calculated scalar.\n\
\n\
With this model, a decision can be made at each node based on whether the\n\
calculated scalar lies withing the thresholding bounds.\n\
\n\
\n\
-----\n\
\n\
Available in:\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
Instantiations:\n\
\n\
- int; int; uint\n\
- uint8_t; uint8_t; uint\n\
- uint8_t; int16_t; uint\n\
- float; float; uint\n\
- double; double; uint\n\
- uint8_t; int16_t; int16_t\n\
- float; float; float\n\
- double; double; double\n\
\n\
\n\
-----\n\
",
                 py::init<

        const std::shared_ptr<fertilized::IFeatureSelectionProvider> &,
        const std::shared_ptr<typename fertilized::ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>::feat_calc_t> &,
        const std::shared_ptr<typename fertilized::ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>::thresh_opt_t> &,
        py::optional<const size_t &,
        const int &,
        const bool &,
        const float &,
        const unsigned int &,
        const bool &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>())
#endif
    .def("compute_feature_importances", ptr_ThresholdDecider_0, "Computes a feature importance vector.\n\
\n\
The vector is normalized to sum to 1.0. It contains the relative\n\
frequencies of the feature occurences. Its length is the number\n\
of available features.\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
-----\n\
")
    .def("__eq__", ptr_ThresholdDecider_1, "-----\n\
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
    .def("__ne__", ptr_ThresholdDecider_2, "")
    ;

    py::implicitly_convertible<std::shared_ptr<ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>,
                               std::shared_ptr<IDecider<input_dtype, feature_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___THRESHOLDDECIDER_EXPORTER_H_