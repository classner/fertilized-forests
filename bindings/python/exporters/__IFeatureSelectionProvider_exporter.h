
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IFEATURESELECTIONPROVIDER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IFEATURESELECTIONPROVIDER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/features/ifeatureselectionprovider.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  
  void export_IFeatureSelectionProvider(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IFeatureSelectionProvider,
               boost::noncopyable>
               (("IFeatureSelectionProvider" + type_short).c_str(),
                "The selection provider generates index combination of data\n\
dimensions.\n\
\n\
During the optimization, :math:`\\phi` may select only a subset of the\n\
provided data dimensions. The selection provider may \"suggest\" many\n\
possible such selections during the optimization process.\n\
\n\
The method register_used must be used after having selected a\n\
proposed selection, so that it can be taken into account for the\n\
generation of future proposals.\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
\n\
\n\
-----\n\
",
                 py::no_init)
#ifdef SERIALIZATION_ENABLED
#endif
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___IFEATURESELECTIONPROVIDER_EXPORTER_H_