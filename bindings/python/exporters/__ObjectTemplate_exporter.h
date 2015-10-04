
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___OBJECTTEMPLATE_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___OBJECTTEMPLATE_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/objecttemplate.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  std::shared_ptr<ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>> __construct_ObjectTemplate() {
    auto *ptr = (ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>*) malloc(sizeof(ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_ObjectTemplate(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable>
               (("ObjectTemplate" + type_short).c_str(),
                "Object template.\n\
\n\
After having described the object, add a section like the following\n\
to specify in which interfaces the object should be available, and, if it\n\
is templated, which instantiations of the object. The instantiations are\n\
;-separated lists of the C++ types to use.\n\
\n\
To start and end this section, use exactly -----. End the lists with a dot\n\
and add an empty line after the last list. This is not due to our parser,\n\
but due to doxygen. It is required to get a meaningful rendering for the\n\
documentation.\n\
\n\
Use exactly the library template names `input_dtype`, `feature_dtype`,\n\
`annotation_dtype`, `leaf_return_dtype`, `forest_dtype` for your\n\
objects as necessary (you may omit unnecessary ones). If your class is\n\
templated differently, only one possible\n\
template instantiation can be used for the interfaces. In that case, you\n\
have to specify this with a parser list \"Soil type always:\". You can find\n\
an example for this in impurities/shannonentropy.h.\n\
\n\
The specification of the \"Serialization generation:\" is important if you\n\
want to serialize your object and remain compatible to older versions\n\
of the library. Specify the number as the version number of the library\n\
in hundreds format (e.g., 1.00 as 100) plus one\n\
(e.g., if the current library version is 1.01, use 102). Your self-\n\
compiled library version with the additional object will be backwards\n\
compatible with all lower library versions. Increase the library version in\n\
the file 'global.h' to the same value!\n\
\n\
IMPORTANT: you HAVE to adjust the `Serializaton generation:` version number\n\
and the library version in 'global.h' to serialize your object and\n\
maintain backwards compatibility!\n\
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
- int; int; uint; std::vector<float>; std::vector<float>\n\
- float; float; uint; std::vector<float>; std::vector<float>\n\
\n\
Serialization generation: 100\n\
\n\
-----\n\
",
                 py::init<

        const unsigned int &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>))
    .def_pickle(ParameterlessPickleSuite<ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___OBJECTTEMPLATE_EXPORTER_H_