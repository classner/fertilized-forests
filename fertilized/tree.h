/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_TREE_H_
#define FERTILIZED_TREE_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <tuple>
#include <vector>
#include <deque>
#include <memory>
#include <utility>
#include <string>
#include <fstream>

#include "./global.h"
#include "./types.h"
#include "./util/gil.hpp"
#include "./leafs/ileafmanager.h"
#include "./data_providers/unchangeddataprovider.h"
#include "./data_providers/patchtoimagecoordinatetransformer.h"
#include "./features/isurfacecalculator.h"
#include "./features/volumefeatureselectionprovider.h"
#include "./deciders/idecider.h"
#include "./deciders/thresholddecider.h"
#include "./serialization/serialization.h"
#include "./ndarray.h"

namespace fertilized {
  /**
   * \brief The main tree class for the fertilized framework.
   *
   * This class is the core element of the framework. It can be used as a
   * standalone tree or to form a forest. It is highly customizable by
   * providing the IClassifierManager and ILeafManager.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int; int; uint; std::vector<float>; std::vector<float>
   * - float; float; uint; std::vector<float>; std::vector<float>
   * - double; double; uint; std::vector<float>; std::vector<float>
   * - uint8_t; uint8_t; uint; std::vector<float>; std::vector<float>
   * - uint8_t; int16_t; uint; std::vector<float>; std::vector<float>
   * - uint8_t; int16_t; int16_t; std::vector<float>; std::vector<float>
   * - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
   * - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
   * - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Tree {
   public:
    // Convenience typedefs for the managers.
    typedef IDecider<input_dtype, feature_dtype,
                     annotation_dtype> dec_t;
    typedef ILeafManager<input_dtype, annotation_dtype,
                         leaf_return_dtype, forest_return_dtype> leaf_man_t;
    typedef typename leaf_man_t::dprov_t dprov_t;
    typedef typename leaf_man_t::wlresult_list_t wlresult_list_t;
    typedef Tree<input_dtype, feature_dtype, annotation_dtype,
                 leaf_return_dtype, forest_return_dtype> tree_t;

    /**
     * \brief The standard constructor for the fertilized trees.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param max_depth uint > 0
     *     The maximum tree depth, including leafs (up to including).
     * \param min_samples_at_leaf uint > 0
     *     The minimum number of samples at a leaf (from including).
     * \param min_samples_at_node uint>=2*min_samples_at_leaf
     *     The minimum number of samples at a node (from including).
     * \param decider \ref IDecider
     *     The decider that stores, optimizes and applies the decision rules
     *     for each inner tree node.
     * \param leaf_manager The leaf manager generates, stores and handles
     *                  the return values of the leaf nodes.
     */
    Tree(const uint &max_depth,
         const uint &min_samples_at_leaf,
         const uint &min_samples_at_node,
         const std::shared_ptr<dec_t> &decider,
         const std::shared_ptr<leaf_man_t> &leaf_manager)
      : max_depth(max_depth),
        is_initialized_for_training(false),
        min_samples_at_node(min_samples_at_node),
        min_samples_at_leaf(min_samples_at_leaf),
        weight(1.0f),
        stored_in_leafs(0),
        decider(decider),
        leaf_manager(leaf_manager),
        tree(0),
        marks(0) {
      if (max_depth == 0) {
        throw Fertilized_Exception("The max depth must be >0!");
      }
      if (min_samples_at_leaf == 0) {
        throw Fertilized_Exception("The minimum number of samples at leafs "
          "must be >0!");
      }
      if (min_samples_at_node < 2 * min_samples_at_leaf) {
        throw Fertilized_Exception("The minimum number of samples at a node "
          "must be >= 2*min_samples_at_leaf!");
      }
      // No need to initialize the marks, they're empty.
      // Initialize the root node.
      tree.push_back(node_id_pair_t(0, 0));
      if (min_samples_at_leaf < 1) {
        throw Fertilized_Exception("min_samples_at_leaf must be greater 0!");
      }
      if (min_samples_at_node < 2 * min_samples_at_leaf) {
        throw Fertilized_Exception("min_samples_at_node must be greater or "
          "equal to 2 * min_samples_at_leaf!");
      }
    };

