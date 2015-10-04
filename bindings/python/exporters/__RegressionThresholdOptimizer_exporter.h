
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___REGRESSIONTHRESHOLDOPTIMIZER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___REGRESSIONTHRESHOLDOPTIMIZER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/threshold_optimizers/regressionthresholdoptimizer.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype>
  std::shared_ptr<RegressionThresholdOptimizer<input_dtype,feature_dtype>> __construct_RegressionThresholdOptimizer() {
    auto *ptr = (RegressionThresholdOptimizer<input_dtype,feature_dtype>*) malloc(sizeof(RegressionThresholdOptimizer<input_dtype,feature_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<RegressionThresholdOptimizer<input_dtype,feature_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype>
  void export_RegressionThresholdOptimizer(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>::*ptr_RegressionThresholdOptimizer_0)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> &
) const =
      &fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>::operator==;
    bool (*ptr_RegressionThresholdOptimizer_1)
    (

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> &
,
     

        const fertilized::IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> &
) =
    &ne_from_eq<fertilized::IThresholdOptimizer<input_dtype, feature_dtype, input_dtype>>;
    py::class_<RegressionThresholdOptimizer<input_dtype,feature_dtype>,
               std::shared_ptr<RegressionThresholdOptimizer<input_dtype,feature_dtype>>,
               boost::noncopyable,
               py::bases<IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> >>
               (("RegressionThresholdOptimizer" + type_short).c_str(),
                "Optimizes the threshold for splitting a dataset, to ensure optimal\n\
regression results on the splits.\n\
\n\
This threshold optimizer draws n_thresholds random values between\n\
the minimum and maximum observed feature value and returns the best\n\
one.\n\
Multiple annotations (and therefore multiple output regression) are allowed.\n\
The splits are evaluated using a provided regression calculator.\n\
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
- float; float\n\
- double; double\n\
\n\
\n\
-----\n\
\n\
",
                 py::init<

        const size_t &,
        const std::shared_ptr<fertilized::IRegressionCalculator<input_dtype> > &,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > &,
        py::optional<const float &,
        const size_t &,
        const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_RegressionThresholdOptimizer<input_dtype,feature_dtype>))
    .def_pickle(ParameterlessPickleSuite<RegressionThresholdOptimizer<input_dtype,feature_dtype>>())
#endif
    .def("__eq__", ptr_RegressionThresholdOptimizer_0, "-----\n\
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
    .def("__ne__", ptr_RegressionThresholdOptimizer_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<RegressionThresholdOptimizer<input_dtype,feature_dtype>>,
                               std::shared_ptr<IThresholdOptimizer<input_dtype, feature_dtype, input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___REGRESSIONTHRESHOLDOPTIMIZER_EXPORTER_H_