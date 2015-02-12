/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_STANDARD_FORESTS_H_
#define FERTILIZED_STANDARD_FORESTS_H_

#include "./global.h"

#include <vector>

#include "./types.h"
#include "./forest.h"
#include "./standard_trees.h"
#include "./bagging/nobagging.h"
#include "./trainings/classictraining.h"

namespace fertilized {
  /**
   * \brief Constructs a default decision forest for classification.
   *
   * The forest uses axis-aligned threshold deciders. The default values for
   * each of the parameters lead to the parameter choice by various
   * heuristics. The results should be similar to those of the
   * ClassificationForest object of scikit-learn.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int
   * - float
   * - double
   * - uint8_t
   * .
   * Exported name: StandardClassificationForest
   *
   * -----
   *
   * \param n_classes uint>1
   *     The number of classes. All annotation labels must be in
   *     [0, ..., n_classes[.
   * \param n_features size_t>0
   *     The number of features available.
   * \param max_depth uint>=0
   *     The maximum tree depth. If 0, it is set to UINT_MAX to allow for
   *     maximally large trees. Default: 0.
   * \param test_n_features_per_node size_t>=0
   *     The number of features to evaluate as split criteria at each tree
   *     node. If 0, it is set to sqrt(n_features). Default: 0.
   * \param n_thresholds_per_features size_t>=0
   *     The number of thresholds to evaluate per feature. If set to zero,
   *     search for the perfect split. Default: 0.
   * \param n_trees uint>1
   *     The number of trees to use. Default: 10.
   * \param min_samples_per_leaf uint>0
   *     The minimum number of samples at a leaf node.  Default: 1.
   * \param min_samples_per_split uint>2*min_samples_per_leaf
   *     The minimum number of samples to continue splitting. Default: 2.
   * \param min_gain_threshold
   *     The minimum gain that must be reached to continue splitting. Default: 1E-7.
   * \param allow_redraw bool
   *     If set to true, allows to try a new feature when optimizing for a
   *     split, when for a feature no split could be found that satisfied
   *     the minimum number of samples per leaf for each subgroup. This may be
   *     done until all features have been checked. Default: true.
   * \param random_seed uint>=1
   *     The random seed to initialize the RNG. Default: 1.
   * \param entropy_name string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
   *     The entropy type to use. For the specification of induced entropy,
   *     see the "Publications" page. Default: 'induced'.
   * \param entropy_p1 float
   *     The entropy parameter. Might be unused (e.g. for the Shannon entropy).
   *     Default: 2.
   * \param threshold_optimization_threads uint>0
   *     The number of threads to use for threshold optimization. Default: 1.
   */
  template <typename input_dtype>
  std::shared_ptr<fertilized::Forest<input_dtype, input_dtype, uint,
    std::vector<float>, std::vector<float>>> construct_classifier_forest(
    const uint &n_classes,
    const size_t &n_features,
    const uint &max_depth=0,
    const size_t &test_n_features_per_node=0,
    const size_t &n_thresholds_per_feature=0,
    const uint &n_trees=10,
    const uint &min_samples_per_leaf=1,
    const uint &min_samples_per_split=2,
    const float &min_gain_threshold=1E-7,
    const bool &allow_redraw=true,
    const uint &random_seed=1,
    std::string entropy_name="induced",
    const float &entropy_p1=2.f,
    const uint threshold_optimization_threads=1) {
    if (n_trees < 2) {
      throw Fertilized_Exception("A forest must consist of at least 2 trees.");
    }
    typedef std::vector<
              std::shared_ptr<
                Tree<input_dtype,
                     input_dtype,
                     uint,
                     std::vector<float>,
                     std::vector<float>>>> tree_ptr_vec_t;

    typedef Forest<input_dtype,
                   input_dtype,
                   uint,
                   std::vector<float>,
                   std::vector<float>> forest_t;
    auto tree_ptr_vec = tree_ptr_vec_t();
    for (uint i = 0; i < n_trees; ++i) {
      auto tree = construct_classifier_tree<input_dtype>
                                            (n_classes,
                                            n_features,
                                            max_depth,
                                            test_n_features_per_node,
                                            n_thresholds_per_feature,
                                            min_samples_per_leaf,
                                            min_samples_per_split,
                                            min_gain_threshold,
                                            allow_redraw,
                                            random_seed + i,
                                            entropy_name,
                                            entropy_p1,
                                            threshold_optimization_threads);
      tree_ptr_vec.push_back(tree);
    }
    auto split_strat = std::make_shared<NoBagging<input_dtype,
                                                  input_dtype,
                                                  uint,
                                                  std::vector<float>,
                                                  std::vector<float>>>();
    auto training_inst = std::make_shared<ClassicTraining<input_dtype,
                                                          input_dtype,
                                                          uint,
                                                          std::vector<float>,
                                                          std::vector<float>>>(split_strat);
    auto forest = new forest_t(tree_ptr_vec, training_inst);
    return std::shared_ptr<forest_t>(forest);
  };