    /**
     * \brief Deserialization constructor for the fertilized trees.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * Exported name: TreeFromFile
     *
     * -----
     *
     * \param filename string
     *   The filename to deserialize the tree from.
     */
    Tree(std::string filename)  {
      std::ifstream fstream(filename);
      std::stringstream sstream;
      if (fstream) {
        sstream << fstream.rdbuf();
        fstream.close();
        deserialize(sstream, this);
      } else {
        throw Fertilized_Exception("Could not load tree from file: " +
          filename);
      }
    };

    /**
     * \brief Handle the creation of one tree node.
     *
     * Takes the next one of the list of marked nodes and fits it to the
     * data. If necessary, creates two child nodes and a split criterion,
     * otherwise makes it a leaf.
     *
     * The function is always using the frontmost mark in the todo-list.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param data_provider shared(IDataProvider)
     *   The data provider to use.
     * \param append_on_different bool
     *   Where to append the produced node-marks in
     *   the deque "todo-list". Appending the nodes on the
     *   same side they're read from leads to performing a
     *   DFS, while appending them on the different end
     *   leads to performing a BFS.
     */
    void make_node(dprov_t *data_provider,
                   const bool &append_on_different) {
      // Assert that there is a node left to process.
      if (marks.empty()) {
        throw Fertilized_Exception("Tried to process a node where none was "
          "left.");
      }
      // Get the data to work with.
      std::shared_ptr<elem_id_vec_t> element_id_list;
      unsigned int node_depth;
      node_id_t node_id;
      std::tie(element_id_list, node_id, node_depth) = marks.front();
      marks.pop_front();
      // Assert that there are sufficiently many elements there.
      FASSERT(element_id_list -> size() >= this -> min_samples_at_leaf);
      FASSERT(node_depth <= max_depth);
      // Give the dataprovider the opportunity to adjust the dataset.
      auto node_predictor_func = [this](const input_dtype *dta,
                                                    const size_t &step,
                                                    const node_id_t start_node,
                                                    const std::function<void(void*)> &tf) {
                                    return this -> predict_leaf(dta, step, start_node, tf);
                                 };
      data_provider -> optimize_set_for_node(node_id,
                                             node_depth,
                                             node_predictor_func,
                                             element_id_list);
      FASSERT(element_id_list -> size() >= this -> min_samples_at_leaf);
      // Check min_samples_at_node and max_tree_depth.
      if (element_id_list -> size() < min_samples_at_node ||
          node_depth >= max_depth) {
        data_provider -> load_samples_for_leaf(node_id,
                                               node_predictor_func,
                                               element_id_list.get());
        leaf_manager -> make_leaf(node_id, *element_id_list, *data_provider);
        stored_in_leafs += element_id_list -> size();
        return;
      }
      // Construct a classifier using them.
      bool make_to_leaf;
      std::shared_ptr<elem_id_vec_t> list_left, list_right;
      decider -> optimize_and_set_for_node(node_id, node_depth,
        min_samples_at_leaf,
        *element_id_list, *data_provider,
        &make_to_leaf, &list_left, &list_right);
      // If the classifier manager couldn't find a sufficiently good split.
      if (make_to_leaf) {
        data_provider -> load_samples_for_leaf(node_id,
                                               node_predictor_func,
                                               element_id_list.get());
        leaf_manager -> make_leaf(node_id, *element_id_list, *data_provider);
        stored_in_leafs += element_id_list -> size();
      } else {
        FASSERT(list_left -> size() >= this -> min_samples_at_leaf);
        FASSERT(list_right -> size() >= this -> min_samples_at_leaf);
        // Left child.
        node_id_t left_id = tree.size();
        tree.push_back(node_id_pair_t(0, 0));
        tree[node_id].first = left_id;
        if (append_on_different)
          marks.push_back(
            node_todo_tuple_t(list_left, left_id, node_depth + 1));
        else
          marks.push_front(
            node_todo_tuple_t(list_left, left_id, node_depth + 1));
        // Right child.
        node_id_t right_id = tree.size();
        tree.push_back(node_id_pair_t(0, 0));
        tree[node_id].second = right_id;
        if (append_on_different)
          marks.push_back(
            node_todo_tuple_t(list_right, right_id, node_depth + 1));
        else
          marks.push_front(
            node_todo_tuple_t(list_right, right_id, node_depth + 1));
        data_provider -> track_child_nodes(node_id, left_id, right_id);
      }
    };

