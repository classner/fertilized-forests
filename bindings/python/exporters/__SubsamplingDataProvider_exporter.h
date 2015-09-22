
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___SUBSAMPLINGDATAPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___SUBSAMPLINGDATAPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/subsamplingdataprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_SubsamplingDataProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<SubsamplingDataProvider<input_dtype,annotation_dtype>,
               std::shared_ptr<SubsamplingDataProvider<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<IDataProvider<input_dtype, annotation_dtype> >>
               (("SubsamplingDataProvider" + type_short).c_str(),
                "Uses at maximum a certain amount of samples for node optimization.\n\
\n\
Tracks the loaded samples during training and adds new samples if possible.\n\
For leafs, all samples are loaded, even if its more than the maximum\n\
number of samples for split optimization.\n\
\n\
\n\
Can only be used for DFS (!!) for efficiency reasons.\n\
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
- uint8_t; int16_t\n\
- uint8_t; uint\n\
\n\
\n\
-----\n\
",
                 py::init<

        const size_t &,
        std::shared_ptr<fertilized::ISampleManager<input_dtype, annotation_dtype> >,
        py::optional<const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
#endif
    ;

    py::implicitly_convertible<std::shared_ptr<SubsamplingDataProvider<input_dtype,annotation_dtype>>,
                               std::shared_ptr<IDataProvider<input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___SUBSAMPLINGDATAPROVIDER_EXPORTER_H_