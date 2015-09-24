
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___FOREST_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___FOREST_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/forest.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  std::shared_ptr<Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>> __construct_Forest() {
    auto *ptr = (Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>*) malloc(sizeof(Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(ptr, free);
  };
#endif
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Forest_fit_overloads, fit, 2, 3)
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Forest_predict_overloads, predict, 1, 2)
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Forest_predict_image_overloads, predict_image, 1, 5)
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_Forest(const std::string &type_short) {
    // Explicit function pointers and overloads.
    void (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_0)
    (

        const fertilized::Array<const input_dtype, 2, 2> &,
        const fertilized::Array<const annotation_dtype, 2, 2> &,
        unsigned int
) =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::fit;
    Array<size_t , 1 , 1> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_1)
    (

) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::depths;
    void (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_2)
    (

        const std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::fdprov_t> &,
        typename fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::exec_strat_t *
) =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::fit_dprov;
    Array<double , 2 , 2> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_3)
    (

        const fertilized::Array<const input_dtype, 2, 2> &,
        const int &
) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::predict;
    Array<float , 2 , 2> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_4)
    (

        const fertilized::Array<const input_dtype, 3, 3> &,
        const size_t &,
        const bool &,
        const float &,
        const float &
) =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::predict_image;
    size_t (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_5)
    (

) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_input_data_dimensions;
    std::shared_ptr<const typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_6)
    (

) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_decider;
    Array<double , 1 , 1> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_7)
    (

) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::compute_feature_importances;
    std::vector<float> (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_8)
    (

) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_tree_weights;
    bool (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_9)
    (

        const fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) const =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::operator==;
    void (fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Forest_10)
    (

        const std::string &
) =
      &fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::save;
    bool (*ptr_Forest_11)
    (

        const fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
,
     

        const fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> &
) =
    &ne_from_eq<fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>>;
    py::class_<Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable>
               (("Forest" + type_short).c_str(),
                "Standard forest class of the library.\n\
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
- uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>\n\
- float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>\n\
- double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>\n\
\n\
\n\
-----\n\
",
                 py::init<

        const unsigned int &,
        const unsigned int &,
        const unsigned int &,
        const unsigned int &,
        const std::vector<std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> > &,
        const std::vector<std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::leaf_man_t> > &,
        const std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::training_t> &
                         >())
    // Constructors.
    .def(py::init<

        const std::vector<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::tree_ptr_t> &,
        const std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::training_t> &
                 >())
    .def(py::init<

        const std::vector<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::tree_ptr_t> &
                 >())
    .def(py::init<

        std::string
                 >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>))
    .def_pickle(ParameterlessPickleSuite<Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    .def("fit", ptr_Forest_0, Forest_fit_overloads())
    .def("depths", ptr_Forest_1, "Gets the depths of all trees.\n\
\n\
The depth is defined to be 0 for an \"empty\" tree (only a leaf/root node)\n\
and as the amount of edges on the longest path in the tree otherwise.\n\
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
    .def("fit_dprov", ptr_Forest_2, "The fitting function for a forest.\n\
\n\
Fits this forest to the data given by the data provider.\n\
Releases the GIL in Python!\n\
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
\n\
\n\
Parameters\n\
==========\n\
\n\
data_provider : shared(IForestDataProvider)\n\
  The data provider for the fitting process.\n\
\n\
execution_strategy : IExecutionStrategy*\n\
  The execution strategy to use.")
    .def("predict", ptr_Forest_3, Forest_predict_overloads())
    .def("predict_image", ptr_Forest_4, Forest_predict_image_overloads())
    .def("get_input_data_dimensions", ptr_Forest_5, "Gets the required input data dimenstion.\n\
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
    .def("get_decider", ptr_Forest_6, "Gets the decider of the first tree.\n\
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
")
    .def("compute_feature_importances", ptr_Forest_7, "Computes a feature importance vector.\n\
\n\
The vector is normalized to sum to 1.0. It contains the relative\n\
frequencies of the feature occurences. Its length is the number\n\
of available features.\n\
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
    .def("get_tree_weights", ptr_Forest_8, "Gets all tree weights.\n\
\n\
The returned list is a copy of the actual weights! Changes to it are not\n\
affecting the forest object!\n\
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
    .def("__eq__", ptr_Forest_9, "-----\n\
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
    .def("save", ptr_Forest_10, "Saves the forest to a file with the specified name.\n\
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
\n\
\n\
Parameters\n\
==========\n\
\n\
filename : string\n\
  The filename to use.")
    .def("__ne__", ptr_Forest_11, "")
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___FOREST_EXPORTER_H_