    /**
     * \brief Do one DFS step with given completion level.
     *
     * For \ref CompletionLevel::Level, the branch of the tree below the
     * currently marked node is completed.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     *
     * \param data_provider shared(IDataProvider)
     *   The data provider to use to get the samples with
     *   the relevant ids.
     * \param completion CompletionLevel
     *   The \ref CompletionLevel to reach before returning
     *   from the function.
     */
    size_t DFS(dprov_t *data_provider,
             const CompletionLevel &completion) {
      auto start_size = marks.size();
      if (start_size <= 0) {
        throw Fertilized_Exception("Called DFS on an empty marker set. Did "
          "you initialize the training by calling the tree's fit method?");
      }
      switch (completion) {
      case CompletionLevel::Complete:
        while (!marks.empty())
          make_node(data_provider, false);
        break;
      case CompletionLevel::Level:
        while (marks.size() > start_size - 1)
          make_node(data_provider, false);
        break;
      case CompletionLevel::Node:
        make_node(data_provider, false);
        break;
      default:
        throw Fertilized_Exception("Unknown completion level used for DFS.");
      }
      return marks.size();
    };

    /**
     * \brief Do one BFS step with given completion level.
     *
     * For \ref CompletionLevel::Level, all nodes with the same depth than the
     * currently processed one are completed. It is assumed that the current
     * deque state originates from a BFS search, i.e. all node marks on the
     * same level are next to each other in the todo-deque.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     *
     * \param data_provider shared(IDataProvider)
     *   The data provider to use to get the samples with
     *   the relevant ids.
     * \param completion CompletionLevel
     *   The \ref CompletionLevel to reach before returning
     *   from the function.
     */
    size_t BFS(dprov_t *data_provider,
               const CompletionLevel &completion) {
      auto start_size = marks.size();
      if (start_size <= 0) {
        throw Fertilized_Exception("Called BFS on an empty marker set. Did "
          "you initialize the training by calling the tree's fit method?");
      }
      switch (completion) {
      case CompletionLevel::Complete:
        while (!marks.empty())
          make_node(data_provider, true);
        break;
      case CompletionLevel::Level:
        {
        unsigned int depth = std::get<2>(marks.front());
        while (!marks.empty() &&
               std::get<2>(marks.front()) == depth)
          make_node(data_provider, true);
        }
        break;
      case CompletionLevel::Node:
        make_node(data_provider, true);
        break;
      default:
        throw Fertilized_Exception("Unknown completion level used for BFS.");
      }
      return marks.size();
    };

    /**
     * Get the tree depth.
     *
     * The depth is defined to be 0 for an "empty" tree (only a leaf/root node)
     * and as the amount of edges on the longest path in the tree otherwise.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    size_t depth() const {
      size_t depth = 0;
      if (! tree.empty()) {
        std::vector<std::pair<size_t, size_t>> to_check;
        to_check.push_back(std::make_pair(0, 0));
        while(! to_check.empty()) {
          const std::pair<size_t, size_t> to_process = to_check.back();
          to_check.pop_back();
          const size_t &node_id = to_process.first;
          const size_t &current_depth = to_process.second;
          if (current_depth > depth)
            depth = current_depth;
          FASSERT (node_id < tree.size());
          const auto &child_nodes = tree[node_id];
          if (child_nodes.first == 0) {
            if (child_nodes.second == 0) {
              // Leaf.
              continue;
            } else {
              to_check.push_back(std::make_pair(child_nodes.second,
                                                current_depth+1));
            }
          } else {
            to_check.push_back(std::make_pair(child_nodes.first,
                                              current_depth+1));
            if (child_nodes.second != 0) {
              to_check.push_back(std::make_pair(child_nodes.second,
                                                current_depth+1));
            }
          }
        }
      }
      return depth;
    }

    /**
     * \brief Standard fitting function.
     *
     * Fits this tree to the data given by the data provider. If
     * complete_dfs is true, the tree is completely fitted to the data
     * Otherwise, just a node todo for the root node is added and the tree
     * may be performed step-by-step by calling the \ref BFS or \ref DFS
     * functions.
     *
     * Releases the GIL in Python!
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param data Array<input_dtype>, 2D, row-major contiguous
     *   Row-wise data points.
     * \param annotations Array<annotation_dtype>, 2D, row-major contiguous
     *   Row-wise annotations.
     * \param complete_dfs bool
     *   If set to true, finishes training the tree. Otherwise, the training
     *   is just set up, and \ref make_node must be called. Default: true.
     */
    void fit(const Array<const input_dtype, 2, 2> &data,
             const Array<const annotation_dtype, 2, 2> &annotations,
             const bool &complete_dfs = true) {
#ifdef PYTHON_ENABLED
      py::gil_guard_release guard;
#endif
      auto data_provider = std::make_shared<UnchangedDataProvider<input_dtype,
                                                                  annotation_dtype>>(data, annotations);
      fit_dprov(data_provider.get(), complete_dfs);
    }

