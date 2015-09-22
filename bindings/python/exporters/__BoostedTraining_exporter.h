
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___BOOSTEDTRAINING_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___BOOSTEDTRAINING_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/trainings/boostedtraining.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  std::shared_ptr<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>> __construct_BoostedTraining() {
    auto *ptr = (BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>*) malloc(sizeof(BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_BoostedTraining(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_BoostedTraining_0)
    (

        const fertilized::ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) const =
      &fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::operator==;
    bool (*ptr_BoostedTraining_1)
    (

        const fertilized::ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
,
     

        const fertilized::ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) =
    &ne_from_eq<fertilized::ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>>;
    py::class_<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable,
               py::bases<ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> >>
               (("BoostedTraining" + type_short).c_str(),
                "Implements a boosted training that uses a boosting implementation defined by an IBoostingStrategy\n\
\n\
Trains all trees using a given boosting algorithm implementation\n\
Use a BoostingLeafManager to let the boosting strategies decide their weight functions\n\
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

        const std::shared_ptr<typename fertilized::BoostedTraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::boost_strat_t> &
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>))
    .def_pickle(ParameterlessPickleSuite<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    .def("__eq__", ptr_BoostedTraining_0, "Standard comparison operator.\n\
\n\
-----\n\
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
    .def("__ne__", ptr_BoostedTraining_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
                               std::shared_ptr<ITraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___BOOSTEDTRAINING_EXPORTER_H_