  /**
   * \brief Constructs a default decision forest for regression.
   *
   * It uses an axis aligned decider and uses linear regression at split
   * and leaf nodes.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float
   * - double
   * .
   * Exported name: StandardRegressionForest
   *
   * -----
   *
   * \param n_features size_t>0
   *     The number of features available.
   * \param max_depth uint>=0
   *     The maximum tree depth. If 0, it is set to UINT_MAX to allow for
   *     maximally large trees. Default: 0.
   * \param test_n_features_per_node size_t>=0
   *     The number of features to evaluate as split criteria at each tree
   *     node. If 0, it is set to sqrt(n_features). Default: 0.
   * \param n_thresholds_per_feature size_t>0
   *     The number of thresholds to evaluate per feature. Default: 10.
   * \param n_trees size_t>1
   *     The number of trees to use. Default: 10.
   * \param min_samples_per_leaf uint>0
   *     The minimum number of samples at a leaf node.  Default: 3.
   * \param min_samples_per_split uint>2*min_samples_per_leaf
   *     The minimum number of samples to continue splitting. Default: 6.
   * \param min_gain_threshold
   *     The minimum gain that must be reached to continue splitting. Default: 1E-7.
   * \param allow_redraw bool
   *     If set to true, allows to try a new feature when optimizing for a
   *     split, when for a feature no split could be found that satisfied
   *     the minimum number of samples per leaf for each subgroup. This may be
   *     done until all features have been checked. Default: true.
   * \param random_seed uint>=1
   *     The random seed to initialize the RNG. Default: 1.
   * \param entropy_name string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
   *     The entropy type to use. For the specification of induced entropy,
   *     see the "Publications" page. Default: 'shannon'.
   * \param entropy_p1 float
   *     The entropy parameter. Might be unused (e.g. for the Shannon entropy).
   *     Default: 2.
   * \param numerical_zero_threshold float>=0.f || -1.f
   *     The threshold below of which all values are treated as zeros.
   *     If set to -1.f, use the value suggested by Eigen. Default: -1.f.
   * \param threshold_optimization_threads uint>0
   *     The number of threads to use for threshold optimization. Default: 1.
   * \param summary_mode uint<3
   *   Determines the meaning of the values in the prediction matrix of
   *   the forest (the output of the convenience `predict` method of a forest).
   *   Case 0: Each row contains the prediction for each regressor (the first
   *           half of its entries) and the expected variances for each
   *           regressor (second half of its entries). To estimate the joint
   *           variance, a gaussian is fitted over the multimodal distribution
   *           defined by all trees.
   *   Case 1: Each row contains the prediction for each regressor (the first
   *           half of its entries) and the mean of the expected variances of
   *           each tree. This has no direct semantic meaning, but can give
   *           better results in active learning applications.
   *   Case 2: Each row contains the prediction for each regressor and
   *           the variance estimate for each regressor for each tree, e.g.,
   *           (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
   *           denoting regressor prediction and variance respectively, the
   *           first index the tree and the second index the regressor index.
   *   Default: 0.
   */
   template <typename input_dtype>
   std::shared_ptr<fertilized::Forest<input_dtype, input_dtype, input_dtype,
       std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, 
       std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>> 
    construct_regression_forest(
      const size_t &n_features,
      uint max_depth=0,
      size_t test_n_features_per_node=0,
      const size_t &n_thresholds_per_feature=10,
      const size_t &n_trees=10,
      const uint &min_samples_per_leaf=3,
      const uint &min_samples_per_split=6,
      const float &min_gain_threshold=1E-7,
      const bool &allow_redraw=true,
      const uint &random_seed=1,
      std::string entropy_name="shannon",
      const float &entropy_p1=2,
      const float &numerical_zero_threshold=-1.f,
      const uint &threshold_optimization_threads=1,
      const uint &summary_mode=0) {
    if (n_trees < 2) {
      throw Fertilized_Exception("A forest must consist of at least 2 trees.");
    }
    typedef std::vector<
              std::shared_ptr<
                Tree<input_dtype,
                     input_dtype,
                     input_dtype,
                     std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                     std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>> tree_ptr_vec_t;

    typedef Forest<input_dtype,
                     input_dtype,
                     input_dtype,
                     std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                     std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>> forest_t;
    auto tree_ptr_vec = tree_ptr_vec_t();
    for (uint i = 0; i < n_trees; ++i) {
      auto tree = construct_regression_tree<input_dtype>
                                            (n_features,
                                            max_depth,
                                            test_n_features_per_node,
                                            n_thresholds_per_feature,
                                            min_samples_per_leaf,
                                            min_samples_per_split,
                                            min_gain_threshold,
                                            allow_redraw,
                                            random_seed + i,
                                            entropy_name,
                                            entropy_p1,
                                            numerical_zero_threshold,
                                            threshold_optimization_threads,
                                            summary_mode);
      tree_ptr_vec.push_back(tree);
    }
    auto split_strat = std::make_shared<NoBagging<input_dtype,
                                                  input_dtype,
                                                  input_dtype,
                                                  std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                                                  std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>();
    auto training_inst = std::make_shared<ClassicTraining<input_dtype,
                                                          input_dtype,
                                                          input_dtype,
                                                          std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                                                          std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>(split_strat);
    auto forest = new forest_t(tree_ptr_vec, training_inst);
    return std::shared_ptr<forest_t>(forest);
  };


