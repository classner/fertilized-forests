
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___CONSTANTREGRESSIONCALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___CONSTANTREGRESSIONCALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/regression/constantregressioncalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype>
  void export_ConstantRegressionCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::ConstantRegressionCalculator<input_dtype>::*ptr_ConstantRegressionCalculator_0)
    (

        const fertilized::IRegressionCalculator<input_dtype> &
) const =
      &fertilized::ConstantRegressionCalculator<input_dtype>::operator==;
    bool (*ptr_ConstantRegressionCalculator_1)
    (

        const fertilized::IRegressionCalculator<input_dtype> &
,
     

        const fertilized::IRegressionCalculator<input_dtype> &
) =
    &ne_from_eq<fertilized::IRegressionCalculator<input_dtype>>;
    py::class_<ConstantRegressionCalculator<input_dtype>,
               std::shared_ptr<ConstantRegressionCalculator<input_dtype>>,
               boost::noncopyable,
               py::bases<IRegressionCalculator<input_dtype> >>
               (("ConstantRegressionCalculator" + type_short).c_str(),
                "Calculator for constant regression.\n\
\n\
This regression calculator uses a constant value to predict the output value.\n\
Therefore, it provides a constant prediction and a constant prediction covariance matrix.\n\
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

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<ConstantRegressionCalculator<input_dtype>>())
#endif
    .def("__eq__", ptr_ConstantRegressionCalculator_0, "-----\n\
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
    .def("__ne__", ptr_ConstantRegressionCalculator_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<ConstantRegressionCalculator<input_dtype>>,
                               std::shared_ptr<IRegressionCalculator<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___CONSTANTREGRESSIONCALCULATOR_EXPORTER_H_