    /**
     * \brief The fitting function for a single tree.
     *
     * Fits this tree to the data given by the data provider. If
     * complete_dfs is true, the tree is completely fitted to the data
     * Otherwise, just a node todo for the root node is added and the tree
     * may be performed step-by-step by calling the \ref BFS or \ref DFS
     * functions.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param data_provider shared(IDataProvider)
     *   The data provider for the fitting process.
     * \param complete_dfs bool
     *   If true, complete the fitting process.
     */
    void fit_dprov(dprov_t *data_provider,
                   const bool complete_dfs = true) {
      // Compatibility-check for leaf manager - data provider.
      if (!leaf_manager -> IsCompatibleWith(*data_provider)) {
        throw Fertilized_Exception("Leaf manager incompatible with selected"
                                   "data provider!");
      }
      if (data_provider -> get_feat_vec_dim() !=
          this -> get_input_data_dimensions()) {
        throw Fertilized_Exception("This data provider has the wrong number "
          "of data features!");
      }
      // Get the initial sample set for the root node.
      auto init_samples = data_provider -> get_initial_sample_list();
      auto samples = std::make_shared<elem_id_vec_t>(init_samples -> begin(),
                                                     init_samples -> end());
      if (samples -> size() <= 1) {
        throw Fertilized_Exception("More than one example must arrive at the "
          "tree root node.");
      }
      marks.push_back(node_todo_tuple_t(samples, 0, 0));
      is_initialized_for_training = true;

      // Directly complete the DFS fitting for this tree if necessary.
      if (complete_dfs) DFS(data_provider, CompletionLevel::Complete);
    };

    /**
     * \brief Get the leaf id of the leaf where the given data will arrive.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     *
     * \param data The data to propagate through the tree.
     * \param data_step A step size in memory from one data element to the
     *             next.
     * \return The node id of the leaf.
     */
    node_id_t predict_leaf(const input_dtype *data,
                           const size_t &data_step,
                           const node_id_t &start_node = 0,
                           const std::function<void(void*)> &dptf = nullptr)
     const {
      node_id_t current_node_id = start_node;
      while (true) {
        if (tree[ current_node_id ].first == 0 &&
            tree[ current_node_id ].second == 0) {
          return current_node_id;
        } else {
          bool decision = decider ->
            decide(current_node_id, data, data_step, dptf);
          current_node_id = (decision ?  tree[ current_node_id ].first :
                                         tree[ current_node_id ].second);
        }
      }
    };

    /**
     * Predicts new data points.
     *
     * Releases the GIL in Python!
     *
     * -----
     * Available in:
     * - C++
     * - Python  
     * - Matlab
     * .
     *
     * -----
     *
     * \param data Array<input_data>, 2D, row-major contiguous
     *   The data predict with one sample per row.
     *
     * \param num_threads int>0
     *   The number of threads to use for prediction. The number of
     *   samples should be at least three times larger than the number
     *   of threads to observe very good parallelization behaviour.
     */
    Array<double, 2, 2> predict(const Array<const input_dtype, 2, 2> &data,
                                const int &num_threads=1)
      const {
      // Check the shape of the incoming array.
      if (data.TPLMETH getSize<1>() != decider -> get_required_num_data_dim()){
         throw Fertilized_Exception("Wrong array shape! Expecting " +
           std::to_string(decider -> get_required_num_data_dim()) + " columns, "
           "got " + std::to_string(data.TPLMETH getSize<1>()) + "!");
      }
      if (num_threads == 0) {
         throw Fertilized_Exception("The number of threads must be >0!");
      }
      Array<double, 2, 2> result_array = allocate(data.TPLMETH getSize<0>(),
                                                  leaf_manager ->
                                                    get_summary_dimensions(1));
      {
#ifdef PYTHON_ENABLED
        py::gil_guard_release guard;
#endif
    const input_dtype *base_ptr = &data[0][0];
    const size_t line_length = data.TPLMETH getSize<1>();
        // Extract the lines serially, since the Array class is not thread-safe (yet)
        std::vector<Array<double, 2, 2>::Reference> lines;
        for (int i = 0; i < data.TPLMETH getSize<0>(); ++i) {
          lines.push_back(result_array[i]);
        }
        #pragma omp parallel for num_threads(num_threads) if (num_threads != 1) \
          default(none) /* Require explicit spec. */\
          shared(data, result_array, base_ptr, lines) \
          schedule(static)
        for (int i = 0; i < data.TPLMETH getSize<0>(); ++i) {
          leaf_manager -> summarize_tree_result(predict_leaf_result(base_ptr + i * line_length),
                                                lines[i]);
        }
      }
      return result_array;
    }

