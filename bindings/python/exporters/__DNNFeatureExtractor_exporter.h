
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___DNNFEATUREEXTRACTOR_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___DNNFEATUREEXTRACTOR_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/feature_extraction/dnnfeatureextractor.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DNNFeatureExtractor_extract_overloads, extract, 1, 2)
  
  void export_DNNFeatureExtractor(const std::string &type_short) {
    // Explicit function pointers and overloads.
    Array<float , 4 , 4> (fertilized::DNNFeatureExtractor::*ptr_DNNFeatureExtractor_0)
    (

        const std::vector<fertilized::Array<float, 3, 3> > &,
        const bool &
) =
      &fertilized::DNNFeatureExtractor::extract;
    py::class_<DNNFeatureExtractor,
               std::shared_ptr<DNNFeatureExtractor>,
               boost::noncopyable>
               (("DNNFeatureExtractor" + type_short).c_str(),
                "Extracts DNN features using a pretrained caffe network.\n\
\n\
To obtain reproducible results, you have to remove the dropout layers\n\
from the network specification file (this has been done for the default\n\
AlexNet). During extraction, always the full batch size is used. This\n\
means, that if you repeatedly only extract features from one image with\n\
the extract method, most of the batch will be unused. You should observe\n\
large speed gains by reducing the batch size in the model specification\n\
file to a batch size of one in that case.\n\
\n\
The mean image must be subtracted from any image before\n\
using the feature extractor. This can be done within the `extract` method,\n\
or, if you want to use many samples from an image, you can do that before.\n\
The default mean image is the one of the ImageNet dataset. The mean image\n\
format is a text file with a very simple layout:\n\
\n\
\n\
- the first line consists of the number of rows,\n\
- the second line consists of the columns,\n\
- the third line consists of the number of channels,\n\
- the fourth line contains all pixel values, in OpenCV memory layout\n\
(rows, columns, channels, where channels are contiguous).\n\
\n\
-----\n\
\n\
Available in:\n\
- C++\n\
- Python\n\
- Matlab\n\
\n\
\n\
-----\n\
",
                 py::init<

        std::string,
        std::string,
        std::string,
        py::optional<const bool &,
        const int &,
        std::string>
                         >())
#ifdef SERIALIZATION_ENABLED
#endif
    .def("extract", ptr_DNNFeatureExtractor_0, DNNFeatureExtractor_extract_overloads())
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___DNNFEATUREEXTRACTOR_EXPORTER_H_