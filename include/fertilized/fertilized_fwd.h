
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */#pragma once
#ifndef FERTILIZED_FERTILIZED_FWD_H_
#define FERTILIZED_FERTILIZED_FWD_H_

namespace fertilized {
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Forest;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class Tree;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ObjectTemplate;

  template<typename input_dtype, typename annotation_dtype>
  struct TrainingAction;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class IExecutionStrategy;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class LocalExecutionStrategy;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IDecider;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ThresholdDecider;

  template <typename input_dtype, typename annotation_dtype>
  struct Sample;

  template <typename input_dtype, typename annotation_dtype>
  class NoCopyPatchSampleManager;

  template <typename input_dtype, typename annotation_dtype>
  class IDataProvider;

  template <typename input_dtype, typename annotation_dtype>
  class ISampleManager;

  template<typename input_dtype, typename annotation_dtype>
  class SubsamplingDataProvider;

  template<typename input_dtype, typename annotation_dtype>
  class UnchangedFDataProvider;

  
  struct PatchToImageCoordinateTransformer;

  template<typename input_dtype, typename annotation_dtype>
  class UnchangedDataProvider;

  template<typename input_dtype, typename annotation_dtype>
  class IForestDataProvider;

  template <typename input_dtype, typename annotation_dtype>
  class PatchSampleManager;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class NoBagging;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class EqualDistBagging;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class IBaggingStrategy;

  template<typename input_dtype>
  class LinearRegressionCalculator;

  template <typename input_dtype>
  class IRegressionCalculator;

  template <typename input_dtype>
  class ConstantRegressionCalculator;

  template <typename input_dtype>
  class InducedEntropy;

  template <typename input_dtype>
  class RenyiEntropy;

  template <typename input_dtype>
  class ShannonEntropy;

  template <typename input_dtype>
  class ClassificationError;

  template <typename input_dtype>
  class TsallisEntropy;

  template <typename input_dtype>
  class IEntropyFunction;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class IThresholdOptimizer;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class RandomizedClassificationThresholdOptimizer;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class VarianceClassificationThresholdOptimizer;

  template<typename input_dtype, typename feature_dtype>
  class RegressionThresholdOptimizer;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class TwoSideClassificationThresholdOptimizer;

  template<typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ClassificationThresholdOptimizer;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class AlternatingThresholdOptimizer;

  template <typename counting_dtype>
  class IGainCalculator;

  template <typename input_dtype>
  class EntropyGain;

  
  class DNNFeatureExtractor;

  
  class HOGExtractor;

  
  class IFeatureSelectionProvider;

  
  class StandardFeatureSelectionProvider;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DifferenceSurfaceCalculator;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class ISurfaceCalculator;

  
  class VolumeFeatureSelectionProvider;

  template <typename input_dtype, typename annotation_dtype>
  class LinearSurfaceCalculator;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
  class DirectPatchDifferenceSurfCalculator;

  
  class VolumeFeatureSelectionGenerator;

  
  class FeatCalcParamSet;

  
  class IFeatureSelectionGenerator;

  
  class StandardFeatureSelectionGenerator;

  template <typename input_dtype, typename annotation_dtype>
  class AlignedSurfaceCalculator;

  template <typename input_dtype, typename annotation_dtype>
  class QuadraticSurfaceCalculator;

  template<typename input_dtype, typename annotation_dtype>
  class ClassificationLeafManager;

  template<typename input_dtype, typename annotation_dtype>
  class HoughLeafManager;

  template <typename input_dtype>
  class RegressionLeafManager;

  template <typename input_dtype, typename annotation_dtype>
  class BoostingLeafManager;

  template<typename input_dtype, typename annotation_dtype,typename leaf_return_dtype, typename forest_return_dtype>
  class ILeafManager;

  template <typename T>
  class SamplingWithoutReplacement;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class AdaBoost;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class Samme_R;

  template <typename input_dtype, typename feature_dtype,typename annotation_dtype, typename leaf_return_dtype,typename forest_return_dtype>
  class Samme;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class IBoostingStrategy;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ITraining;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ClassicTraining;

  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class BoostedTraining;

}  // namespace fertilized
#endif  // FERTILIZED_FERTILIZED_FWD_H_
