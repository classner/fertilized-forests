
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___SHANNONENTROPY_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___SHANNONENTROPY_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/shannonentropy.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype>
  void export_ShannonEntropy(const std::string &type_short) {
    // Explicit function pointers and overloads.
    float (fertilized::ShannonEntropy<input_dtype>::*ptr_ShannonEntropy_0)
    (

        const std::vector<input_dtype> &,
        const float &
) const =
      &fertilized::ShannonEntropy<input_dtype>::operator();
    bool (fertilized::ShannonEntropy<input_dtype>::*ptr_ShannonEntropy_1)
    (

        const fertilized::IEntropyFunction<input_dtype> &
) const =
      &fertilized::ShannonEntropy<input_dtype>::operator==;
    bool (*ptr_ShannonEntropy_2)
    (

        const fertilized::IEntropyFunction<input_dtype> &
,
     

        const fertilized::IEntropyFunction<input_dtype> &
) =
    &ne_from_eq<fertilized::IEntropyFunction<input_dtype>>;
    py::class_<ShannonEntropy<input_dtype>,
               std::shared_ptr<ShannonEntropy<input_dtype>>,
               boost::noncopyable,
               py::bases<IEntropyFunction<input_dtype> >>
               (("ShannonEntropy" + type_short).c_str(),
                "Computes the classical Shannon-Entropy.\n\
\n\
Works correctly up to a total sum of elements of\n\
numeric_limits<input_dtype>::max().\n\
\n\
For classes :math:`C={c_1, \\ldots, c_n}`, the Shannon entropy is defined as\n\
\n\
.. math::\n\
  -\\sum_{c\\in C}p_z\\cdot \\log_2 p_z.\n\
\n\
\n\
The differential Shannon entropy for a normal distribution with covariance\n\
matrix :math:`\\Sigma` in :math:`n` dimensions is defined as\n\
\n\
.. math::\n\
  \\frac{1}{2}\\log\\left((2\\pi e)^n\\left|\\Sigma\\right|\\right).\n\
\n\
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

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<ShannonEntropy<input_dtype>>())
#endif
    .def("__call__", ptr_ShannonEntropy_0, "The method is supposed to be fast and hence no checking for the validity\n\
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
class_member_numbers : Vector\n\
  The class member counts (class histogram).\n\
\n\
fsum : float\n\
  The total of the class_member_numbers Vector.\n\
  \\return The calculated entropy value.")
    .def("__eq__", ptr_ShannonEntropy_1, "-----\n\
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
    .def("__ne__", ptr_ShannonEntropy_2, "")
    ;

    py::implicitly_convertible<std::shared_ptr<ShannonEntropy<input_dtype>>,
                               std::shared_ptr<IEntropyFunction<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___SHANNONENTROPY_EXPORTER_H_