  /**
   * \brief Constructs a fast decision forest for regression.
   *
   * It uses an axis aligned decider and uses constant regression at split
   * and linear regression at leaf nodes.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float
   * - double
   * .
   * Exported name: FastRegressionForest
   *
   * -----
   *
   * \param n_features size_t>0
   *     The number of features available.
   * \param max_depth uint>=0
   *     The maximum tree depth. If 0, it is set to UINT_MAX to allow for
   *     maximally large trees. Default: 0.
   * \param test_n_features_per_node size_t>=0
   *     The number of features to evaluate as split criteria at each tree
   *     node. If 0, it is set to sqrt(n_features). Default: 0.
   * \param n_thresholds_per_feature size_t>0
   *     The number of thresholds to evaluate per feature. Default: 10.
   * \param n_trees size_t>1
   *     The number of trees. Default: 10.
   * \param min_samples_per_leaf uint>0
   *     The minimum number of samples at a leaf node.  Default: 3.
   * \param min_samples_per_split uint>2*min_samples_per_leaf
   *     The minimum number of samples to continue splitting. Default: 6.
   * \param min_gain_threshold
   *     The minimum gain that must be reached to continue splitting. Default: 1E-7.
   * \param allow_redraw bool
   *     If set to true, allows to try a new feature when optimizing for a
   *     split, when for a feature no split could be found that satisfied
   *     the minimum number of samples per leaf for each subgroup. This may be
   *     done until all features have been checked. Default: true.
   * \param random_seed uint>=1
   *     The random seed to initialize the RNG. Default: 1.
   * \param entropy_name string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
   *     The entropy type to use. For the specification of induced entropy,
   *     see the "Publications" page. Default: 'shannon'.
   * \param entropy_p1 float
   *     The entropy parameter. Might be unused (e.g. for the Shannon entropy).
   *     Default: 1E-7.
   * \param numerical_zero_threshold float>=0.f || -1.f
   *     The threshold below of which all values are treated as zeros.
   *     If set to -1.f, use the value suggested by Eigen. Default: -1.f.
   * \param threshold_optimization_threads uint>0
   *     The number of threads to use for threshold optimization. Default: 1.
   * \param summary_mode uint<3
   *   Determines the meaning of the values in the prediction matrix of
   *   the forest (the output of the convenience `predict` method of a forest).
   *   Case 0: Each row contains the prediction for each regressor (the first
   *           half of its entries) and the expected variances for each
   *           regressor (second half of its entries). To estimate the joint
   *           variance, a gaussian is fitted over the multimodal distribution
   *           defined by all trees.
   *   Case 1: Each row contains the prediction for each regressor (the first
   *           half of its entries) and the mean of the expected variances of
   *           each tree. This has no direct semantic meaning, but can give
   *           better results in active learning applications.
   *   Case 2: Each row contains the prediction for each regressor and
   *           the variance estimate for each regressor for each tree, e.g.,
   *           (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
   *           denoting regressor prediction and variance respectively, the
   *           first index the tree and the second index the regressor index.
   *   Default: 0.
   */
   template <typename input_dtype>
   std::shared_ptr<fertilized::Forest<input_dtype, input_dtype, input_dtype,
       std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, 
       std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>> 
    construct_fast_regression_forest(
      const size_t &n_features,
      uint max_depth=0,
      size_t test_n_features_per_node=0,
      const size_t &n_thresholds_per_feature=10,
      const size_t &n_trees=10,
      const uint &min_samples_per_leaf=3,
      const uint &min_samples_per_split=6,
      const float &min_gain_threshold=1E-7,
      const bool &allow_redraw=true,
      const uint &random_seed=1,
      std::string entropy_name="shannon",
      const float &entropy_p1=2.f,
      const float &numerical_zero_threshold=-1.f,
      const uint &threshold_optimization_threads=1,
      const uint &summary_mode=0) {
    if (n_trees < 2) {
      throw Fertilized_Exception("A forest must consist of at least 2 trees.");
    }
    typedef std::vector<
              std::shared_ptr<
                Tree<input_dtype,
                     input_dtype,
                     input_dtype,
                     std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                     std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>> tree_ptr_vec_t;

    typedef Forest<input_dtype,
                     input_dtype,
                     input_dtype,
                     std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                     std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>> forest_t;
    auto tree_ptr_vec = tree_ptr_vec_t();
    for (uint i = 0; i < n_trees; ++i) {
      auto tree = construct_fast_regression_tree<input_dtype>
                                            (n_features,
                                            max_depth,
                                            test_n_features_per_node,
                                            n_thresholds_per_feature,
                                            min_samples_per_leaf,
                                            min_samples_per_split,
                                            min_gain_threshold,
                                            allow_redraw,
                                            random_seed + i,
                                            entropy_name,
                                            entropy_p1,
                                            numerical_zero_threshold,
                                            threshold_optimization_threads,
                                            summary_mode);
      tree_ptr_vec.push_back(tree);
    }
    auto split_strat = std::make_shared<NoBagging<input_dtype,
                                                  input_dtype,
                                                  input_dtype,
                                                  std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                                                  std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>();
    auto training_inst = std::make_shared<ClassicTraining<input_dtype,
                                                          input_dtype,
                                                          input_dtype,
                                                          std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,
                                                          std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>(split_strat);
    auto forest = new forest_t(tree_ptr_vec, training_inst);
    return std::shared_ptr<forest_t>(forest);
  };
}  // namespace fertilized
#endif  // FERTILIZED_STANDARD_FORESTS_H_
