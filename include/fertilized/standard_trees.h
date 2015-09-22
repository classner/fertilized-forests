/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_STANDARD_TREES_H_
#define FERTILIZED_STANDARD_TREES_H_

#include "./global.h"

#include <vector>
#include <memory>
#include <utility>
#include <limits>

#include "./types.h"
#include "./tree.h"

#include "./impurities/ientropyfunction.h"
#include "./impurities/inducedentropy.h"
#include "./impurities/classificationerror.h"
#include "./impurities/renyientropy.h"
#include "./impurities/shannonentropy.h"
#include "./impurities/tsallisentropy.h"
#include "./gains/entropygain.h"
#include "./threshold_optimizers/ithresholdoptimizer.h"
#include "./threshold_optimizers/classificationthresholdoptimizer.h"
#include "./threshold_optimizers/randomizedclassificationthresholdoptimizer.h"
#include "./threshold_optimizers/regressionthresholdoptimizer.h"
#include "./threshold_optimizers/varianceclassificationthresholdoptimizer.h"
#include "./threshold_optimizers/alternatingthresholdoptimizer.h"
#include "./regression/constantregressioncalculator.h"
#include "./regression/linearregressioncalculator.h"
#include "./features/alignedsurfacecalculator.h"
#include "./features/standardfeatureselectionprovider.h"
#include "./features/volumefeatureselectionprovider.h"
#include "./deciders/thresholddecider.h"
#include "./leafs/classificationleafmanager.h"
#include "./leafs/regressionleafmanager.h"
#include "./leafs/houghleafmanager.h"
#include "./leafs/ileafmanager.h"
#include "./features/isurfacecalculator.h"
#include "./deciders/idecider.h"
#include "./default_values.h"

