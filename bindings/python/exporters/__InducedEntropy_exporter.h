
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___INDUCEDENTROPY_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___INDUCEDENTROPY_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/inducedentropy.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<InducedEntropy<input_dtype>> __construct_InducedEntropy() {
    auto *ptr = (InducedEntropy<input_dtype>*) malloc(sizeof(InducedEntropy<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<InducedEntropy<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_InducedEntropy(const std::string &type_short) {
    // Explicit function pointers and overloads.
    float (fertilized::InducedEntropy<input_dtype>::*ptr_InducedEntropy_0)
    (

        const std::vector<input_dtype> &,
        const float &
) const =
      &fertilized::InducedEntropy<input_dtype>::operator();
    bool (fertilized::InducedEntropy<input_dtype>::*ptr_InducedEntropy_1)
    (

        const fertilized::IEntropyFunction<input_dtype> &
) const =
      &fertilized::InducedEntropy<input_dtype>::operator==;
    bool (*ptr_InducedEntropy_2)
    (

        const fertilized::IEntropyFunction<input_dtype> &
,
     

        const fertilized::IEntropyFunction<input_dtype> &
) =
    &ne_from_eq<fertilized::IEntropyFunction<input_dtype>>;
    py::class_<InducedEntropy<input_dtype>,
               std::shared_ptr<InducedEntropy<input_dtype>>,
               boost::noncopyable,
               py::bases<IEntropyFunction<input_dtype> >>
               (("InducedEntropy" + type_short).c_str(),
                "Computes the induced p entropy.\n\
\n\
Works correctly up to a total sum of elements of\n\
numeric_limits<input_dtype>::max().\n\
\n\
This is the induced p-metric of the vector of :math:`n` class probabilities\n\
and the point of maximum unorder (the vector with all entries\n\
:math:`\\frac{1}{n}`) in the n-dimensional space without applying the root.\n\
It is equal to the Gini-measure for :math:`p=2`.\n\
\n\
The definition for :math:`c` classes:\n\
\n\
.. math::\n\
  \\sum_{i=1}^{c} \\left\\Vert p_i - 0.5\\right\\Vert ^p\n\
.\n\
\n\
The differential entropy for a normal distribution with covariance\n\
matrix :math:`\\Sigma` in :math:`n` dimensions is defined as:\n\
\n\
.. math::\n\
  \\frac{1}{\\sqrt{p^n}}\\cdot\\left(\\sqrt{2\\pi}^n\\cdot\\sqrt{\\left|\\Sigma\\right|}\\right)^{-(p-1)}\n\
\n\
\n\
In the differential normal case, the most useful values for :math:`p` are\n\
very close to 1 (e.g. 1.00001)! :math:`p=2` is already equivalent to the\n\
infinite norm!\n\
\n\
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
- float\n\
- uint\n\
\n\
Soil type always:\n\
\n\
- float\n\
\n\
\n\
-----\n\
",
                 py::init<

        const float &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_InducedEntropy<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<InducedEntropy<input_dtype>>())
#endif
    .def("__call__", ptr_InducedEntropy_0, "The method is supposed to be fast and hence no checking for the validity\n\
of fsum is done in release mode!\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
\n\
-----\n\
\n\
\n\
Parameters\n\
==========\n\
\n\
class_member_numbers : Vector  The class member counts (class histogram).\n\
\n\
fsum : float The total of the class_member_numbers Vector.\n\
  \\return The calculated entropy value.")
    .def("__eq__", ptr_InducedEntropy_1, "-----\n\
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
    .def("__ne__", ptr_InducedEntropy_2, "")
    ;

    py::implicitly_convertible<std::shared_ptr<InducedEntropy<input_dtype>>,
                               std::shared_ptr<IEntropyFunction<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___INDUCEDENTROPY_EXPORTER_H_