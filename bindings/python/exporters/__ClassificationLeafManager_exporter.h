
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___CLASSIFICATIONLEAFMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___CLASSIFICATIONLEAFMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/leafs/classificationleafmanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename annotation_dtype>
  std::shared_ptr<ClassificationLeafManager<input_dtype,annotation_dtype>> __construct_ClassificationLeafManager() {
    auto *ptr = (ClassificationLeafManager<input_dtype,annotation_dtype>*) malloc(sizeof(ClassificationLeafManager<input_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<ClassificationLeafManager<input_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename annotation_dtype>
  void export_ClassificationLeafManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>::*ptr_ClassificationLeafManager_0)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
) const =
      &fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_ClassificationLeafManager_1)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
,
     

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
) =
    &ne_from_eq<fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> >>;
    py::class_<ClassificationLeafManager<input_dtype,annotation_dtype>,
               std::shared_ptr<ClassificationLeafManager<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ILeafManager<input_dtype, annotation_dtype,
                          std::vector<float>, std::vector<float>> >>
               (("ClassificationLeafManager" + type_short).c_str(),
                "Stores the probability distributions for n_classes at a leaf.\n\
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
- int; uint\n\
- float; uint\n\
- double; uint\n\
- uint8_t; uint\n\
- uint8_t; int16_t\n\
\n\
\n\
-----\n\
",
                 py::init<

        const unsigned int &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_ClassificationLeafManager<input_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<ClassificationLeafManager<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_ClassificationLeafManager_0, "-----\n\
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
    .def("__ne__", ptr_ClassificationLeafManager_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<ClassificationLeafManager<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ILeafManager<input_dtype, annotation_dtype,
                          std::vector<float>, std::vector<float>> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___CLASSIFICATIONLEAFMANAGER_EXPORTER_H_