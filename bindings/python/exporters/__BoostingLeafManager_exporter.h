
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___BOOSTINGLEAFMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___BOOSTINGLEAFMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/leafs/boostingleafmanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename annotation_dtype>
  std::shared_ptr<BoostingLeafManager<input_dtype,annotation_dtype>> __construct_BoostingLeafManager() {
    auto *ptr = (BoostingLeafManager<input_dtype,annotation_dtype>*) malloc(sizeof(BoostingLeafManager<input_dtype,annotation_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<BoostingLeafManager<input_dtype,annotation_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename annotation_dtype>
  void export_BoostingLeafManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::BoostingLeafManager<input_dtype,annotation_dtype>::*ptr_BoostingLeafManager_0)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
) const =
      &fertilized::BoostingLeafManager<input_dtype,annotation_dtype>::operator==;
    bool (*ptr_BoostingLeafManager_1)
    (

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
,
     

        const fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> > &
) =
    &ne_from_eq<fertilized::ILeafManager<input_dtype, annotation_dtype, std::vector<float>, std::vector<float> >>;
    py::class_<BoostingLeafManager<input_dtype,annotation_dtype>,
               std::shared_ptr<BoostingLeafManager<input_dtype,annotation_dtype>>,
               boost::noncopyable,
               py::bases<ClassificationLeafManager<input_dtype, annotation_dtype> >>
               (("BoostingLeafManager" + type_short).c_str(),
                "Allows the boosting strategies to set their own tree functions\n\
to influence the combined result.\n\
\n\
Using thes LeafManager may lead to better classifcation results.\n\
\n\
Note that the output does not represent probabilites and may vary when\n\
using different IBoostingStrategies\n\
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
Serialization generation: 101\n\
\n\
-----\n\
",
                 py::init<

        const unsigned int &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_BoostingLeafManager<input_dtype,annotation_dtype>))
    .def_pickle(ParameterlessPickleSuite<BoostingLeafManager<input_dtype,annotation_dtype>>())
#endif
    .def("__eq__", ptr_BoostingLeafManager_0, "-----\n\
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
    .def("__ne__", ptr_BoostingLeafManager_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<BoostingLeafManager<input_dtype,annotation_dtype>>,
                               std::shared_ptr<ClassificationLeafManager<input_dtype, annotation_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___BOOSTINGLEAFMANAGER_EXPORTER_H_