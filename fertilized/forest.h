/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FOREST_H_
#define FERTILIZED_FOREST_H_

#include "./global.h"

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <fstream>

#include "./types.h"
#include "./tree.h"

#include "./trainings/itraining.h"
#include "./bagging/ibaggingstrategy.h"
#include "./execution_strategies/iexecutionstrategy.h"
#include "./execution_strategies/localexecutionstrategy.h"
#include "./data_providers/iforestdataprovider.h"
#include "./data_providers/unchangedfdataprovider.h"
#include "./serialization/serialization.h"
#include "./ndarray.h"

namespace fertilized {
  /**
   * Standard forest class of the library.
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
   * - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
   * - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
   * - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
   * .
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Forest {
   public:
    typedef Tree<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> tree_t;
    typedef ITraining<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> training_t;
    typedef IExecutionStrategy<input_dtype, feature_dtype, annotation_dtype,
                  leaf_return_dtype, forest_return_dtype> exec_strat_t;
    typedef IForestDataProvider<input_dtype, annotation_dtype> fdprov_t;
    typedef typename tree_t::dec_t dec_t;
    typedef typename tree_t::leaf_man_t leaf_man_t;
    typedef std::shared_ptr<tree_t> tree_ptr_t;
    typedef std::vector<tree_ptr_t> tree_ptr_vec_t;
    typedef typename leaf_man_t::wlresult_list_t wlresult_list_t;

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param max_tree_depth uint > 0
     *     The maximum tree depth, including leafs (up to including).
     * \param min_samples_at_leaf uint > 0
     *     The minimum number of samples at a leaf (from including).
     * \param min_samples_at_node uint>=2*min_samples_at_leaf
     *     The minimum number of samples at a node (from including).
     * \param n_trees uint>1
     *     The number of trees.
     * \param deciders vector(shared(IDecider))
     *     The deciders for each tree.
     * \param leaf_managers vector(shared(ILeafManager))
     *     The leaf managers for each tree.
     * \param training ITraining
     *     The training to use.
     */
    Forest(const uint &max_tree_depth,
           const uint &min_samples_at_leaf,
           const uint &min_samples_at_node,
           const uint &n_trees,
           const std::vector<std::shared_ptr<dec_t>> &deciders,
           const std::vector<std::shared_ptr<leaf_man_t>> &leaf_managers,
           const std::shared_ptr<training_t> &training)
      : trees(std::make_shared<tree_ptr_vec_t>(tree_ptr_vec_t(n_trees))),
        training(training) {
      if (n_trees < 2) {
        throw Fertilized_Exception("The number of trees to form a forest must "
          "be greater 1!");
      }
      if (deciders.size() != static_cast<size_t>(n_trees) ||
          leaf_managers.size() != static_cast<size_t>(n_trees)) {
        throw Fertilized_Exception("The number of provided classifier managers "
          "and leaf managers for the construction of a forest must exactly "
          "match the number of trees in the forest.");
      }
      for (size_t i = 0; i < n_trees; ++i) {
        // Check compatibility training - classifier manager.
        this -> training -> check_compatibility(*(deciders[i]));
        // Create the tree.
        (*trees)[i] = tree_ptr_t(
          new tree_t(max_tree_depth, min_samples_at_leaf, min_samples_at_node,
                      deciders[i],
                      leaf_managers[i]));
      }
    };

   /**
    * Combines UNTRAINED trees to a forest.
    *
    * -----
    * Available in:
    * - C++
    * - Python
    * - Matlab
    * .
    * Exported name: ForestFromTrees
    *
    * -----
    *
    * \param trees vector(shared(Tree))
    *   The untrained trees.
    * \param training ITraining
    *   The training to use.
    */
    Forest(const tree_ptr_vec_t &trees,
           const std::shared_ptr<training_t> &training) {
      if (trees.size() < 2) {
        throw Fertilized_Exception("The number of trees to form a forest must "
          "be greater 1!");
      }
      for (const auto &tree_ptr : trees) {
        if (tree_ptr -> is_initialized() || tree_ptr -> depth() > 0) {
          throw Fertilized_Exception("The method forest.ForestFromTrees "
            "is only meant to combine UNTRAINED trees! Otherwise, use "
            "'CombineTrees'!");
        }
      }
      this -> trees = std::make_shared<tree_ptr_vec_t>(trees);
      this -> training = training;
    };

