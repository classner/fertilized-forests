
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___RENYIENTROPY_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___RENYIENTROPY_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/impurities/renyientropy.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<RenyiEntropy<input_dtype>> __construct_RenyiEntropy() {
    auto *ptr = (RenyiEntropy<input_dtype>*) malloc(sizeof(RenyiEntropy<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<RenyiEntropy<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_RenyiEntropy(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::RenyiEntropy<input_dtype>::*ptr_RenyiEntropy_0)
    (

        const fertilized::IEntropyFunction<input_dtype> &
) const =
      &fertilized::RenyiEntropy<input_dtype>::operator==;
    bool (*ptr_RenyiEntropy_1)
    (

        const fertilized::IEntropyFunction<input_dtype> &
,
     

        const fertilized::IEntropyFunction<input_dtype> &
) =
    &ne_from_eq<fertilized::IEntropyFunction<input_dtype>>;
    py::class_<RenyiEntropy<input_dtype>,
               std::shared_ptr<RenyiEntropy<input_dtype>>,
               boost::noncopyable,
               py::bases<IEntropyFunction<input_dtype> >>
               (("RenyiEntropy" + type_short).c_str(),
                "Computes the Renyi entropy.\n\
\n\
Works correctly up to a total sum of elements of\n\
numeric_limits<input_dtype>::max().\n\
\n\
This is the Renyi entropy, as introduced by Alfred Renyi\n\
(see http://en.wikipedia.org/wiki/R%C3%A9nyi_entropy).\n\
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
    .def("__init__", py::make_constructor(__construct_RenyiEntropy<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<RenyiEntropy<input_dtype>>())
#endif
    .def("__eq__", ptr_RenyiEntropy_0, "-----\n\
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
    .def("__ne__", ptr_RenyiEntropy_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<RenyiEntropy<input_dtype>>,
                               std::shared_ptr<IEntropyFunction<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___RENYIENTROPY_EXPORTER_H_