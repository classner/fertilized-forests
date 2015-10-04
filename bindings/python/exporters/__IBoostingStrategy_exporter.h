
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___IBOOSTINGSTRATEGY_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___IBOOSTINGSTRATEGY_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/boosting/iboostingstrategy.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_IBoostingStrategy(const std::string &type_short) {
    // Explicit function pointers and overloads.
    py::class_<IBoostingStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               boost::noncopyable>
               (("IBoostingStrategy" + type_short).c_str(),
                "Specifies the boosting algorithm that will be used for training\n\
\n\
Use the IBoostingStrategy in combination with a BoostingLeafManager\n\
to allow it to set a custom weight function per tree which may lead to\n\
better classification results.\n\
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
                 py::no_init)
#ifdef SERIALIZATION_ENABLED
#endif
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___IBOOSTINGSTRATEGY_EXPORTER_H_