   /**
    * Combines TRAINED trees to a forest. !! Training is not possible any more !!
    *
    * -----
    * Available in:
    * - C++
    * - Python
    * - Matlab
    * .
    * Exported name: CombineTrees
    *
    * -----
    *
    * \param trees vector(shared(Tree))
    *   The trained trees to combine.
    */
    Forest(const tree_ptr_vec_t &trees) {
      if (trees.size() < 2) {
        throw Fertilized_Exception("The number of trees to form a forest must "
          "be greater 1!");
      }
      size_t tree_counter = 0;
      for (const auto &tree_ptr : trees) {
        if (! tree_ptr -> is_initialized()) {
          throw Fertilized_Exception("The method forest.CombineTrees "
            "is only meant to combine TRAINED trees! Otherwise, use "
            "'ForestFromTrees'! Tree " + std::to_string(tree_counter) +
            " is not initialized!");
          tree_counter++;
        }
      }
      this -> trees = std::make_shared<tree_ptr_vec_t>(trees);
      this -> training = std::shared_ptr<training_t>(nullptr);
    };

    /**
     * Deserializing constructor to load a forest from a file.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     * Exported name: ForestFromFile
     *
     * -----
     *
     * \param filename string
     *   The file to load the forest from.
     */
    Forest(std::string filename) {
      std::ifstream fstream(filename);
      std::stringstream sstream;
      if (fstream) {
        sstream << fstream.rdbuf();
        fstream.close();
        deserialize(sstream, this);
      } else {
        throw Fertilized_Exception("Could not load forest from file: " +
          filename);
      }
    };


    /**
     * Fits the forest on the given data.
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
     * \param num_threads uint>0
     *   The number of threads to use for fitting.
     */
    void fit(const Array<const input_dtype, 2, 2> &data,
             const Array<const annotation_dtype, 2, 2> &annotations,
             uint num_threads=1) {
      auto data_provider = std::make_shared<UnchangedFDataProvider<input_dtype,
                                                                   annotation_dtype>>(data, annotations);
      if (data.TPLMETH getSize<1>() != get_input_data_dimensions()) {
        throw Fertilized_Exception("Incorrect number of features!");
      }
      auto execstrat = LocalExecutionStrategy<input_dtype,
        feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>(num_threads);
      fit_dprov(data_provider, &execstrat);
    };

