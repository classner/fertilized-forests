
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ENTROPYGAIN_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ENTROPYGAIN_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/gains/entropygain.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<EntropyGain<input_dtype>> __construct_EntropyGain() {
    auto *ptr = (EntropyGain<input_dtype>*) malloc(sizeof(EntropyGain<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<EntropyGain<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_EntropyGain(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::EntropyGain<input_dtype>::*ptr_EntropyGain_0)
    (

        const fertilized::IGainCalculator<input_dtype> &
) const =
      &fertilized::EntropyGain<input_dtype>::operator==;
    bool (*ptr_EntropyGain_1)
    (

        const fertilized::IGainCalculator<input_dtype> &
,
     

        const fertilized::IGainCalculator<input_dtype> &
) =
    &ne_from_eq<fertilized::IGainCalculator<input_dtype>>;
    py::class_<EntropyGain<input_dtype>,
               std::shared_ptr<EntropyGain<input_dtype>>,
               boost::noncopyable,
               py::bases<IGainCalculator<input_dtype> >>
               (("EntropyGain" + type_short).c_str(),
                "Calculates the gain as difference of current entropy and the\n\
weighted sum of subgroup entropies.\n\
\n\
Works correctly up to a total sum of elements of\n\
min(numeric_limits<float>::max(), numeric_limits<input_dtype>::max())\n\
and the limitations of the selected entropy function.\n\
Speed optimized function that does no checks in release mode!\n\
\n\
Parameters\n\
==========\n\
\n\
input_dtype : The datatype for counting class members. This might\n\
  be a float if sample weights are used.\n\
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

        const std::shared_ptr<typename fertilized::EntropyGain<input_dtype>::entropy_func_t> &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_EntropyGain<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<EntropyGain<input_dtype>>())
#endif
    .def("__eq__", ptr_EntropyGain_0, "-----\n\
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
    .def("__ne__", ptr_EntropyGain_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<EntropyGain<input_dtype>>,
                               std::shared_ptr<IGainCalculator<input_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___ENTROPYGAIN_EXPORTER_H_