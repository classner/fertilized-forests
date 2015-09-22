
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IREGRESSIONCALCULATOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IREGRESSIONCALCULATOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/regression/iregressioncalculator.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype>
  void export_IRegressionCalculator(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IRegressionCalculator<input_dtype>,
               boost::noncopyable>
               (("IRegressionCalculator" + type_short).c_str(),
                "The interface for a regression calculator.\n\
\n\
Given a set of annotated samples, it calculates a model that explains the dependency\n\
between the input variables and the response variables of the sampels.\n\
This model is chosen as good as its parameters allow it to fit the data.\n\
With this model, a prediction for the response variables on a single sample\n\
can be calculated.\n\
Additionally, the probability distribution for a specific output value\n\
given a single sample can be computed.\n\
Often, samples have to be incrementally added or removed from the sample set.\n\
This can be done by initializing a IRegressionCalculator with\n\
the complete set of samples and afterwards specify an interval as the index-range\n\
denoting which sample are actually used for the regression model.\n\
Depending on the type of regression calculator, this can lead to a major\n\
performance increase.\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
\n\
Instantiations:\n\
\n\
- float\n\
- double\n\
\n\
\n\
-----\n\
",
                 py::no_init)
#ifdef SERIALIZATION_ENABLED
#endif
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___IREGRESSIONCALCULATOR_EXPORTER_H_