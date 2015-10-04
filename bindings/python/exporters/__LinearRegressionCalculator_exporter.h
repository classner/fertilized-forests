
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___LINEARREGRESSIONCALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___LINEARREGRESSIONCALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/regression/linearregressioncalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<LinearRegressionCalculator<input_dtype>> __construct_LinearRegressionCalculator() {
    auto *ptr = (LinearRegressionCalculator<input_dtype>*) malloc(sizeof(LinearRegressionCalculator<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<LinearRegressionCalculator<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_LinearRegressionCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::LinearRegressionCalculator<input_dtype>::*ptr_LinearRegressionCalculator_0)
    (

        const fertilized::IRegressionCalculator<input_dtype> &
) const =
      &fertilized::LinearRegressionCalculator<input_dtype>::operator==;
    bool (*ptr_LinearRegressionCalculator_1)
    (

        const fertilized::IRegressionCalculator<input_dtype> &
,
     

        const fertilized::IRegressionCalculator<input_dtype> &
) =
    &ne_from_eq<fertilized::IRegressionCalculator<input_dtype>>;
    py::class_<LinearRegressionCalculator<input_dtype>,
               std::shared_ptr<LinearRegressionCalculator<input_dtype>>,
               boost::noncopyable,
               py::bases<IRegressionCalculator<input_dtype> >>
               (("LinearRegressionCalculator" + type_short).c_str(),
                "Calculator for linear regression.\n\
\n\
This regression calculator uses a linear combination of the input dimensions\n\
to predict the output value. Therefore it does not provide a constant prediction\n\
or a constant prediction covariance matrix.\n\
If there are multiple output values to be predicted, each output is produced\n\
using its own linear model.\n\
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
- double\n\
\n\
\n\
-----\n\
",
                 py::init<

        py::optional<const bool &,
        const input_dtype &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_LinearRegressionCalculator<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<LinearRegressionCalculator<input_dtype>>())
#endif
    .def("__eq__", ptr_LinearRegressionCalculator_0, "-----\n\
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
    .def("__ne__", ptr_LinearRegressionCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<LinearRegressionCalculator<input_dtype>>,
                               std::shared_ptr<IRegressionCalculator<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___LINEARREGRESSIONCALCULATOR_EXPORTER_H_