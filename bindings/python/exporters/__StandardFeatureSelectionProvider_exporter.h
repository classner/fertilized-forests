
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___STANDARDFEATURESELECTIONPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___STANDARDFEATURESELECTIONPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/standardfeatureselectionprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  
  std::shared_ptr<StandardFeatureSelectionProvider> __construct_StandardFeatureSelectionProvider() {
    auto *ptr = (StandardFeatureSelectionProvider*) malloc(sizeof(StandardFeatureSelectionProvider));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<StandardFeatureSelectionProvider>(ptr, free);
  };
#endif
  
  void export_StandardFeatureSelectionProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::StandardFeatureSelectionProvider::*ptr_StandardFeatureSelectionProvider_0)
    (

        const fertilized::IFeatureSelectionProvider &
) const =
      &fertilized::StandardFeatureSelectionProvider::operator==;
    size_t (fertilized::StandardFeatureSelectionProvider::*ptr_StandardFeatureSelectionProvider_1)
    (

) const =
      &fertilized::StandardFeatureSelectionProvider::get_n_available_features;
    bool (*ptr_StandardFeatureSelectionProvider_2)
    (

        const fertilized::IFeatureSelectionProvider &
,
     

        const fertilized::IFeatureSelectionProvider &
) =
    &ne_from_eq<fertilized::IFeatureSelectionProvider>;
    py::class_<StandardFeatureSelectionProvider,
               std::shared_ptr<StandardFeatureSelectionProvider>,
               boost::noncopyable,
               py::bases<IFeatureSelectionProvider >>
               (("StandardFeatureSelectionProvider" + type_short).c_str(),
                "This selection provider generates random selection combinations.\n\
\n\
It may be seeded for reproducible results. It can be configured to only\n\
use a part of the available data dimensions. It only uses then the first\n\
that are registered as used.\n\
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
\n\
-----\n\
",
                 py::init<

        const size_t &,
        const size_t &,
        const size_t &,
        py::optional<size_t,
        const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_StandardFeatureSelectionProvider))
    .def_pickle(ParameterlessPickleSuite<StandardFeatureSelectionProvider>())
#endif
    .def("__eq__", ptr_StandardFeatureSelectionProvider_0, "-----\n\
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
    .def("get_n_available_features", ptr_StandardFeatureSelectionProvider_1, "Get the total number of of available features.\n\
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
    .def("__ne__", ptr_StandardFeatureSelectionProvider_2, "")
    ;

    py::implicitly_convertible<std::shared_ptr<StandardFeatureSelectionProvider>,
                               std::shared_ptr<IFeatureSelectionProvider > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___STANDARDFEATURESELECTIONPROVIDER_EXPORTER_H_