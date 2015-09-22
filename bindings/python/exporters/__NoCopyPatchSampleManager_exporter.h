
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___NOCOPYPATCHSAMPLEMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___NOCOPYPATCHSAMPLEMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/data_providers/nocopypatchsamplemanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype>
  void export_NoCopyPatchSampleManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<NoCopyPatchSampleManager<input_dtype,annotation_dtype>,
               std::shared_ptr<NoCopyPatchSampleManager<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<PatchSampleManager<input_dtype, annotation_dtype> >>
               (("NoCopyPatchSampleManager" + type_short).c_str(),
                "A sample manager for Hough forests that limits the number of\n\
patches for one node, but does not copy anything but uses direct access\n\
tricks.\n\
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
- uint8_t; int16_t\n\
- uint8_t; uint\n\
\n\
\n\
-----\n\
",
                 py::init<

        const std::vector<fertilized::Array<const input_dtype, 3, 3> > &,
        const fertilized::Array<const annotation_dtype, 2, 2> &,
        const size_t &,
        const size_t &,
        const size_t &,
        const size_t &,
        py::optional<const bool &>
                         >())
#ifdef SERIALIZATION_ENABLED
#endif
    ;

    py::implicitly_convertible<std::shared_ptr<NoCopyPatchSampleManager<input_dtype,annotation_dtype>>,
                               std::shared_ptr<PatchSampleManager<input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___NOCOPYPATCHSAMPLEMANAGER_EXPORTER_H_