
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___VOLUMEFEATURESELECTIONPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___VOLUMEFEATURESELECTIONPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/volumefeatureselectionprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  
  std::shared_ptr<VolumeFeatureSelectionProvider> __construct_VolumeFeatureSelectionProvider() {
    auto *ptr = (VolumeFeatureSelectionProvider*) malloc(sizeof(VolumeFeatureSelectionProvider));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<VolumeFeatureSelectionProvider>(ptr, free);
  };
#endif
  
  void export_VolumeFeatureSelectionProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (fertilized::VolumeFeatureSelectionProvider::*ptr_VolumeFeatureSelectionProvider_0)
    (

        const fertilized::IFeatureSelectionProvider &
) const =
      &fertilized::VolumeFeatureSelectionProvider::operator==;
    size_t (fertilized::VolumeFeatureSelectionProvider::*ptr_VolumeFeatureSelectionProvider_1)
    (

) const =
      &fertilized::VolumeFeatureSelectionProvider::get_size_x;
    size_t (fertilized::VolumeFeatureSelectionProvider::*ptr_VolumeFeatureSelectionProvider_2)
    (

) const =
      &fertilized::VolumeFeatureSelectionProvider::get_size_y;
    size_t (fertilized::VolumeFeatureSelectionProvider::*ptr_VolumeFeatureSelectionProvider_3)
    (

) const =
      &fertilized::VolumeFeatureSelectionProvider::get_size_z;
    size_t (fertilized::VolumeFeatureSelectionProvider::*ptr_VolumeFeatureSelectionProvider_4)
    (

) const =
      &fertilized::VolumeFeatureSelectionProvider::get_n_available_features;
    bool (*ptr_VolumeFeatureSelectionProvider_5)
    (

        const fertilized::IFeatureSelectionProvider &
,
     

        const fertilized::IFeatureSelectionProvider &
) =
    &ne_from_eq<fertilized::IFeatureSelectionProvider>;
    py::class_<VolumeFeatureSelectionProvider,
               std::shared_ptr<VolumeFeatureSelectionProvider>,
               boost::noncopyable,
               py::bases<IFeatureSelectionProvider >>
               (("VolumeFeatureSelectionProvider" + type_short).c_str(),
                "This selection provider generates random selection combinations\n\
from a 3D feature volume.\n\
\n\
It may be seeded for reproducible results.\n\
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
        const size_t &,
        const size_t &,
        py::optional<const unsigned int &>
                         >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_VolumeFeatureSelectionProvider))
    .def_pickle(ParameterlessPickleSuite<VolumeFeatureSelectionProvider>())
#endif
    .def("__eq__", ptr_VolumeFeatureSelectionProvider_0, "-----\n\
\n\
Available in:\n\
\n\
- C+_\n\
- Python\n\
- Matlab\n\
\n\
\n\
-----\n\
")
    .def("get_size_x", ptr_VolumeFeatureSelectionProvider_1, "Get the horizontal patch size.\n\
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
    .def("get_size_y", ptr_VolumeFeatureSelectionProvider_2, "Get the vertical patch size.\n\
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
    .def("get_size_z", ptr_VolumeFeatureSelectionProvider_3, "Get the patch depth.\n\
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
    .def("get_n_available_features", ptr_VolumeFeatureSelectionProvider_4, "Get the total number of of available features.\n\
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
    .def("__ne__", ptr_VolumeFeatureSelectionProvider_5, "")
    ;

    py::implicitly_convertible<std::shared_ptr<VolumeFeatureSelectionProvider>,
                               std::shared_ptr<IFeatureSelectionProvider > >();
  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___VOLUMEFEATURESELECTIONPROVIDER_EXPORTER_H_