    /**
     * Predicts an entire image.
     *
     * This method will iterate pixel per pixel over the image and tries to
     * predict it. This method is only supported for certain setups:
     * 
     * - Leaf Manager: \ref ClassificationLeafManager or \ref HoughLeafManager.
     * - Decider: \ref ThresholdDecider.
     * - Feature Selection Provider: \ref VolumeFeatureSelectionProvider.
     *
     * Releases the GIL in Python!
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param image Array<input_dtype>, 3D, row-major-contiguous
     *   The feature image to predict.
     * \param step_size size_t>0
     *   Step size in pixels between predictions (horizontal and vertical). Default: 1.
     * \param reduce_to_patch_positions bool
     *   A reduced result image grid is used, matching exactly the required size.
     *   This has implications for the use with the HoughLeafManager, because
     *   the offset vectors must also be added on the reduced grid.
     * \param p1 float>0.f
     *   The ratio of x to y axis for the HoughLeafManager.
     * \param p2 float>=0.f
     *   The minimum probability to add a vector for the HoughLeafManager.
     */
    Array<float, 2, 2> predict_image(const Array<const input_dtype, 3, 3> &image,
                                     const size_t &step_size = 1,
                                     const bool &reduce_to_patch_positions = false,
                                     const float &p1 = 1.f,
                                     const float &p2 = 0.f) {
      if (step_size == 0) {
        throw Fertilized_Exception("The step size must be >0!");
      }
      if (p1 <= 0.f) {
        throw Fertilized_Exception("The axis-ratio must be >0.f!");
      }
      if (p2 < 0.f) {
        throw Fertilized_Exception("The probability threshold must be >=0.f!");
      }
      // Currently this method is only supported for a threshold decider
      // and a VolumeFeatureSelectionProvider.
      typedef const ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>* ctcptr;
      ctcptr thresh_dec = dynamic_cast<ctcptr>(decider.get());
      if (! thresh_dec) {
        throw Fertilized_Exception("Image prediction is currently only "
          "supported for trees and forests using threshold deciders and "
          "VolumeFeatureSelectionProviders.");
      }
      const auto *selection_provider = dynamic_cast<
        const VolumeFeatureSelectionProvider*>(
          thresh_dec -> get_selection_provider().get());
      if (! selection_provider) {
        throw Fertilized_Exception("Image prediction is currently only "
          "supported for trees and forests using threshold deciders and "
          "VolumeFeatureSelectionProviders.");
      }
      std::size_t patch_x = selection_provider -> get_size_x();
      std::size_t patch_y = selection_provider -> get_size_y();
      std::size_t patch_z = selection_provider -> get_size_z();
      if (image.TPLMETH getSize<0>() != patch_z) {
        throw Fertilized_Exception("Incorrect feature image depth "
          "(must be " + std::to_string(patch_z) + ", is " +
          std::to_string(image.TPLMETH getSize<0>()));
      }
      if (image.TPLMETH getSize<1>() < patch_y) {
        throw Fertilized_Exception("Incorrect feature image height "
          "(must be >=" + std::to_string(patch_y) + ", is " +
          std::to_string(image.TPLMETH getSize<1>()) + ")");
      }
      if (image.TPLMETH getSize<2>() < patch_x) {
        throw Fertilized_Exception("Incorrect feature image width "
          "(must be >=" + std::to_string(patch_x) + ", is " +
          std::to_string(image.TPLMETH getSize<2>()) + ")");
      }
      // Prepare the result array.
      std::size_t resheight = image.TPLMETH getSize<1>();
      std::size_t reswidth = image.TPLMETH getSize<2>();
      if (reduce_to_patch_positions) {
        resheight = (image.TPLMETH getSize<1>() - patch_y) / step_size + 1;
        reswidth = (image.TPLMETH getSize<2>() - patch_x) / step_size + 1;
      }
      Array<float, 2, 2> result = allocate(resheight, reswidth);
      result.deep() = 0.f;
      float correction_ratio = (reduce_to_patch_positions ?
                                  1.f / static_cast<float>(step_size) :
                                  1.f);
      float ratio_parameters[] = {p1, p2, correction_ratio, correction_ratio};
      {
#ifdef PYTHON_ENABLED
        py::gil_guard_release guard;
#endif
        size_t write_x, write_y;
        const input_dtype *data_ptr = image.getData();
        auto transformer = PatchToImageCoordinateTransformer(patch_x,
                                                             patch_y,
                                                             patch_z,
                                                             image.TPLMETH getSize<1>(),
                                                             image.TPLMETH getSize<2>(),
                                                             true);
        for (size_t left_y = 0; left_y <= image.TPLMETH getSize<1>() - patch_y; left_y += step_size) {
          for (size_t left_x = 0; left_x <= image.TPLMETH getSize<2>() - patch_x; left_x += step_size) {
            transformer.posx = left_x;
            transformer.posy = left_y;
            // Add the prediction values.
            if (reduce_to_patch_positions) {
              write_y = left_y / step_size;
              write_x = left_x / step_size;
            } else {
              write_y = left_y + patch_y / 2;
              write_x = left_x + patch_x / 2;
            }
            leaf_manager -> add_tree_prediction_to_image(
              predict_leaf_result(data_ptr, 1, 0, transformer),
              result,
              write_x,
              write_y,
              ratio_parameters);
          }
        }
      }  // gil_guard_release
      return result;
    }

