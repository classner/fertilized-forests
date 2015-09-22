
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___HOUGHLEAFMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___HOUGHLEAFMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/leafs/houghleafmanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename annotation_dtype>
  std::shared_ptr<HoughLeafManager<input_dtype,annotation_dtype>> __construct_HoughLeafManager() {
    auto *ptr = (HoughLeafManager<input_dtype,annotation_dtype>*) malloc(sizeof(HoughLeafManager<input_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<HoughLeafManager<input_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename annotation_dtype>
  void export_HoughLeafManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::HoughLeafManager<input_dtype,annotation_dtype>::*ptr_HoughLeafManager_0)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > >, std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > > > > &
) const =
      &fertilized::HoughLeafManager<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_HoughLeafManager_1)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > >, std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > > > > &
,
     

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > >, std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > > > > &
) =
    &ne_from_eq<fertilized::ILeafManager<input_dtype, annotation_dtype, std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > >, std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype> > > > >>;
    py::class_<HoughLeafManager<input_dtype,annotation_dtype>,
               std::shared_ptr<HoughLeafManager<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ILeafManager<input_dtype, annotation_dtype,
                          std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                          std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>> >>
               (("HoughLeafManager" + type_short).c_str(),
                "Stores the offset vectors for positive samples and their\n\
probabilities in the leafs.\n\
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
\n\
\n\
-----\n\
",
                 py::init<

        py::optional<const unsigned int &,
        const size_t &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_HoughLeafManager<input_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<HoughLeafManager<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_HoughLeafManager_0, "-----\n\
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
    .def("__ne__", ptr_HoughLeafManager_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<HoughLeafManager<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ILeafManager<input_dtype, annotation_dtype,
                          std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                          std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___HOUGHLEAFMANAGER_EXPORTER_H_