
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___SAMME_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___SAMME_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/boosting/samme.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  std::shared_ptr<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>> __construct_Samme() {
    auto *ptr = (Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>*) malloc(sizeof(Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_Samme(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Samme_0)
    (

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) const =
      &fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::operator==;
    bool (*ptr_Samme_1)
    (

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
,
     

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) =
    &ne_from_eq<fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>>;
    py::class_<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable,
               py::bases<IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> >>
               (("Samme" + type_short).c_str(),
                "SAMME boosting algorithm implementation\n\
\n\
Implements the SAMME boosting algorithm proposed by J. Zhu, H. Zou,\n\
S. Rosset and T. Hastie (\"Multi-class AdaBoost\", 2009).\n\
\n\
One can set the learning rate which specifies the contribution of each\n\
classifier.\n\
\n\
Output when using BoostingLeafManager is\n\
estimator_probability*estimator_weight.\n\
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
- int; int; uint; std::vector<float>; std::vector<float>\n\
- float; float; uint; std::vector<float>; std::vector<float>\n\
- double; double; uint; std::vector<float>; std::vector<float>\n\
- uint8_t; uint8_t; uint; std::vector<float>; std::vector<float>\n\
- uint8_t; int16_t; uint; std::vector<float>; std::vector<float>\n\
- uint8_t; int16_t; int16_t; std::vector<float>; std::vector<float>\n\
\n\
Serialization generation: 101\n\
\n\
-----\n\
",
                 py::init<

        py::optional<float>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>))
    .def_pickle(ParameterlessPickleSuite<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    .def("__eq__", ptr_Samme_0, "-----\n\
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
    .def("__ne__", ptr_Samme_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
                               std::shared_ptr<IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___SAMME_EXPORTER_H_