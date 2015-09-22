
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___TSALLISENTROPY_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___TSALLISENTROPY_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/tsallisentropy.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<TsallisEntropy<input_dtype>> __construct_TsallisEntropy() {
    auto *ptr = (TsallisEntropy<input_dtype>*) malloc(sizeof(TsallisEntropy<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<TsallisEntropy<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_TsallisEntropy(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::TsallisEntropy<input_dtype>::*ptr_TsallisEntropy_0)
    (

        const fertilized::IEntropyFunction<input_dtype> &
) const =
      &fertilized::TsallisEntropy<input_dtype>::operator==;
    bool (*ptr_TsallisEntropy_1)
    (

        const fertilized::IEntropyFunction<input_dtype> &
,
     

        const fertilized::IEntropyFunction<input_dtype> &
) =
    &ne_from_eq<fertilized::IEntropyFunction<input_dtype>>;
    py::class_<TsallisEntropy<input_dtype>,
               std::shared_ptr<TsallisEntropy<input_dtype>>,
               boost::noncopyable,
               py::bases<IEntropyFunction<input_dtype> >>
               (("TsallisEntropy" + type_short).c_str(),
                "Computes the Tsallis entropy.\n\
\n\
Works correctly up to a total sum of elements of\n\
numeric_limits<input_dtype>::max().\n\
\n\
This is the Tsallis entropy, as introduced by Constantino Tsallis\n\
(see http://en.wikipedia.org/wiki/Tsallis_entropy).\n\
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
-----\n\
",
                 py::init<

        const float &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_TsallisEntropy<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<TsallisEntropy<input_dtype>>())
#endif
    .def("__eq__", ptr_TsallisEntropy_0, "-----\n\
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
    .def("__ne__", ptr_TsallisEntropy_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<TsallisEntropy<input_dtype>>,
                               std::shared_ptr<IEntropyFunction<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___TSALLISENTROPY_EXPORTER_H_