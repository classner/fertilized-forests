
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___ILEAFMANAGER_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___ILEAFMANAGER_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/leafs/ileafmanager.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_ILeafManager(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<ILeafManager<input_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               boost::noncopyable>
               (("ILeafManager" + type_short).c_str(),
                "Stores and returns leaf values, and combines them to forest\n\
results.\n\
\n\
\n\
-----\n\
\n\
Available in:\n\
\n\
- C++\n\
- Python\n\
\n\
Instantiations:\n\
\n\
- int; uint; std::vector<float>; std::vector<float>\n\
- float; uint; std::vector<float>; std::vector<float>\n\
- double; uint; std::vector<float>; std::vector<float>\n\
- uint8_t; uint; std::vector<float>; std::vector<float>\n\
- uint8_t; int16_t; std::vector<float>; std::vector<float>\n\
- uint8_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>\n\
- float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>\n\
- double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>\n\
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

#endif  // PYFERTILIZED_EXPORTERS___ILEAFMANAGER_EXPORTER_H_