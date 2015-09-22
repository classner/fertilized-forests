
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___FEATCALCPARAMSET_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___FEATCALCPARAMSET_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/featcalcparamset.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  
  std::shared_ptr<FeatCalcParamSet> __construct_FeatCalcParamSet() {
    auto *ptr = (FeatCalcParamSet*) malloc(sizeof(FeatCalcParamSet));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<FeatCalcParamSet>(ptr, free);
  };
#endif
  
  void export_FeatCalcParamSet(const std::string &type_short) {
    // Explicit function pointers and overloads.
    bool (*ptr_FeatCalcParamSet_0)
    (

        const fertilized::FeatCalcParamSet &
,
     

        const fertilized::FeatCalcParamSet &
) =
    &ne_from_eq<fertilized::FeatCalcParamSet>;
    py::class_<FeatCalcParamSet,
               std::shared_ptr<FeatCalcParamSet>,
               boost::noncopyable>
               (("FeatCalcParamSet" + type_short).c_str(),
                "Can be specialized to any necessary parameters used by a feature\n\
calculator.\n\
\n\
This was planned as an implementable interface, however it must be a\n\
single, plain POD object, since it might be transferred forth and back\n\
between host and MIC device.\n\
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
                 py::no_init)
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_FeatCalcParamSet))
    .def_pickle(ParameterlessPickleSuite<FeatCalcParamSet>())
#endif
    .def("__ne__", ptr_FeatCalcParamSet_0, "")
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___FEATCALCPARAMSET_EXPORTER_H_