namespace fertilized {
  /**
   * \brief Constructs a default decision tree for classification.
   *
   * It uses an axis aligned decider.
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
   * Exported name: StandardClassificationTree
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
   * \param n_thresholds_per_feature size_t>=0
   *     The number of thresholds to evaluate per feature. If set to zero,
   *     search for the perfect split. Default: 0.
   * \param min_samples_per_leaf uint>0
   *     The minimum number of samples at a leaf node. Default: 1.
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
  std::shared_ptr<fertilized::Tree<input_dtype, input_dtype, uint,
       std::vector<float>, std::vector<float>>> construct_classifier_tree(
    const uint &n_classes,
    const size_t &n_features,
    uint max_depth=0,
    size_t test_n_features_per_node=0,
    const size_t &n_thresholds_per_feature=0,
    const uint &min_samples_per_leaf=1,
    const uint &min_samples_per_split=2,
    const float &min_gain_threshold=1E-7,
    const bool &allow_redraw=true,
    const uint &random_seed=1,
    std::string entropy_name="induced",
    const float &entropy_p1=2.f,
    const uint threshold_optimization_threads=1) {
    if (n_classes < 2) {
      throw Fertilized_Exception("It is not possible to create a classifier "
        "for less than two classes!");
    }
    if (test_n_features_per_node == 0) {
      test_n_features_per_node = static_cast<size_t>(floor(sqrt(static_cast<double>(n_features))));
    }
    if (max_depth == 0) {
      max_depth = std::numeric_limits<uint>::max();
    }
    std::shared_ptr<IEntropyFunction<float>> entropy;
    if (entropy_name == "induced")
      entropy = std::make_shared<InducedEntropy<float>>(entropy_p1);
    if (entropy_name == "classification_error")
      entropy = std::make_shared<ClassificationError<float>>();
    if (entropy_name == "renyi")
      entropy = std::make_shared<RenyiEntropy<float>>(entropy_p1);
    if (entropy_name == "tsallis")
      entropy = std::make_shared<TsallisEntropy<float>>(entropy_p1);
    if (entropy_name == "shannon")
      entropy = std::make_shared<ShannonEntropy<float>>();
    if (entropy.get() == nullptr) {
      throw Fertilized_Exception("Unknown entropy!");
    }
    auto gainc = std::make_shared<EntropyGain<float>>(entropy);
    std::shared_ptr<IThresholdOptimizer<input_dtype, input_dtype, uint>> threshopt;
    if (n_thresholds_per_feature == 0) {
      threshopt = std::make_shared<ClassificationThresholdOptimizer<input_dtype, input_dtype, uint>>(true, n_classes, gainc, min_gain_threshold, 1);
    } else {
      threshopt = std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype, input_dtype, uint>>(
        new RandomizedClassificationThresholdOptimizer<input_dtype, input_dtype, uint>(n_thresholds_per_feature, n_classes, gainc, min_gain_threshold, 1, random_seed));
    }
    auto featc = std::make_shared<AlignedSurfaceCalculator<input_dtype, uint>>();
    size_t real_selections_to_generate = test_n_features_per_node;
    if (allow_redraw)
      real_selections_to_generate = n_features;
    auto featsel = std::make_shared<StandardFeatureSelectionProvider>(real_selections_to_generate, 1, n_features, n_features, random_seed);
    size_t n_valids_to_use = 0;
    if (allow_redraw)
      n_valids_to_use = test_n_features_per_node;
    auto classifier = std::shared_ptr<ThresholdDecider<input_dtype, input_dtype, uint>>(
      new ThresholdDecider<input_dtype, input_dtype, uint>(
      featsel, featc, threshopt, n_valids_to_use, threshold_optimization_threads, false, 0.05f, 0, true));
    auto leafm = std::make_shared<ClassificationLeafManager<input_dtype, uint>>(n_classes);
    return std::make_shared<Tree<input_dtype, input_dtype, uint, std::vector<float>, std::vector<float>>>(
      max_depth, min_samples_per_leaf, min_samples_per_split, classifier, leafm);
  };

  /**
   * \brief Constructs a default decision tree for regression.
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
   * Exported name: StandardRegressionTree
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
   * \param min_samples_per_leaf uint>0
   *     The minimum number of samples at a leaf node. Default: 3.
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
  std::shared_ptr<fertilized::Tree<input_dtype, input_dtype, input_dtype,
       std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, 
       std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>> 
    construct_regression_tree(
      const size_t &n_features,
      uint max_depth=0,
      size_t test_n_features_per_node=0,
      const size_t &n_thresholds_per_feature=10,
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
    if (test_n_features_per_node == 0) {
      test_n_features_per_node = static_cast<size_t>(floor(sqrt(static_cast<double>(n_features))));
    }
    if (max_depth == 0) {
      max_depth = std::numeric_limits<uint>::max();
    }
    if (numerical_zero_threshold < 0.f && numerical_zero_threshold != -1.f) {
      throw Fertilized_Exception("Invalid value for numerical_zero_threshold!");
    }
    std::shared_ptr<IEntropyFunction<float>> entropy;
    if (entropy_name == "induced")
      entropy = std::make_shared<InducedEntropy<float>>(entropy_p1);
    if (entropy_name == "classification_error")
      entropy = std::make_shared<ClassificationError<float>>();
    if (entropy_name == "renyi")
      entropy = std::make_shared<RenyiEntropy<float>>(entropy_p1);
    if (entropy_name == "tsallis")
      entropy = std::make_shared<TsallisEntropy<float>>(entropy_p1);
    if (entropy_name == "shannon")
      entropy = std::make_shared<ShannonEntropy<float>>();
    if (entropy.get() == nullptr) {
      throw Fertilized_Exception("Unknown entropy!");
    }
    auto linear_reg_calc = std::make_shared<LinearRegressionCalculator<input_dtype>>(true, static_cast<input_dtype>(numerical_zero_threshold));
    auto threshopt =
      std::shared_ptr<RegressionThresholdOptimizer<input_dtype, input_dtype>>(
        new RegressionThresholdOptimizer<input_dtype, input_dtype>(n_thresholds_per_feature, linear_reg_calc, entropy, min_gain_threshold, 1, random_seed));
    auto featc = std::make_shared<AlignedSurfaceCalculator<input_dtype, input_dtype>>();
    size_t real_selections_to_generate = test_n_features_per_node;
    if (allow_redraw)
      real_selections_to_generate = n_features;
    auto class_featsel = std::make_shared<StandardFeatureSelectionProvider>(real_selections_to_generate, 1, n_features, n_features, random_seed);
    auto leaf_featsel = std::make_shared<StandardFeatureSelectionProvider>(n_features, 1, n_features, n_features, random_seed);
    size_t n_valids_to_use = 0;
    if (allow_redraw)
      n_valids_to_use = test_n_features_per_node;
    auto classifier = std::make_shared<ThresholdDecider<input_dtype, input_dtype, input_dtype>>(
      class_featsel, featc, threshopt, n_valids_to_use,threshold_optimization_threads);
    auto leafm = std::shared_ptr<RegressionLeafManager<input_dtype>>(new RegressionLeafManager<input_dtype>(leaf_featsel,n_valids_to_use, linear_reg_calc, entropy, true, threshold_optimization_threads, summary_mode));
    return std::make_shared<Tree<input_dtype, input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>(
      max_depth, min_samples_per_leaf, min_samples_per_split, classifier, leafm);
  };

   /**
   * \brief Constructs a fast decision tree for regression.
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
   * Exported name: FastRegressionTree
   *
   * -----
   *
   * \param n_features size_t>0
   *     The number of features available.
   * \param max_depth uint>=0
   *     The maximum tree depth. If 0, it is set to UINT_MAX to allow for
   *     maximally large trees.
   * \param test_n_features_per_node size_t>=0
   *     The number of features to evaluate as split criteria at each tree
   *     node. If 0, it is set to sqrt(n_features). Default: 0.
   * \param n_thresholds_per_feature size_t>0
   *     The number of thresholds to evaluate per feature. Default: 10.
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
  std::shared_ptr<fertilized::Tree<input_dtype, input_dtype, input_dtype,
       std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, 
       std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>> 
    construct_fast_regression_tree(
      const size_t &n_features,
      uint max_depth=0,
      size_t test_n_features_per_node=0,
      const size_t &n_thresholds_per_feature=10,
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
    if (test_n_features_per_node == 0) {
      test_n_features_per_node = static_cast<size_t>(floor(sqrt(static_cast<double>(n_features))));
    }
    if (max_depth == 0) {
      max_depth = std::numeric_limits<uint>::max();
    }
    if (numerical_zero_threshold < 0.f && numerical_zero_threshold != -1.f) {
      throw Fertilized_Exception("Invalid value for numerical_zero_threshold!");
    }

    std::shared_ptr<IEntropyFunction<float>> entropy;
    if (entropy_name == "shannon")
      entropy =  std::make_shared<ShannonEntropy<float>>();
    if (entropy_name == "induced")
      entropy =  std::make_shared<InducedEntropy<float>>(entropy_p1);
    auto constant_reg_calc = std::make_shared<ConstantRegressionCalculator<input_dtype>>();
    auto linear_reg_calc = std::make_shared<LinearRegressionCalculator<input_dtype>>(true, static_cast<input_dtype>(numerical_zero_threshold));
    auto threshopt =
      std::shared_ptr<RegressionThresholdOptimizer<input_dtype, input_dtype>>(
        new RegressionThresholdOptimizer<input_dtype, input_dtype>(n_thresholds_per_feature, constant_reg_calc, entropy, min_gain_threshold, 1, random_seed));
    auto featc = std::make_shared<AlignedSurfaceCalculator<input_dtype, input_dtype>>();
    size_t real_selections_to_generate = test_n_features_per_node;
    if (allow_redraw)
      real_selections_to_generate = n_features;
    auto class_featsel = std::make_shared<StandardFeatureSelectionProvider>(real_selections_to_generate, 1, n_features, n_features, random_seed);
    auto leaf_featsel = std::make_shared<StandardFeatureSelectionProvider>(n_features, 1, n_features, n_features, random_seed);
    size_t n_valids_to_use = 0;
    if (allow_redraw)
      n_valids_to_use = test_n_features_per_node;
    auto classifier = std::make_shared<ThresholdDecider<input_dtype, input_dtype, input_dtype>>(
      class_featsel, featc, threshopt, n_valids_to_use,threshold_optimization_threads);
    auto leafm = std::shared_ptr<RegressionLeafManager<input_dtype>>(new RegressionLeafManager<input_dtype>(leaf_featsel,n_valids_to_use, linear_reg_calc, entropy, true, threshold_optimization_threads, summary_mode));
    return std::make_shared<Tree<input_dtype, input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>>>(
      max_depth, min_samples_per_leaf, min_samples_per_split, classifier, leafm);
  };

  /**
   * Constructs a default Hough tree.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - uint8_t; int16_t; int16_t
   * .
   * Exported name: StandardHoughTree
   *
   * -----
   *
   * \param patch_dimensions vector<size_t>0>, three elements
   *     The patch size in x, y, z.
   * \param n_thresholds_per_split size_t>=0
   *     The number of thresholds to evaluate per feature.
   * \param n_splits_per_node size_t>0
   *     The number of features to evaluate as split criteria at each tree
   *     node.
   * \param max_depth uint>=0
   *     The maximum tree depth. If 0, it is set to UINT_MAX to allow for
   *     maximally large trees.
   * \param min_sample_counts vector<uint>0>, two elements.
   *     The min samples per leaf, and min samples per split. The second value
   *     must be >= 2 * the first value.
   * \param random_seed uint>=1
   *     The random seed to initialize the RNG.
   * \param min_gain_thresholds vector<float>=0.f>, two elements.
   *     The minimum gains for classification and regression.
   * \param patch_annot_luc bool
   *     Whether the patch annotations contain patch position for the patch
   *     left upper corner or patch center. Default: false.
   * \param allow_redraw bool
   *     If set to true, allows to try a new feature when optimizing for a
   *     split, when for a feature no split could be found that satisfied
   *     the minimum number of samples per leaf for each subgroup. This may be
   *     done until all features have been checked. Default: true.
   * \param num_threads uint>0
   *     The number of threads to use for optimizing the split nodes.
   *     Default: 1.
   * \param entropy_names vector<string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]>, two elements.
   *     The entropy type to use for classification and regression.
   *     Default: ["shannon", "shannon"]
   * \param entropy_p1 vector<float>0.f>, two elements.
   *     The entropy parameters. Might be unused (e.g. for the Shannon entropy).
   *     Default: [2, 2]
   * \param use_hough_heuristic bool
   *   Whether or not to use a heuristic for hough
   *   forests introduced by Juergen Gall
   *   (http://www.vision.ee.ethz.ch/~gallju/projects/houghforest/houghforest.html)
   *   Can be used only with an \ref AlternatingThresholdOptimizer.
   *   If used, the AlternatingThresholdOptimizer will guaranteed
   *   use opt2 if the ratio of negative samples is < \ref hough_heuristic_ratio or
   *   depth >= \ref hough_heuristic_maxd. opt2 must be a
   *   \ref VarianceClassificationThresholdOptimizer (check this
   *   manually!). Default: true.
   * \param hough_heuristic_ratio float>=0.f
   *   Default: 0.05f.
   * \param hough_heuristic_maxd uint
   *   Default: 0.
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  std::shared_ptr<fertilized::Tree<input_dtype, feature_dtype, annotation_dtype,
                       std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                       std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>> >>
    construct_hough_tree(const std::vector<size_t> &patch_dimensions,
                         const size_t &n_thresholds_per_split,
                         const size_t &n_splits_per_node,
                         uint max_depth,
                         const std::vector<uint> &min_sample_counts,
                         const uint &random_seed,
                         const std::vector<float> &min_gain_thresholds,
                         const bool &patch_annot_luc=false,
                         const bool &allow_redraw=true,
                         const uint &num_threads=1,
                         const std::vector<std::string> &entropy_names=_DEFAULT_ENTROPY_VEC_2,
                         const std::vector<float> &entropy_p1=_DEFAULT_ENTROPY_P1_2,
                         const bool &use_hough_heuristic=true,
                         const float &hough_heuristic_ratio=0.05f,
                         uint hough_heuristic_maxd=0) {
    if (n_splits_per_node == 0) {
      throw Fertilized_Exception("n_splits_per_node must be >0!");
    }
    if (max_depth == 0) {
      max_depth = std::numeric_limits<uint>::max();
    }
    if (patch_dimensions.size() != 3) {
      throw Fertilized_Exception("Exactly 3 patch dimensions are required!");
    }
    size_t patch_x = patch_dimensions[0];
    size_t patch_y = patch_dimensions[1];
    size_t patch_z = patch_dimensions[2];
    if (patch_x == 0 || patch_y == 0 || patch_z == 0) {
      throw Fertilized_Exception("Each patch dimension must be >0!");
    }
    if (min_sample_counts.size() != 2) {
      throw Fertilized_Exception("Exactly two sample counts are required!");
    }
    uint min_samples_at_leaf = min_sample_counts[0];
    uint min_samples_at_node = min_sample_counts[1];
    if (min_gain_thresholds.size() != 2) {
      throw Fertilized_Exception("Exactly two thresholds are required!");
    }
    float class_gain_threshold = min_gain_thresholds[0];
    float var_gain_threshold = min_gain_thresholds[1];
    if (hough_heuristic_maxd == 0) {
      hough_heuristic_maxd = max_depth - 2;
    }
    if (entropy_names.size() != 2) {
      throw Fertilized_Exception("Exactly two entropy names are required!");
    }
    std::shared_ptr<IEntropyFunction<float>> entropy_class;
    std::shared_ptr<IEntropyFunction<float>> entropy_reg;
    if ((entropy_names[0] == "induced" ||
         entropy_names[0] == "tsallis" ||
         entropy_names[0] == "renyi") &&
        entropy_p1.size() < 1) {
        throw Fertilized_Exception("If a generalized entropy should be used "
          "for classification, entropy_p1[0] must be specified!");
    }
    if (entropy_names[0] == "induced") {
      entropy_class = std::make_shared<InducedEntropy<float>>(entropy_p1[0]);
    } else {
      if (entropy_names[0] == "shannon") {
        entropy_class = std::make_shared<ShannonEntropy<float>>();
      } else {
        if (entropy_names[0] == "tsallis") {
          entropy_class = std::make_shared<TsallisEntropy<float>>(entropy_p1[0]);
        } else {
          if (entropy_names[0] == "renyi") {
            entropy_class = std::make_shared<RenyiEntropy<float>>(entropy_p1[0]);
          } else {
            throw Fertilized_Exception("Unknown entropy name for classification!");
          }
        }
      }
    }
    if ((entropy_names[1] == "induced" ||
         entropy_names[1] == "tsallis" ||
         entropy_names[1] == "renyi") &&
        entropy_p1.size() < 2) {
        throw Fertilized_Exception("If a generalized entropy should be used "
          "for regression, entropy_p1[1] must be specified!");
    }
    if (entropy_names[1] == "induced") {
      entropy_reg = std::make_shared<InducedEntropy<float>>(entropy_p1[1]);
    } else {
      if (entropy_names[1] == "shannon") {
        entropy_reg = std::make_shared<ShannonEntropy<float>>();
      } else {
        if (entropy_names[1] == "nvariance") {
          entropy_reg = std::shared_ptr<IEntropyFunction<float>>(nullptr);
        } else {
          if (entropy_names[1] == "tsallis") {
            entropy_reg = std::make_shared<TsallisEntropy<float>>(entropy_p1[1]);
          } else {
            if (entropy_names[1] == "renyi") {
              entropy_reg = std::make_shared<RenyiEntropy<float>>(entropy_p1[1]);
            } else {
              throw Fertilized_Exception("Unknown entropy name for regression!");
            }
          }
        }
      }
    }
    auto gainc = std::make_shared<EntropyGain<float>>(entropy_class);
    auto class_thresh_opt = std::shared_ptr<RandomizedClassificationThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>(
      new RandomizedClassificationThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>(
        n_thresholds_per_split,
        2, gainc, class_gain_threshold,
        3, random_seed));
    auto var_thresh_opt = std::shared_ptr<VarianceClassificationThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>(
      new VarianceClassificationThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>(
        n_thresholds_per_split, 2, 2, entropy_reg, var_gain_threshold, random_seed+1));
    auto alt_thresh_opt = std::shared_ptr<AlternatingThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>>(
      new AlternatingThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>(
        class_thresh_opt, var_thresh_opt, random_seed));
    size_t real_selections_to_generate = n_splits_per_node;
    if (allow_redraw)
      real_selections_to_generate = 3 * n_splits_per_node;
    auto feat_sel = std::shared_ptr<VolumeFeatureSelectionProvider>(
      new VolumeFeatureSelectionProvider(2, patch_x, patch_y, patch_z,
                                         real_selections_to_generate, random_seed));
    auto surf_calc = std::shared_ptr<DirectPatchDifferenceSurfCalculator<input_dtype, feature_dtype, annotation_dtype>>(
      new DirectPatchDifferenceSurfCalculator<input_dtype, feature_dtype, annotation_dtype>(patch_x, patch_y, patch_z, 
        patch_annot_luc));
    size_t n_valids_to_use = 0;
    if (allow_redraw)
      n_valids_to_use = n_splits_per_node;
    auto weak_classifier = std::shared_ptr<ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>>(
      new ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>(feat_sel, surf_calc,
        alt_thresh_opt, n_valids_to_use, num_threads, use_hough_heuristic,
        hough_heuristic_ratio, hough_heuristic_maxd));
    auto leaf_man = std::shared_ptr<HoughLeafManager<input_dtype, annotation_dtype>>(
      new HoughLeafManager<input_dtype, annotation_dtype>(2, 2));
    return std::make_shared<Tree<input_dtype, feature_dtype, annotation_dtype,
                         std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>,
                         std::vector<std::pair<float, std::shared_ptr<std::vector<annotation_dtype>>>>>>(
                         max_depth, min_samples_at_leaf, min_samples_at_node,
                         weak_classifier, leaf_man);
  };
};  // namespace fertilized
#endif  // FERTILIZED_STANDARD_TREES_H_
