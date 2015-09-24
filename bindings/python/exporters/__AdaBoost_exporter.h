
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ADABOOST_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ADABOOST_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/boosting/adaboost.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_AdaBoost(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_AdaBoost_0)
    (

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) const =
      &fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::operator==;
    bool (*ptr_AdaBoost_1)
    (

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
,
     

        const fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) =
    &ne_from_eq<fertilized::IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>>;
    py::class_<AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable,
               py::bases<IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> >>
               (("AdaBoost" + type_short).c_str(),
                "AdaBoost.M2 boosting algorithm implementation\n\
\n\
Implements the original AdaBoost algorithm proposed by Freund and Schapire\n\
\n\
See \"A decision-theoretic generalization of on-line learning and an\n\
application to boosting\". Journal of Computer and System Sciences 55. 1997\n\
\n\
To support multi-class classification, the AdaBoost.M2 algorithm is used.\n\
\n\
Output when using BoostingLeafManager is\n\
estimator_probability*std::log(1.f/beta).\n\
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

                         >())
#ifdef SERIALIZATION_ENABLED
    .def_pickle(ParameterlessPickleSuite<AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    .def("__eq__", ptr_AdaBoost_0, "-----\n\
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
    .def("__ne__", ptr_AdaBoost_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
                               std::shared_ptr<IBoostingStrategy<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___ADABOOST_EXPORTER_H_