    /**
     * \brief Get the data prediction result for the given data.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     *
     * \param data The data to propagate through the tree.
     * \param data_step A step size in memory from one data element to the
     *             next.
     * \return The prediction result from the leaf.
     */
    leaf_return_dtype predict_leaf_result(const input_dtype *data,
                                          const size_t &data_step = 1,
                                          const node_id_t &start_node = 0,
                                          const std::function<void(void*)> &dptf = nullptr)
     const {
      return leaf_manager -> get_result(predict_leaf(data,
                                                     data_step,
                                                     start_node,
                                                     dptf),
                                        data,
                                        data_step,
                                        dptf);
    };

    /**
     * Combine the leaf results of several trees to the forest result.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     */
    forest_return_dtype combine_leaf_results(
      const wlresult_list_t &res_pair_list) const {
      return leaf_manager -> get_combined_result(res_pair_list);
    }

    /**
     * \brief Whether the trees \ref fit method has been called and its DFS
     * and BFS methods can now be used.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * .
     *
     * -----
     */
    const bool is_initialized() { return is_initialized_for_training; }

    /**
     * \brief The tree weight.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    const float get_weight() const { return weight; }

    /**
     * \brief The number of tree nodes.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    const size_t get_n_nodes() const { return tree.size(); }

    /**
     * \brief Sets the tree weight.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    void set_weight(const float &new_weight) { weight = new_weight; }

    /**
     * \brief The data dimension that is required by this tree.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    const size_t get_input_data_dimensions() const {
      return decider -> get_required_num_data_dim();
    };

    /**
     * \brief The classifier manager used by this tree.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * .
     *
     * -----
     */
    std::shared_ptr<const dec_t> get_decider() const {
      return decider;
    };
    
    /**
     * \brief Computes a feature importance vector.
     * 
     * The vector is normalized to sum to 1.0. It contains the relative
     * frequencies of the feature occurences. Its length is the number
     * of available features.
     * 
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * 
     * -----
     */
    Array<double, 1, 1> compute_feature_importances() const {
        if (this -> tree.size() == 1) {
            throw Fertilized_Exception(
              "It is impossible to compute feature importances from this "
              "tree, since no decision nodes have been created. Either run "
              "the tree training to create some, or use forest -> "
              "compute_feature_importances() to have the importances computed "
              "from other, more successful trees.");
        }
        return decider -> compute_feature_importances();
    }