    /**
     * Gets the depths of all trees.
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
    Array<size_t, 1, 1> depths() const {
      Array<size_t, 1, 1> result = allocate(trees -> size());
      size_t tree_id = 0;
      for (const auto &tree_ptr : *trees) {
        result[tree_id] = tree_ptr -> depth();
        tree_id++;
      }
      return result;
    }

    /**
     * \brief The fitting function for a forest.
     *
     * Fits this forest to the data given by the data provider.
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
     * \param data_provider shared(IForestDataProvider)
     *   The data provider for the fitting process.
     * \param execution_strategy IExecutionStrategy*
     *   The execution strategy to use.
     */
    void fit_dprov(const std::shared_ptr<fdprov_t> &fdata_provider,
                   exec_strat_t *execution_strategy) {
      if (training == nullptr)
        throw Fertilized_Exception("No training was provided when constructing"
          " the forest! 'fit' not possible.");
      {
#ifdef PYTHON_ENABLED
        py::gil_guard_release guard;
#endif
        // Compatibility check training - dataprovider.
        training -> check_compatibility(*fdata_provider);
        // Initialize execution strategy.
        execution_strategy -> initialize(fdata_provider, trees);
        // Train.
        training -> perform(*trees, fdata_provider.get(), execution_strategy);
        // Cleanup.
        execution_strategy -> cleanup();
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
      if (data.TPLMETH getSize<1>() != get_decider() -> get_required_num_data_dim()) {
         throw Fertilized_Exception("Wrong array shape! Expecting " +
           std::to_string(get_decider() -> get_required_num_data_dim()) + " columns, "
           "got " + std::to_string(data.TPLMETH getSize<1>()) + "!");
      }
      if (num_threads == 0) {
         throw Fertilized_Exception("The number of threads must be >0!");
      }
      auto leaf_manager = get_leaf_manager();
      Array<double, 2, 2> result_array = allocate(data.TPLMETH getSize<0>(),
                                                  leaf_manager ->
                                                    get_summary_dimensions(trees -> size()));
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
          shared(data, leaf_manager, result_array, base_ptr, lines) \
          schedule(static)
        for (int i = 0; i < data.TPLMETH getSize<0>(); ++i) {
          leaf_manager -> summarize_forest_result(predict_forest_result(
                                                    base_ptr + i * line_length,
                                                    1),
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
      // Currently this method is only supported for a threshold decider
      // and a VolumeFeatureSelectionProvider.
      typedef const ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>* ctcptr;
      ctcptr thresh_dec = dynamic_cast<ctcptr>(get_decider().get());
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
        resheight = static_cast<int>((image.TPLMETH getSize<1>() - patch_y) / step_size + 1);
        reswidth = static_cast<int>((image.TPLMETH getSize<2>() - patch_x) / step_size + 1);
      }
      Array<float, 2, 2> result = allocate(resheight, reswidth);
      result.deep() = 0.f;
      float correction_ratio = (reduce_to_patch_positions ?
                                  1.f / static_cast<float>(step_size) :
                                  1.f);
      float ratio_parameters[] = {p1, p2, correction_ratio, correction_ratio};
      size_t write_x, write_y;
      {
#ifdef PYTHON_ENABLED
        py::gil_guard_release guard;
#endif
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
            get_leaf_manager() -> add_forest_prediction_to_image(
              get_tree_weights(),
              predict_forest_result(data_ptr, 1, transformer),
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
    forest_return_dtype predict_forest_result(const input_dtype *data,
                                              const size_t &data_step,
                                              const std::function<void(void*)> &dptf = nullptr) const {
      auto result_pair_list = wlresult_list_t();
      result_pair_list.reserve(trees -> size());
      for (const auto &tree_ptr : *trees) {
        result_pair_list.push_back(
          std::make_pair(tree_ptr -> predict_leaf_result(data, data_step, 0, dptf),
                         tree_ptr -> get_weight()));
      }
      return (*trees)[0] -> combine_leaf_results(result_pair_list);
    };

    /**
     * \brief Data prediction.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     */
    forest_return_dtype predict_forest_result(const std::vector<input_dtype> &data) const {
      return predict_forest_result(&data[0], 1);
    };

    /**
     * Gets the required input data dimenstion.
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
    size_t get_input_data_dimensions() const {
      return (*trees)[0] -> get_input_data_dimensions();
    }

    /**
     * Gets the decider of the first tree.
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
      return (*trees)[0] -> get_decider();
    };

    /**
     * Gets the tree vector.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     */ 
    tree_ptr_vec_t get_trees() const {
      return trees;
    }
    
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
      Array<double, 1, 1> result;
      unsigned int nvalid = 0;
      bool initialized = false;
      for (const auto &tree_ptr : *trees) {
        if (tree_ptr -> get_n_nodes() <= 1) {
          // The tree cannot be used for importance computation, since
          // it has no decision nodes!
          continue;
        } else {
          nvalid++;
          if (initialized) {
            result.deep() += tree_ptr -> compute_feature_importances();
          } else {
            result = tree_ptr -> compute_feature_importances();
            initialized = true;
          }
        }
      }
      if (nvalid == 0) {
        throw Fertilized_Exception("No trees with deciders found! Can not "
                                   "compute feature importances. Have you run "
                                   "the training? If so, the trees do not find "
                                   "any meaningful splits.");
      }
      // Normalize!
      result.deep() /= static_cast<double>(nvalid);
      return result;
    }

    /**
     * Gets the leaf manager of the first tree.
     *
     * -----
     * Available in:
     * - C++
     * .
     *
     * -----
     */
    std::shared_ptr<const leaf_man_t> get_leaf_manager() const {
      return (*trees)[0] -> get_leaf_manager();
    }

    /**
     * Gets all tree weights.
     *
     * The returned list is a copy of the actual weights! Changes to it are not
     * affecting the forest object!
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
    std::vector<float> get_tree_weights() const {
      std::vector<float> result(trees -> size());
      for (std::size_t tree_idx = 0; tree_idx < trees -> size(); ++tree_idx) {
        result[tree_idx] = trees -> at(tree_idx) -> get_weight();
      }
      return result;
    }

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    bool operator==(const Forest<input_dtype, feature_dtype, annotation_dtype,
                           leaf_return_dtype, forest_return_dtype> &rhs) const {
      if (trees -> size() != rhs.trees -> size())
        return false;
      for (size_t i = 0; i < trees -> size(); ++i) {
        if (!(*(trees -> at(i)) == *(rhs.trees -> at(i))))
          return false;
      }
      if (trees -> at(0) -> get_samples_stored() == 0) {
        // Training has not yet taken place. Compare training strategies.
        if (training.get() == nullptr) {
          if (rhs.training.get() != nullptr) {
            return false;
          }
        } else {
          if (! (*training == *(rhs.training))) {
            return false;
          }
        }
      }

      return true;
    }

    /**
     * Saves the forest to a file with the specified name.
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
     *   The filename to use.
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
    void serialize(Archive & ar, const uint file_version) {
      ar & trees;
      ar & training;
    }
#endif

   protected:
    Forest() {}

   private:
    std::shared_ptr<tree_ptr_vec_t> trees;
    std::shared_ptr<training_t> training;
    // Should only work with deep copies, if at all.
    DISALLOW_COPY_AND_ASSIGN(Forest);
  };
};  // namespace fertilized
#endif  // FERTILIZED_FOREST_H_
