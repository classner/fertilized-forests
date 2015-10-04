
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___REGRESSIONLEAFMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___REGRESSIONLEAFMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/leafs/regressionleafmanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype>
  std::shared_ptr<RegressionLeafManager<input_dtype>> __construct_RegressionLeafManager() {
    auto *ptr = (RegressionLeafManager<input_dtype>*) malloc(sizeof(RegressionLeafManager<input_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<RegressionLeafManager<input_dtype>>(ptr, free);
  };
#endif
  template <typename input_dtype>
  void export_RegressionLeafManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::RegressionLeafManager<input_dtype>::*ptr_RegressionLeafManager_0)
    (

        const fertilized::ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, float> > > &
) const =
      &fertilized::RegressionLeafManager<input_dtype>::operator==;
    bool (*ptr_RegressionLeafManager_1)
    (

        const fertilized::ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, float> > > &
,
     

        const fertilized::ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, float> > > &
) =
    &ne_from_eq<fertilized::ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> >, std::shared_ptr<std::vector<input_dtype> > >, float> > >>;
    py::class_<RegressionLeafManager<input_dtype>,
               std::shared_ptr<RegressionLeafManager<input_dtype>>,
               boost::noncopyable,
               py::bases<ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>> >>
               (("RegressionLeafManager" + type_short).c_str(),
                "Manages the leaf nodes of regression trees.\n\
\n\
This leaf manager creates leaf nodes and stores a probabilistic regression\n\
model at each leaf.\n\
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
- float\n\
- double\n\
\n\
\n\
-----\n\
",
                 py::init<

        const std::shared_ptr<fertilized::IFeatureSelectionProvider> &,
        const size_t &,
        const std::shared_ptr<fertilized::IRegressionCalculator<input_dtype> > &,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > &,
        py::optional<const bool &,
        const int &,
        const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_RegressionLeafManager<input_dtype>))
    .def_pickle(ParameterlessPickleSuite<RegressionLeafManager<input_dtype>>())
#endif
    .def("__eq__", ptr_RegressionLeafManager_0, "-----\n\
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
    .def("__ne__", ptr_RegressionLeafManager_1, "")
    ;

    py::implicitly_convertible<std::shared_ptr<RegressionLeafManager<input_dtype>>,
                               std::shared_ptr<ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>> > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___REGRESSIONLEAFMANAGER_EXPORTER_H_