    /**
     * \brief The leaf manager used by this tree.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * .
     *
     * -----
     */
    std::shared_ptr<const leaf_man_t> get_leaf_manager() const {
      return leaf_manager;
    }

    /**
     * \brief The number of samples stored in leafs.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    size_t get_samples_stored() const {
      return stored_in_leafs;
    }

    /**
     * Get the vector of marked nodes.
     */
    std::deque<node_todo_tuple_t> get_marks() const {
      return marks;
    }

    /**
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    bool operator==(tree_t const &rhs) const {
      bool eq_depth = max_depth == rhs.max_depth;
      bool eq_init = is_initialized_for_training == rhs.is_initialized_for_training;
      bool eq_min_samples = min_samples_at_node == rhs.min_samples_at_node;
      bool eq_min_samples_leaf = min_samples_at_leaf == rhs.min_samples_at_leaf;
      bool eq_weight = weight == rhs.weight;
      bool eq_dec = *decider == *(rhs.decider);
      bool eq_lm = *leaf_manager == *(rhs.leaf_manager);
      bool eq_tree = tree == rhs.tree;
      bool eq_marks = marks == rhs.marks;
      //std::cout << eq_depth << std::endl;
      //std::cout << eq_init << std::endl;
      //std::cout << eq_min_samples << std::endl;
      //std::cout << eq_min_samples_leaf << std::endl;
      //std::cout << eq_weight << std::endl;
      //std::cout << eq_dec << std::endl;
      //std::cout << eq_lm << std::endl;
      //std::cout << eq_tree << std::endl;
      //std::cout << eq_marks << std::endl;
      return (eq_depth &&
              eq_init &&
              eq_min_samples &&
              eq_min_samples_leaf &&
              eq_weight &&
              eq_dec &&
              eq_lm &&
              eq_tree &&
              eq_marks);
    }

    /**
     * \brief Saves the tree to a textfile.
     *
     * This method can be used platform and system independent (e.g. Matlab -
     * C++).
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param filename string
     *   The filename of the file to store the tree in.
     */
    void save(const std::string &filename) {
      std::string serialized = fertilized::serialize(this, true);
      std::ofstream fstream(filename);
      fstream << serialized;
      fstream.close();
    }
#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint &version) {
        ar & max_depth;
        ar & is_initialized_for_training;
        ar & min_samples_at_node;
        ar & min_samples_at_leaf;
        ar & weight;
        ar & decider;
        ar & leaf_manager;
        ar & tree;
        ar & marks;
        ar & stored_in_leafs;
    };
#endif

   protected:
    // cppcheck-suppress uninitVar
    Tree() {}

   private:
    /**
     * The maximum depth of the tree. Non-const for serialization purposes
     * only.
     */
    uint max_depth;
    /**
     * Whether the \ref fit method has been called and the DFS and BFS
     * methods can now be used for training.
     */
    bool is_initialized_for_training;
    /** The minimum number of samples that must arrive at an inner node. */
    unsigned int min_samples_at_node;
    /** The minimum number of samples that must arrive at a leaf. */
    unsigned int min_samples_at_leaf;
    /** A weight assigned to this tree. Can be used by learning algorithms. */
    float weight;
    /** The amount of samples stored in leafs so far. */
    size_t stored_in_leafs;
    /** The associated classifier manager. */
    std::shared_ptr<dec_t> decider;
    /** The associated leaf manager. */
    std::shared_ptr<leaf_man_t> leaf_manager;
    /** Holds the entire tree structure. */
    std::vector<node_id_pair_t> tree;
    /**
     * A storage for marked nodes that still must to be processed during the
     * tree building process.
     */
    std::deque<node_todo_tuple_t> marks;
    // If any, a deep copy must be made of a tree to guarantee consistency
    // between the tree layout and the saved features, classifiers and leafs.
    // This is disallowed for the first.
    DISALLOW_COPY_AND_ASSIGN(Tree);
  };
};  // namespace fertilized
#endif  // FERTILIZED_TREE_H_
