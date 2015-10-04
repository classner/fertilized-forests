
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */#pragma once
#ifndef FERTILIZED_FERTILIZED_FWD_H_
#define FERTILIZED_FERTILIZED_FWD_H_

namespace fertilized {
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class AdaBoost;

  template <typename input_dtype, typename annotation_dtype>
  class AlignedSurfaceCalculator;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class AlternatingThresholdOptimizer;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class BoostedTraining;

  template <typename input_dtype, typename annotation_dtype>
  class BoostingLeafManager;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ClassicTraining;

  template <typename input_dtype>
  class ClassificationError;

  template<typename input_dtype, typename annotation_dtype>
  class ClassificationLeafManager;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ClassificationThresholdOptimizer;

  template <typename input_dtype>
  class ConstantRegressionCalculator;

  
  class DNNFeatureExtractor;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DifferenceSurfaceCalculator;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DirectPatchDifferenceSurfCalculator;

  template <typename input_dtype>
  class EntropyGain;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class EqualDistBagging;

  
  class FeatCalcParamSet;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Forest;

  
  class HOGExtractor;

  template<typename input_dtype, typename annotation_dtype>
  class HoughLeafManager;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class IBaggingStrategy;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class IBoostingStrategy;

  template <typename input_dtype, typename annotation_dtype>
  class IDataProvider;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IDecider;

  template <typename input_dtype>
  class IEntropyFunction;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class IExecutionStrategy;

  
  class IFeatureSelectionGenerator;

  
  class IFeatureSelectionProvider;

  template<typename input_dtype, typename annotation_dtype>
  class IForestDataProvider;

  template <typename counting_dtype>
  class IGainCalculator;

  template<typename input_dtype, typename annotation_dtype,typename leaf_return_dtype, typename forest_return_dtype>
  class ILeafManager;

  template <typename input_dtype>
  class IRegressionCalculator;

  template <typename input_dtype, typename annotation_dtype>
  class ISampleManager;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ISurfaceCalculator;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IThresholdOptimizer;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ITraining;

  template <typename input_dtype>
  class InducedEntropy;

  template<typename input_dtype>
  class LinearRegressionCalculator;

  template <typename input_dtype, typename annotation_dtype>
  class LinearSurfaceCalculator;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class LocalExecutionStrategy;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class NoBagging;

  template <typename input_dtype, typename annotation_dtype>
  class NoCopyPatchSampleManager;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ObjectTemplate;

  template <typename input_dtype, typename annotation_dtype>
  class PatchSampleManager;

  
  struct PatchToImageCoordinateTransformer;

  template <typename input_dtype, typename annotation_dtype>
  class QuadraticSurfaceCalculator;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class RandomizedClassificationThresholdOptimizer;

  template <typename input_dtype>
  class RegressionLeafManager;

  template<typename input_dtype, typename feature_dtype>
  class RegressionThresholdOptimizer;

  template <typename input_dtype>
  class RenyiEntropy;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class Samme;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class Samme_R;

  template <typename input_dtype, typename annotation_dtype>
  struct Sample;

  template <typename T>
  class SamplingWithoutReplacement;

  template <typename input_dtype>
  class ShannonEntropy;

  
  class StandardFeatureSelectionGenerator;

  
  class StandardFeatureSelectionProvider;

  template<typename input_dtype, typename annotation_dtype>
  class SubsamplingDataProvider;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ThresholdDecider;

  template<typename input_dtype, typename annotation_dtype>
  struct TrainingAction;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Tree;

  template <typename input_dtype>
  class TsallisEntropy;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class TwoSideClassificationThresholdOptimizer;

  template<typename input_dtype, typename annotation_dtype>
  class UnchangedDataProvider;

  template<typename input_dtype, typename annotation_dtype>
  class UnchangedFDataProvider;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class VarianceClassificationThresholdOptimizer;

  
  class VolumeFeatureSelectionGenerator;

  
  class VolumeFeatureSelectionProvider;

}  // namespace fertilized
#endif  // FERTILIZED_FERTILIZED_FWD_H_
