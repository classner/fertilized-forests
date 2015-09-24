
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */

#pragma once
#ifndef PYFERTILIZED_EXPORTERS___TREE_EXPORTER_H_
#define PYFERTILIZED_EXPORTERS___TREE_EXPORTER_H_

#include "../global.h"

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include "../util.h"
#include "../serialization.h"

#include <fertilized/tree.h>
namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
#ifdef SERIALIZATION_ENABLED
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  std::shared_ptr<Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>> __construct_Tree() {
    auto *ptr = (Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>*) malloc(sizeof(Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>));
    boost::serialization::access::construct(ptr);
    return std::shared_ptr<Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(ptr, free);
  };
#endif
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Tree_fit_overloads, fit, 2, 3)
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Tree_fit_dprov_overloads, fit_dprov, 1, 2)
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Tree_predict_overloads, predict, 1, 2)
  BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Tree_predict_image_overloads, predict_image, 1, 5)
  template <typename input_dtype,typename feature_dtype,typename annotation_dtype,typename leaf_return_dtype,typename forest_return_dtype>
  void export_Tree(const std::string &type_short) {
    // Explicit function pointers and overloads.
    void (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_0)
    (

        fertilized::dprov_t *,
        const bool &
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::make_node;
    size_t (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_1)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::depth;
    void (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_2)
    (

        const fertilized::Array<const input_dtype, 2, 2> &,
        const fertilized::Array<const annotation_dtype, 2, 2> &,
        const bool &
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::fit;
    void (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_3)
    (

        fertilized::dprov_t *,
        const bool
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::fit_dprov;
    Array<double , 2 , 2> (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_4)
    (

        const fertilized::Array<const input_dtype, 2, 2> &,
        const int &
) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::predict;
    Array<float , 2 , 2> (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_5)
    (

        const fertilized::Array<const input_dtype, 3, 3> &,
        const size_t &,
        const bool &,
        const float &,
        const float &
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::predict_image;
    const bool (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_6)
    (

) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::is_initialized;
    const float (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_7)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_weight;
    const size_t (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_8)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_n_nodes;
    void (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_9)
    (

        const float &
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::set_weight;
    const size_t (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_10)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_input_data_dimensions;
    std::shared_ptr<const typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_11)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_decider;
    Array<double , 1 , 1> (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_12)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::compute_feature_importances;
    std::shared_ptr<const typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::leaf_man_t> (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_13)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_leaf_manager;
    size_t (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_14)
    (

) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::get_samples_stored;
    bool (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_15)
    (

        const fertilized::tree_t &
) const =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::operator==;
    void (fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::*ptr_Tree_16)
    (

        const std::string &
) =
      &fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>::save;
    bool (*ptr_Tree_17)
    (

        const fertilized::tree_t &
,
     

        const fertilized::tree_t &
) =
    &ne_from_eq<fertilized::tree_t>;
    py::class_<Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>,
               std::shared_ptr<Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>,
               boost::noncopyable>
               (("Tree" + type_short).c_str(),
                "The main tree class for the fertilized framework.\n\
\n\
This class is the core element of the framework. It can be used as a\n\
standalone tree or to form a forest. It is highly customizable by\n\
providing the IClassifierManager and ILeafManager.\n\
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
        const std::shared_ptr<typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> &,
        const std::shared_ptr<typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::leaf_man_t> &
                         >())
    // Constructors.
    .def(py::init<

        std::string
                 >())
#ifdef SERIALIZATION_ENABLED
    // Pickle support constructor.
    .def("__init__", py::make_constructor(__construct_Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>))
    .def_pickle(ParameterlessPickleSuite<Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>())
#endif
    .def("make_node", ptr_Tree_0, "Handle the creation of one tree node.\n\
\n\
Takes the next one of the list of marked nodes and fits it to the\n\
data. If necessary, creates two child nodes and a split criterion,\n\
otherwise makes it a leaf.\n\
\n\
The function is always using the frontmost mark in the todo-list.\n\
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
data_provider : shared(IDataProvider)\n\
  The data provider to use.\n\
\n\
append_on_different : bool\n\
  Where to append the produced node-marks in\n\
  the deque \"todo-list\". Appending the nodes on the\n\
  same side they're read from leads to performing a\n\
  DFS, while appending them on the different end\n\
  leads to performing a BFS.")
    .def("depth", ptr_Tree_1, "Get the tree depth.\n\
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
    .def("fit", ptr_Tree_2, Tree_fit_overloads())
    .def("fit_dprov", ptr_Tree_3, Tree_fit_dprov_overloads())
    .def("predict", ptr_Tree_4, Tree_predict_overloads())
    .def("predict_image", ptr_Tree_5, Tree_predict_image_overloads())
    .def("is_initialized", ptr_Tree_6, "Whether the trees fit method has been called and its DFS\n\
and BFS methods can now be used.\n\
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
    .def("get_weight", ptr_Tree_7, "The tree weight.\n\
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
    .def("get_n_nodes", ptr_Tree_8, "The number of tree nodes.\n\
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
    .def("set_weight", ptr_Tree_9, "Sets the tree weight.\n\
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
    .def("get_input_data_dimensions", ptr_Tree_10, "The data dimension that is required by this tree.\n\
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
    .def("get_decider", ptr_Tree_11, "The classifier manager used by this tree.\n\
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
    .def("compute_feature_importances", ptr_Tree_12, "Computes a feature importance vector.\n\
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
    .def("get_leaf_manager", ptr_Tree_13, "The leaf manager used by this tree.\n\
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
    .def("get_samples_stored", ptr_Tree_14, "The number of samples stored in leafs.\n\
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
    .def("__eq__", ptr_Tree_15, "\n\
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
    .def("save", ptr_Tree_16, "Saves the tree to a textfile.\n\
\n\
This method can be used platform and system independent (e.g. Matlab -\n\
C++).\n\
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
  The filename of the file to store the tree in.")
    .def("__ne__", ptr_Tree_17, "")
    ;

  };
}  // namespace fertilized

#endif  // PYFERTILIZED_EXPORTERS___TREE_EXPORTER_H_