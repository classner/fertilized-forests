
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#pragma once
#ifndef FERTILIZED_SOIL_H_
#define FERTILIZED_SOIL_H_
#if !defined(FERTILIZED_FERTILIZED_H_)
#error The soil header may only be included within the fertilized.h header! Include fertilized.h itself to use the soil object.
#endif

namespace fertilized {
  /**
   * \brief Provides convenience summary types for the result types similar to Python and Matlab.
   */
  namespace Result_Types {
    /**
     * \brief Classification result types.
     * 
     * They are always defined as std::vector<float>.
     */
    struct probabilities {
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct leaf_return_dtype {
        typedef std::vector<float> type;
      };
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct forest_return_dtype {
        typedef std::vector<float> type;
      };
    };
    /**
     * \brief Regression result types.
     * 
     * They depend on the input_dtype. See the documentation of the
     * \ref RegressionLeafManager.
     */
    struct regression {
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct leaf_return_dtype {
        typedef std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>> type;
      };
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct forest_return_dtype {
        typedef std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>> type;
      };
    };
    /**
     * \brief Hough Forest result types.
     * 
     * They consist of a pair of float (foreground prob.) and a pointer to
     * a vector of int16_t (offsets). For a forest, contains a vector of these
     * pairs.
     */
    struct hough_map {
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct leaf_return_dtype {
        typedef std::pair<float, std::shared_ptr<std::vector<int16_t>>> type;
      };
      template <typename input_dtype, typename feature_dtype, typename annotation_dtype>
      struct forest_return_dtype {
        typedef std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>> type;
      };
    };
  };

  template <typename input_dtype=float,
            typename feature_dtype=float,
            typename annotation_dtype=unsigned int,
            typename result_type=Result_Types::probabilities>
  struct Soil {
  Soil() {};
  ~Soil() {};

  typedef typename result_type::template leaf_return_dtype<input_dtype, feature_dtype, annotation_dtype>::type leaf_return_dtype;
  typedef typename result_type::template forest_return_dtype<input_dtype, feature_dtype, annotation_dtype>::type forest_return_dtype;

  auto adaboost_vec_t() -> std::vector<std::shared_ptr<fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief AdaBoost.M2 boosting algorithm implementation
*
* Implements the original AdaBoost algorithm proposed by Freund and Schapire
*
* See "A decision-theoretic generalization of on-line learning and an
* application to boosting". Journal of Computer and System Sciences 55. 1997
*
* To support multi-class classification, the AdaBoost.M2 algorithm is used.
*
* Output when using BoostingLeafManager is
* estimator_probability*std::log(1.f/beta).
*
* \ingroup fertilizedboostingGroup
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
* .
* Serialization generation: 101
*
* -----
*/
  std::shared_ptr<fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  AdaBoost(

    ) {
   return std::shared_ptr<fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::AdaBoost<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

	   ));
  };

  auto alignedsurfacecalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>>>;
  /**
* \brief Forwards the data as features.
*
* Does not require any parameters.
*
* \ingroup fertilizedfeaturesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; uint
* - uint8_t; uint
* - float; uint
* - float; float
* - double; uint
* - double; double
* .
*
* -----
*/
  std::shared_ptr<fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>>
  AlignedSurfaceCalculator(

    ) {
   return std::shared_ptr<fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>>(
     new fertilized::AlignedSurfaceCalculator<input_dtype,annotation_dtype>(

	   ));
  };

  auto alternatingthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::AlternatingThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Uses two other threshold optimizers and randomly selects one of them at each split.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float; float; float
* - double; double; double
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::AlternatingThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  AlternatingThresholdOptimizer(

        const std::shared_ptr<typename fertilized::AlternatingThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>::IThresholdOptimizer_t> & opt1,
        const std::shared_ptr<typename fertilized::AlternatingThresholdOptimizer<input_dtype, feature_dtype, annotation_dtype>::IThresholdOptimizer_t> & opt2,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::AlternatingThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::AlternatingThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         opt1,
         opt2,
         random_seed
	   ));
  };

  auto boostedtraining_vec_t() -> std::vector<std::shared_ptr<fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief Implements a boosted training that uses a boosting implementation defined by an \ref IBoostingStrategy
*
* Trains all trees using a given boosting algorithm implementation
* Use a \ref BoostingLeafManager to let the boosting strategies decide their weight functions
*
* \ingroup fertilizedtrainingsGroup
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
* .
* Serialization generation: 101
*
* -----
*/
  std::shared_ptr<fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  BoostedTraining(

        const std::shared_ptr<typename fertilized::BoostedTraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::boost_strat_t> & boosting_strategy
    ) {
   return std::shared_ptr<fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::BoostedTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         boosting_strategy
	   ));
  };

  auto boostingleafmanager_vec_t() -> std::vector<std::shared_ptr<fertilized::BoostingLeafManager<input_dtype,annotation_dtype>>>;
  /**
* \brief Allows the boosting strategies to set their own tree functions
* to influence the combined result.
*
* Using thes LeafManager may lead to better classifcation results.
*
* Note that the output does not represent probabilites and may vary when
* using different \ref IBoostingStrategies
*
* \ingroup fertilizedleafsGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; uint
* - float; uint
* - double; uint
* - uint8_t; uint
* - uint8_t; int16_t
* .
* Serialization generation: 101
*
* -----
*/
  std::shared_ptr<fertilized::BoostingLeafManager<input_dtype,annotation_dtype>>
  BoostingLeafManager(

        const unsigned int & n_classes
    ) {
   return std::shared_ptr<fertilized::BoostingLeafManager<input_dtype,annotation_dtype>>(
     new fertilized::BoostingLeafManager<input_dtype,annotation_dtype>(

         n_classes
	   ));
  };

  auto classictraining_vec_t() -> std::vector<std::shared_ptr<fertilized::ClassicTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief Implements the vanilla decision forest training.
*
* Trains all trees independent of each other as allowed by the
* \ref IExecutionStrategy, possibly exploiting parallelism, etc.
*
* \ingroup fertilizedtrainingsGroup
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
  std::shared_ptr<fertilized::ClassicTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  ClassicTraining(

        const std::shared_ptr<typename fertilized::ClassicTraining<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::bag_strat_t> & bagging_strategy
    ) {
   return std::shared_ptr<fertilized::ClassicTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::ClassicTraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         bagging_strategy
	   ));
  };

  auto classificationerror_vec_t() -> std::vector<std::shared_ptr<fertilized::ClassificationError<float>>>;
  /**
* \brief Computes the classification error as 1-\max(p_i).
*
* \ingroup fertilizedimpuritiesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
* .
*
* -----
*/
  std::shared_ptr<fertilized::ClassificationError<float>>
  ClassificationError(

    ) {
   return std::shared_ptr<fertilized::ClassificationError<float>>(
     new fertilized::ClassificationError<float>(

	   ));
  };

  auto classificationleafmanager_vec_t() -> std::vector<std::shared_ptr<fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>>>;
  /**
* \brief Stores the probability distributions for n_classes at a leaf.
*
* \ingroup fertilizedleafsGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; uint
* - float; uint
* - double; uint
* - uint8_t; uint
* - uint8_t; int16_t
* .
* 
* -----
*/
  std::shared_ptr<fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>>
  ClassificationLeafManager(

        const unsigned int & n_classes
    ) {
   return std::shared_ptr<fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>>(
     new fertilized::ClassificationLeafManager<input_dtype,annotation_dtype>(

         n_classes
	   ));
  };

  auto classificationthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::ClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Optimizes one threshold very efficiently.
*
* Supports only classification annotations (unsigned int) with annotation
* values ranging in [0; n_classes - 1]. Searches the perfect threshold to
* split the data.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::ClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  ClassificationThresholdOptimizer(

        const bool & use_fast_search_approximation,
        const size_t & n_classes,
        const std::shared_ptr<fertilized::IGainCalculator<float> > & gain_calculator,
        const float & gain_threshold=1E-7,
        const size_t & annotation_step=1
    ) {
   return std::shared_ptr<fertilized::ClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::ClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         use_fast_search_approximation,
         n_classes,
         gain_calculator,
         gain_threshold,
         annotation_step
	   ));
  };

  auto constantregressioncalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::ConstantRegressionCalculator<input_dtype>>>;
  /**
* \brief Calculator for constant regression.
*
* This regression calculator uses a constant value to predict the output value.
* Therefore, it provides a constant prediction and a constant prediction covariance matrix.
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
*
* -----
*/
  std::shared_ptr<fertilized::ConstantRegressionCalculator<input_dtype>>
  ConstantRegressionCalculator(

    ) {
   return std::shared_ptr<fertilized::ConstantRegressionCalculator<input_dtype>>(
     new fertilized::ConstantRegressionCalculator<input_dtype>(

	   ));
  };

  auto dnnfeatureextractor_vec_t() -> std::vector<std::shared_ptr<fertilized::DNNFeatureExtractor>>;
  /**
* Extracts DNN features using a pretrained caffe network.
*
* To obtain reproducible results, you have to remove the dropout layers
* from the network specification file (this has been done for the default
* AlexNet). During extraction, always the full batch size is used. This
* means, that if you repeatedly only extract features from one image with
* the extract method, most of the batch will be unused. You should observe
* large speed gains by reducing the batch size in the model specification
* file to a batch size of one in that case.
*
* The mean image must be subtracted from any image before
* using the feature extractor. This can be done within the `extract` method,
* or, if you want to use many samples from an image, you can do that before.
* The default mean image is the one of the ImageNet dataset. The mean image
* format is a text file with a very simple layout:
*
* - the first line consists of the number of rows,
* - the second line consists of the columns,
* - the third line consists of the number of channels,
* - the fourth line contains all pixel values, in OpenCV memory layout
*   (rows, columns, channels, where channels are contiguous).
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
  std::shared_ptr<fertilized::DNNFeatureExtractor>
  DNNFeatureExtractor(

        std::string net_layout_file,
        std::string net_weights_file,
        std::string net_outlayer,
        const bool & use_cpu=0,
        const int & device_id=0,
        std::string mean_file=""
    ) {
   return std::shared_ptr<fertilized::DNNFeatureExtractor>(
     new fertilized::DNNFeatureExtractor(

         net_layout_file,
         net_weights_file,
         net_outlayer,
         use_cpu,
         device_id,
         mean_file
	   ));
  };

  auto differencesurfacecalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Calculates a feature as the difference between two data dimensions
* of inputs.
*
* \ingroup fertilizedfeaturesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - float; float; float
* - double; double; uint
* - double; double; double
* .
*
* -----
*/
  std::shared_ptr<fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>
  DifferenceSurfaceCalculator(

    ) {
   return std::shared_ptr<fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::DifferenceSurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>(

	   ));
  };

  auto directpatchdifferencesurfcalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Calculates a feature as the difference between two data dimensions
* of inputs.
*
* In contrast to the \ref DifferenceSurfaceCalculator, works with patches
* in images directly. It only works together with a \ref SubsamplingDataProvider
* with a \ref NoCopyPatchSampleManager, because they provide the images
* in the correct format.
*
* \ingroup fertilizedfeaturesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - uint8_t; int16_t; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>
  DirectPatchDifferenceSurfCalculator(

        const size_t & psx,
        const size_t & psy,
        const size_t & psz,
        const bool & luc
    ) {
   return std::shared_ptr<fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::DirectPatchDifferenceSurfCalculator<input_dtype,feature_dtype,annotation_dtype>(

         psx,
         psy,
         psz,
         luc
	   ));
  };

  auto entropygain_vec_t() -> std::vector<std::shared_ptr<fertilized::EntropyGain<float>>>;
  /**
* \brief Calculates the gain as difference of current entropy and the
* weighted sum of subgroup entropies.
*
* Works correctly up to a total sum of elements of
* min(numeric_limits<float>::max(), numeric_limits<input_dtype>::max())
* and the limitations of the selected entropy function.
* Speed optimized function that does no checks in release mode!
*
* \param input_dtype The datatype for counting class members. This might
* be a float if sample weights are used.
*
* \ingroup fertilizedgainsGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
* .
*
* -----
*/
  std::shared_ptr<fertilized::EntropyGain<float>>
  EntropyGain(

        const std::shared_ptr<typename fertilized::EntropyGain<float>::entropy_func_t> & entropy_function
    ) {
   return std::shared_ptr<fertilized::EntropyGain<float>>(
     new fertilized::EntropyGain<float>(

         entropy_function
	   ));
  };

  auto equaldistbagging_vec_t() -> std::vector<std::shared_ptr<fertilized::EqualDistBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief Equal distribution bagging.
*
* The samples are distributed equally amongst the trees. Each sample belongs
* to exactly one tree. Note that this behaviour destroys the max-margin
* property of decision forests.
*
* \ingroup fertilizedbaggingGroup
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
  std::shared_ptr<fertilized::EqualDistBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  EqualDistBagging(

    ) {
   return std::shared_ptr<fertilized::EqualDistBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::EqualDistBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

	   ));
  };

  auto featcalcparamset_vec_t() -> std::vector<std::shared_ptr<fertilized::FeatCalcParamSet>>;
  auto forest_vec_t() -> std::vector<std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
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
  std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  Forest(

        const unsigned int & max_tree_depth,
        const unsigned int & min_samples_at_leaf,
        const unsigned int & min_samples_at_node,
        const unsigned int & n_trees,
        const std::vector<std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> > & deciders,
        const std::vector<std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::leaf_man_t> > & leaf_managers,
        const std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::training_t> & training
    ) {
   return std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         max_tree_depth,
         min_samples_at_leaf,
         min_samples_at_node,
         n_trees,
         deciders,
         leaf_managers,
         training
	   ));
  };

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
  std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  ForestFromTrees(

        const std::vector<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::tree_ptr_t> & trees,
        const std::shared_ptr<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::training_t> & training
    ) {
   return std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         trees,
         training
	   ));
  };

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
  std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  CombineTrees(

        const std::vector<typename fertilized::Forest<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::tree_ptr_t> & trees
    ) {
   return std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         trees
	   ));
  };

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
  std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  ForestFromFile(

        std::string filename
    ) {
   return std::shared_ptr<fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Forest<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         filename
	   ));
  };

  auto houghleafmanager_vec_t() -> std::vector<std::shared_ptr<fertilized::HoughLeafManager<input_dtype,annotation_dtype>>>;
  /**
* \brief Stores the offset vectors for positive samples and their
* probabilities in the leafs.
*
* \ingroup fertilizedleafsGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - uint8_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::HoughLeafManager<input_dtype,annotation_dtype>>
  HoughLeafManager(

        const unsigned int & n_classes=2,
        const size_t & annot_dim=2
    ) {
   return std::shared_ptr<fertilized::HoughLeafManager<input_dtype,annotation_dtype>>(
     new fertilized::HoughLeafManager<input_dtype,annotation_dtype>(

         n_classes,
         annot_dim
	   ));
  };

  auto ibaggingstrategy_vec_t() -> std::vector<std::shared_ptr<fertilized::IBaggingStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  auto iboostingstrategy_vec_t() -> std::vector<std::shared_ptr<fertilized::IBoostingStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  auto idataprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::IDataProvider<input_dtype,annotation_dtype>>>;
  auto idecider_vec_t() -> std::vector<std::shared_ptr<fertilized::IDecider<input_dtype,feature_dtype,annotation_dtype>>>;
  auto ientropyfunction_vec_t() -> std::vector<std::shared_ptr<fertilized::IEntropyFunction<float>>>;
  auto iexecutionstrategy_vec_t() -> std::vector<std::shared_ptr<fertilized::IExecutionStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  auto ifeatureselectionprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::IFeatureSelectionProvider>>;
  auto iforestdataprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::IForestDataProvider<input_dtype,annotation_dtype>>>;
  auto igaincalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::IGainCalculator<float>>>;
  auto ileafmanager_vec_t() -> std::vector<std::shared_ptr<fertilized::ILeafManager<input_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  auto iregressioncalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::IRegressionCalculator<input_dtype>>>;
  auto isamplemanager_vec_t() -> std::vector<std::shared_ptr<fertilized::ISampleManager<input_dtype,annotation_dtype>>>;
  auto isurfacecalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::ISurfaceCalculator<input_dtype,feature_dtype,annotation_dtype>>>;
  auto ithresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::IThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  auto itraining_vec_t() -> std::vector<std::shared_ptr<fertilized::ITraining<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  auto inducedentropy_vec_t() -> std::vector<std::shared_ptr<fertilized::InducedEntropy<float>>>;
  /**
* \brief Computes the induced p entropy.
*
* Works correctly up to a total sum of elements of
* numeric_limits<input_dtype>::max().
*
* This is the induced p-metric of the vector of \f$n\f$ class probabilities
* and the point of maximum unorder (the vector with all entries
* \f$\frac{1}{n}\f$) in the n-dimensional space without applying the root.
* It is equal to the Gini-measure for \f$p=2\f$.
*
* The definition for \f$c\f$ classes:
* \f[\sum_{i=1}^{c} \left\Vert p_i - 0.5\right\Vert ^p\f].
*
* The differential entropy for a normal distribution with covariance
* matrix \f$\Sigma\f$ in \f$n\f$ dimensions is defined as:
* \f[\frac{1}{\sqrt{p^n}}\cdot\left(\sqrt{2\pi}^n\cdot\sqrt{\left|\Sigma\right|}\right)^{-(p-1)}\f]
*
* In the differential normal case, the most useful values for \f$p\f$ are
* very close to 1 (e.g. 1.00001)! \f$p=2\f$ is already equivalent to the
* infinite norm!
*
* \ingroup fertilizedimpuritiesGroup
*
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
* .
*
* -----
*/
  std::shared_ptr<fertilized::InducedEntropy<float>>
  InducedEntropy(

        const float & p
    ) {
   return std::shared_ptr<fertilized::InducedEntropy<float>>(
     new fertilized::InducedEntropy<float>(

         p
	   ));
  };

  auto linearregressioncalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::LinearRegressionCalculator<input_dtype>>>;
  /**
* \brief Calculator for linear regression.
*
* This regression calculator uses a linear combination of the input dimensions
* to predict the output value. Therefore it does not provide a constant prediction
* or a constant prediction covariance matrix.
* If there are multiple output values to be predicted, each output is produced
* using its own linear model.
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
*
* -----
*/
  std::shared_ptr<fertilized::LinearRegressionCalculator<input_dtype>>
  LinearRegressionCalculator(

        const bool & force_numerical_stability=1,
        const input_dtype & numerical_zero_threshold=static_cast<input_dtype>(-1)
    ) {
   return std::shared_ptr<fertilized::LinearRegressionCalculator<input_dtype>>(
     new fertilized::LinearRegressionCalculator<input_dtype>(

         force_numerical_stability,
         numerical_zero_threshold
	   ));
  };

  auto linearsurfacecalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>>>;
  /**
* \brief Calculates a feature as linear combination of inputs.
*
* \ingroup fertilizedfeaturesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; uint
* - uint8_t; uint
* - float; uint
* - float; float
* - double; double
* - double; uint
* .
*
* -----
*/
  std::shared_ptr<fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>>
  LinearSurfaceCalculator(

        const size_t & n_params_per_feat_sel,
        const size_t & n_comb_dims=2,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>>(
     new fertilized::LinearSurfaceCalculator<input_dtype,annotation_dtype>(

         n_params_per_feat_sel,
         n_comb_dims,
         random_seed
	   ));
  };

  auto localexecutionstrategy_vec_t() -> std::vector<std::shared_ptr<fertilized::LocalExecutionStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* Executes the training on the local machine.
*
* \ingroup fertilizedexecution_strategiesGroup
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
  std::shared_ptr<fertilized::LocalExecutionStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  LocalExecutionStrategy(

        const int & num_threads=1
    ) {
   return std::shared_ptr<fertilized::LocalExecutionStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::LocalExecutionStrategy<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         num_threads
	   ));
  };

  auto nobagging_vec_t() -> std::vector<std::shared_ptr<fertilized::NoBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* As the name suggests, performs no bagging and uses all samples for all trees.
*
* \ingroup fertilizedbaggingGroup
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
  std::shared_ptr<fertilized::NoBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  NoBagging(

    ) {
   return std::shared_ptr<fertilized::NoBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::NoBagging<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

	   ));
  };

  auto nocopypatchsamplemanager_vec_t() -> std::vector<std::shared_ptr<fertilized::NoCopyPatchSampleManager<input_dtype,annotation_dtype>>>;
  /**
* \brief A sample manager for Hough forests that limits the number of
* patches for one node, but does not copy anything but uses direct access
* tricks.
*
*
* \ingroup fertilizeddata_providersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - uint8_t; int16_t
* - uint8_t; uint
* .
*
* -----
*/
  std::shared_ptr<fertilized::NoCopyPatchSampleManager<input_dtype,annotation_dtype>>
  NoCopyPatchSampleManager(

        const std::vector<fertilized::Array<const input_dtype, 3, 3> > & images,
        const fertilized::Array<const annotation_dtype, 2, 2> & patch_descs,
        const size_t & n_positives,
        const size_t & patch_size_z,
        const size_t & patch_size_y,
        const size_t & patch_size_x,
        const bool & patches_luc=0
    ) {
   return std::shared_ptr<fertilized::NoCopyPatchSampleManager<input_dtype,annotation_dtype>>(
     new fertilized::NoCopyPatchSampleManager<input_dtype,annotation_dtype>(

         images,
         patch_descs,
         n_positives,
         patch_size_z,
         patch_size_y,
         patch_size_x,
         patches_luc
	   ));
  };

  auto objecttemplate_vec_t() -> std::vector<std::shared_ptr<fertilized::ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* Object template.
*
* After having described the object, add a section like the following
* to specify in which interfaces the object should be available, and, if it
* is templated, which instantiations of the object. The instantiations are
* ;-separated lists of the C++ types to use.
*
* To start and end this section, use exactly -----. End the lists with a dot
* and add an empty line after the last list. This is not due to our parser,
* but due to doxygen. It is required to get a meaningful rendering for the
* documentation.
*
* Use exactly the library template names `input_dtype`, `feature_dtype`,
* `annotation_dtype`, `leaf_return_dtype`, `forest_dtype` for your
* objects as necessary (you may omit unnecessary ones). If your class is 
* templated differently, only one possible
* template instantiation can be used for the interfaces. In that case, you
* have to specify this with a parser list "Soil type always:". You can find
* an example for this in impurities/shannonentropy.h.
*
* The specification of the "Serialization generation:" is important if you
* want to serialize your object and remain compatible to older versions
* of the library. Specify the number as the version number of the library
* in hundreds format (e.g., 1.00 as 100) plus one
* (e.g., if the current library version is 1.01, use 102). Your self-
* compiled library version with the additional object will be backwards
* compatible with all lower library versions. Increase the library version in
* the file 'global.h' to the same value!
*
* IMPORTANT: you HAVE to adjust the `Serializaton generation:` version number
* and the library version in 'global.h' to serialize your object and
* maintain backwards compatibility!
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
* .
* Serialization generation: 100
*
* -----
*/
  std::shared_ptr<fertilized::ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  ObjectTemplate(

        const unsigned int & example_param
    ) {
   return std::shared_ptr<fertilized::ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::ObjectTemplate<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         example_param
	   ));
  };

  auto patchsamplemanager_vec_t() -> std::vector<std::shared_ptr<fertilized::PatchSampleManager<input_dtype,annotation_dtype>>>;
  /**
* \brief Manages patch samples for the \ref SubsamlingDataProvider.
*
* Loads patches from the images on-demand and always has only
* the maximum allowed number of patches in memory. This exception
* might only be violated at leafs.
*
* \ingroup fertilizeddata_providersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - uint8_t; int16_t
* - uint8_t; uint
* .
*
* -----
*/
  std::shared_ptr<fertilized::PatchSampleManager<input_dtype,annotation_dtype>>
  PatchSampleManager(

        const std::vector<fertilized::Array<const input_dtype, 3, 3> > & images,
        const fertilized::Array<const annotation_dtype, 2, 2> & patch_descs,
        const size_t & n_positives,
        const size_t & patch_size_z,
        const size_t & patch_size_y,
        const size_t & patch_size_x,
        const bool & patches_luc=0
    ) {
   return std::shared_ptr<fertilized::PatchSampleManager<input_dtype,annotation_dtype>>(
     new fertilized::PatchSampleManager<input_dtype,annotation_dtype>(

         images,
         patch_descs,
         n_positives,
         patch_size_z,
         patch_size_y,
         patch_size_x,
         patches_luc
	   ));
  };

  auto quadraticsurfacecalculator_vec_t() -> std::vector<std::shared_ptr<fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>>;
  /**
* \brief Calculates a feature as the response value of a quadratic
* surface (see CriminisiShotton 2013, p. 15). Currently only supports two
* feature dimensions.
*
* \ingroup fertilizedfeaturesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; uint
* - uint8_t; uint
* - float; uint
* - float; float
* - double; uint
* - double; double
* .
*
* -----
*/
  std::shared_ptr<fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>
  QuadraticSurfaceCalculator(

        const size_t & n_params_per_feat_sel,
        const std::vector<float> & min_max_vals,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>>(
     new fertilized::QuadraticSurfaceCalculator<input_dtype,annotation_dtype>(

         n_params_per_feat_sel,
         min_max_vals,
         random_seed
	   ));
  };

  auto randomizedclassificationthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Optimizes a threshold by selecting the best of few random values.
*
* Supports only classification annotations (unsigned int) with annotation
* values in [0, ..., n_classes[.
* The threshold optimizer draws n_thresholds random values between
* the minimum and maximum observed feature value and returns the best
* one.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  RandomizedClassificationThresholdOptimizer(

        const size_t & n_thresholds,
        const size_t & n_classes,
        const std::shared_ptr<fertilized::IGainCalculator<float> > & gain_calculator,
        const float & gain_threshold=1E-7,
        const size_t & annotation_step=1,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::RandomizedClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         n_thresholds,
         n_classes,
         gain_calculator,
         gain_threshold,
         annotation_step,
         random_seed
	   ));
  };

  auto regressionleafmanager_vec_t() -> std::vector<std::shared_ptr<fertilized::RegressionLeafManager<input_dtype>>>;
  /**
* \brief Manages the leaf nodes of regression trees.
*
* This leaf manager creates leaf nodes and stores a probabilistic regression
* model at each leaf.
*
* \ingroup fertilizedleafsGroup
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
*
* -----
*/
  std::shared_ptr<fertilized::RegressionLeafManager<input_dtype>>
  RegressionLeafManager(

        const std::shared_ptr<fertilized::IFeatureSelectionProvider> & selection_provider,
        const size_t & n_valids_to_use,
        const std::shared_ptr<fertilized::IRegressionCalculator<input_dtype> > & regression_calculator,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > & entropy_function,
        const bool & use_fallback_constant_regression=0,
        const int & num_threads=1,
        const unsigned int & summary_mode=0
    ) {
   return std::shared_ptr<fertilized::RegressionLeafManager<input_dtype>>(
     new fertilized::RegressionLeafManager<input_dtype>(

         selection_provider,
         n_valids_to_use,
         regression_calculator,
         entropy_function,
         use_fallback_constant_regression,
         num_threads,
         summary_mode
	   ));
  };

  auto regressionthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>>>;
  /**
* \brief Optimizes the threshold for splitting a dataset, to ensure optimal
* regression results on the splits.
*
* This threshold optimizer draws n_thresholds random values between
* the minimum and maximum observed feature value and returns the best
* one.
* Multiple annotations (and therefore multiple output regression) are allowed.
* The splits are evaluated using a provided regression calculator.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float; float
* - double; double
* .
*
* -----
*
*/
  std::shared_ptr<fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>>
  RegressionThresholdOptimizer(

        const size_t & n_thresholds,
        const std::shared_ptr<fertilized::IRegressionCalculator<input_dtype> > & regression_calculator,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > & entropy_function,
        const float & gain_threshold=1E-7,
        const size_t & annotation_step=1,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>>(
     new fertilized::RegressionThresholdOptimizer<input_dtype,feature_dtype>(

         n_thresholds,
         regression_calculator,
         entropy_function,
         gain_threshold,
         annotation_step,
         random_seed
	   ));
  };

  auto renyientropy_vec_t() -> std::vector<std::shared_ptr<fertilized::RenyiEntropy<float>>>;
  /**
* \brief Computes the Renyi entropy.
*
* Works correctly up to a total sum of elements of
* numeric_limits<input_dtype>::max().
*
* This is the Renyi entropy, as introduced by Alfred Renyi
* (see http://en.wikipedia.org/wiki/R%C3%A9nyi_entropy).
*
* \ingroup fertilizedimpuritiesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
* .
*
* -----
*/
  std::shared_ptr<fertilized::RenyiEntropy<float>>
  RenyiEntropy(

        const float & alpha
    ) {
   return std::shared_ptr<fertilized::RenyiEntropy<float>>(
     new fertilized::RenyiEntropy<float>(

         alpha
	   ));
  };

  auto samme_vec_t() -> std::vector<std::shared_ptr<fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief SAMME boosting algorithm implementation
*
* Implements the SAMME boosting algorithm proposed by J. Zhu, H. Zou,
* S. Rosset and T. Hastie ("Multi-class AdaBoost", 2009).
*
* One can set the learning rate which specifies the contribution of each
* classifier.
*
* Output when using BoostingLeafManager is
* estimator_probability*estimator_weight.
*
* \ingroup fertilizedboostingGroup
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
* .
* Serialization generation: 101
*
* -----
*/
  std::shared_ptr<fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  Samme(

        float learning_rate=1
    ) {
   return std::shared_ptr<fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Samme<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         learning_rate
	   ));
  };

  auto samme_r_vec_t() -> std::vector<std::shared_ptr<fertilized::Samme_R<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
  /**
* \brief SAMME.R real boosting algorithm implementation
*
* Implements the SAMME.R real boosting algorithm proposed by J. Zhu,
* H. Zou, S. Rosset and T. Hastie ("Multi-class AdaBoost", 2009).
*
* One can set the learning rate which specifies the contribution of
* each classifier.
*
* Output when using BoostingLeafManager is
* \f$log(p_k^m(x))-1/K*sum_k(log(p_k^m(x)))\f$.
*
* with \f$x\f$ the sample to classify, \f$K\f$ the number of classes,
* \f$k\f$ the classIndex, \f$m\f$ the estimatorIndex and \f$p\f$ the
* estimator probability.
*
* \ingroup fertilizedboostingGroup
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
* .
* Serialization generation: 101
*
* -----
*/
  std::shared_ptr<fertilized::Samme_R<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  Samme_R(

        float learning_rate=1
    ) {
   return std::shared_ptr<fertilized::Samme_R<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Samme_R<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         learning_rate
	   ));
  };

  auto sample_vec_t() -> std::vector<std::shared_ptr<fertilized::Sample<input_dtype,annotation_dtype>>>;
  auto shannonentropy_vec_t() -> std::vector<std::shared_ptr<fertilized::ShannonEntropy<float>>>;
  /**
* \brief Computes the classical Shannon-Entropy.
*
* Works correctly up to a total sum of elements of
* numeric_limits<input_dtype>::max().
*
* For classes \f$C={c_1, \ldots, c_n}\f$, the Shannon entropy is defined as
* \f[-\sum_{c\in C}p_z\cdot \log_2 p_z.\f]
*
* The differential Shannon entropy for a normal distribution with covariance
* matrix \f$\Sigma\f$ in \f$n\f$ dimensions is defined as
* \f[\frac{1}{2}\log\left((2\pi e)^n\left|\Sigma\right|\right).\f]
*
* \ingroup fertilizedimpuritiesGroup
*
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
* .
* 
* -----
*/
  std::shared_ptr<fertilized::ShannonEntropy<float>>
  ShannonEntropy(

    ) {
   return std::shared_ptr<fertilized::ShannonEntropy<float>>(
     new fertilized::ShannonEntropy<float>(

	   ));
  };

  auto standardfeatureselectionprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::StandardFeatureSelectionProvider>>;
  /**
* \brief This selection provider generates random selection combinations.
*
* It may be seeded for reproducible results. It can be configured to only
* use a part of the available data dimensions. It only uses then the first
* that are registered as used.
*
*
* \ingroup fertilizedfeaturesGroup
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
  std::shared_ptr<fertilized::StandardFeatureSelectionProvider>
  StandardFeatureSelectionProvider(

        const size_t & n_selections_per_node,
        const size_t & selection_dimension,
        const size_t & how_many_available,
        size_t max_to_use=0,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::StandardFeatureSelectionProvider>(
     new fertilized::StandardFeatureSelectionProvider(

         n_selections_per_node,
         selection_dimension,
         how_many_available,
         max_to_use,
         random_seed
	   ));
  };

  auto subsamplingdataprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::SubsamplingDataProvider<input_dtype,annotation_dtype>>>;
  /**
* \brief Uses at maximum a certain amount of samples for node optimization.
*
* Tracks the loaded samples during training and adds new samples if possible.
* For leafs, all samples are loaded, even if its more than the maximum
* number of samples for split optimization.
*
* \ingroup fertilizeddata_providersGroup
*
* Can only be used for DFS (!!) for efficiency reasons.
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - uint8_t; int16_t
* - uint8_t; uint
* .
*
* -----
*/
  std::shared_ptr<fertilized::SubsamplingDataProvider<input_dtype,annotation_dtype>>
  SubsamplingDataProvider(

        const size_t & max_samples_per_node,
        std::shared_ptr<fertilized::ISampleManager<input_dtype, annotation_dtype> > sample_manager,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::SubsamplingDataProvider<input_dtype,annotation_dtype>>(
     new fertilized::SubsamplingDataProvider<input_dtype,annotation_dtype>(

         max_samples_per_node,
         sample_manager,
         random_seed
	   ));
  };

  auto thresholddecider_vec_t() -> std::vector<std::shared_ptr<fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief A classifier manager for weak classifiers with a filter function,
* a feature calculation function and a thresholding.
*
* The classifier design is heavily inspired by "Decision Forests for
* Classification, Regression, Density Estimation, Manifold Learning and
* Semi-Supervised Learning" (Criminisi, Shotton and Konukoglu, 2011).
* With their definition, node classifier parameters \f$\theta\f$ can
* be split into three parts:
*  - \f$\phi\f$: a filter function that selects relevant features,
*  - \f$\psi\f$: parameters of a function that combines the feature values
*                to a single scalar,
*  - \f$\tau\f$: thresholding parameters for the calculated scalar.
*
* With this model, a decision can be made at each node based on whether the
* calculated scalar lies withing the thresholding bounds.
*
* \ingroup fertilizeddecidersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* - float; float; float
* - double; double; double
* .
*
* -----
*/
  std::shared_ptr<fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>
  ThresholdDecider(

        const std::shared_ptr<fertilized::IFeatureSelectionProvider> & selection_provider,
        const std::shared_ptr<typename fertilized::ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>::feat_calc_t> & feature_calculator,
        const std::shared_ptr<typename fertilized::ThresholdDecider<input_dtype, feature_dtype, annotation_dtype>::thresh_opt_t> & threshold_optimizer,
        const size_t & n_valid_features_to_use=0,
        const int & num_threads=1,
        const bool & use_hough_heuristic=0,
        const float & hough_heuristic_ratio=0.05,
        const unsigned int & hough_heuristic_maxd=0,
        const bool & allow_early_stopping=0
    ) {
   return std::shared_ptr<fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::ThresholdDecider<input_dtype,feature_dtype,annotation_dtype>(

         selection_provider,
         feature_calculator,
         threshold_optimizer,
         n_valid_features_to_use,
         num_threads,
         use_hough_heuristic,
         hough_heuristic_ratio,
         hough_heuristic_maxd,
         allow_early_stopping
	   ));
  };

  auto trainingaction_vec_t() -> std::vector<std::shared_ptr<fertilized::TrainingAction<input_dtype,annotation_dtype>>>;
  /**
* Represents one training action.
*
* -----
* Available in:
* - C++
* .
* Instantiations:
* - int; uint
* - float; uint
* - double; uint
* - uint8_t; uint
* - uint8_t; int16_t
* - float; float
* - double; double
* .
*
* -----
*/
  std::shared_ptr<fertilized::TrainingAction<input_dtype,annotation_dtype>>
  TrainingAction(

        const size_t & tree_id,
        const fertilized::CompletionLevel & completeness,
        const fertilized::action_type & action,
        const std::shared_ptr<typename fertilized::TrainingAction<input_dtype, annotation_dtype>::dprov_t> & data_provider
    ) {
   return std::shared_ptr<fertilized::TrainingAction<input_dtype,annotation_dtype>>(
     new fertilized::TrainingAction<input_dtype,annotation_dtype>(

         tree_id,
         completeness,
         action,
         data_provider
	   ));
  };

  auto tree_vec_t() -> std::vector<std::shared_ptr<fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>>;
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
  std::shared_ptr<fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  Tree(

        const unsigned int & max_depth,
        const unsigned int & min_samples_at_leaf,
        const unsigned int & min_samples_at_node,
        const std::shared_ptr<typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::dec_t> & decider,
        const std::shared_ptr<typename fertilized::Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>::leaf_man_t> & leaf_manager
    ) {
   return std::shared_ptr<fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         max_depth,
         min_samples_at_leaf,
         min_samples_at_node,
         decider,
         leaf_manager
	   ));
  };

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
  std::shared_ptr<fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>
  TreeFromFile(

        std::string filename
    ) {
   return std::shared_ptr<fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>>(
     new fertilized::Tree<input_dtype,feature_dtype,annotation_dtype,leaf_return_dtype,forest_return_dtype>(

         filename
	   ));
  };

  auto tsallisentropy_vec_t() -> std::vector<std::shared_ptr<fertilized::TsallisEntropy<float>>>;
  /**
* \brief Computes the Tsallis entropy.
*
* Works correctly up to a total sum of elements of
* numeric_limits<input_dtype>::max().
*
* This is the Tsallis entropy, as introduced by Constantino Tsallis
* (see http://en.wikipedia.org/wiki/Tsallis_entropy).
*
*
* \ingroup fertilizedimpuritiesGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float
* - uint
* .
* Soil type always:
* - float
*
* -----
*/
  std::shared_ptr<fertilized::TsallisEntropy<float>>
  TsallisEntropy(

        const float & q
    ) {
   return std::shared_ptr<fertilized::TsallisEntropy<float>>(
     new fertilized::TsallisEntropy<float>(

         q
	   ));
  };

  auto twosideclassificationthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::TwoSideClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Optimizes two sided classifcation thresholds very efficiently.
*
* Supports only classification annotations (unsigned int) with annotation
* values in {0, ..., n_classes - 1}.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::TwoSideClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  TwoSideClassificationThresholdOptimizer(

        const bool & use_fast_search_approximation,
        const size_t & n_classes,
        const std::shared_ptr<fertilized::IGainCalculator<float> > & gain_calculator,
        const float & gain_threshold=1E-7,
        const size_t annotation_step=1
    ) {
   return std::shared_ptr<fertilized::TwoSideClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::TwoSideClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         use_fast_search_approximation,
         n_classes,
         gain_calculator,
         gain_threshold,
         annotation_step
	   ));
  };

  auto unchangeddataprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::UnchangedDataProvider<input_dtype,annotation_dtype>>>;
  /**
* \brief Uses the provided data unchanged throughout the training.
*
* It builds its sample database from two pointer on memory arrays with
* data and annotations. Both must be provided in contiguous layout. The
* data (but not the annotations!) can be provided row- or column-wise.
* Column-wise layout is to be preferred, since it has more locality for 
* most optimization processes.
*
* The annotations MUST always be provided in row major order, independent
* of the provided value for \ref column_wise.
*
*
* \ingroup fertilizeddata_providersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float; uint
* - int; uint
* - uint8_t; uint
* - uint8_t; int16_t
* - double; uint
* - double; double
* - float; float
* .
* 
* -----
*/
  std::shared_ptr<fertilized::UnchangedDataProvider<input_dtype,annotation_dtype>>
  UnchangedDataProvider(

        const fertilized::Array<const input_dtype, 2, 2> & data,
        const fertilized::Array<const annotation_dtype, 2, 2> & annotations
    ) {
   return std::shared_ptr<fertilized::UnchangedDataProvider<input_dtype,annotation_dtype>>(
     new fertilized::UnchangedDataProvider<input_dtype,annotation_dtype>(

         data,
         annotations
	   ));
  };

  auto unchangedfdataprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::UnchangedFDataProvider<input_dtype,annotation_dtype>>>;
  /**
* \brief Uses unchanged data providers for each tree.
*
*
* \ingroup fertilizeddata_providersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - float; uint
* - int; uint
* - uint8_t; uint
* - uint8_t; int16_t
* - double; uint
* - double; double
* - float; float
* .
* 
* -----
*/
  std::shared_ptr<fertilized::UnchangedFDataProvider<input_dtype,annotation_dtype>>
  UnchangedFDataProvider(

        const fertilized::Array<const input_dtype, 2, 2> & data_array,
        const fertilized::Array<const annotation_dtype, 2, 2> & annotation_array
    ) {
   return std::shared_ptr<fertilized::UnchangedFDataProvider<input_dtype,annotation_dtype>>(
     new fertilized::UnchangedFDataProvider<input_dtype,annotation_dtype>(

         data_array,
         annotation_array
	   ));
  };

  auto varianceclassificationthresholdoptimizer_vec_t() -> std::vector<std::shared_ptr<fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>>;
  /**
* \brief Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.
*
* The annotations are assumed to be a class label followed by its offset
* values. Since all these values must be of the same datatype, the only supported type
* is (signed) int in this case (to allow for negative offsets). The class labels
* must still be in [0; n_classes - 1].
*
* This threshold optimizer draws n_thresholds random values between
* the minimum and maximum observed feature value and returns the best
* one.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  VarianceClassificationThresholdOptimizer(

        const size_t & n_thresholds,
        const size_t & n_classes=2,
        const size_t & offset_dim=2,
        const float & gain_threshold=0,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         n_thresholds,
         n_classes,
         offset_dim,
         gain_threshold,
         random_seed
	   ));
  };

  /**
* \brief Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.
*
* The annotations are assumed to be a class label followed by its offset
* values. Since all these values must be of the same datatype, the only supported type
* is (signed) int in this case (to allow for negative offsets). The class labels
* must still be in [0; n_classes - 1].
*
* This threshold optimizer draws n_thresholds random values between
* the minimum and maximum observed feature value and returns the best
* one.
*
* \ingroup fertilizedthreshold_optimizersGroup
*
* -----
* Available in:
* - C++
* - Python
* - Matlab
* .
* Instantiations:
* - int; int; uint
* - int; float; uint
* - float; int; uint
* - uint8_t; int; uint
* - uint8_t; uint8_t; uint
* - uint8_t; float; uint
* - uint8_t; int16_t; uint
* - float; float; uint
* - double; double; uint
* - uint8_t; int16_t; int16_t
* .
*
* -----
*/
  std::shared_ptr<fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>
  VarianceClassificationThresholdOptimizerWEntropy(

        const size_t & n_thresholds,
        const size_t & n_classes,
        const size_t & offset_dim,
        const std::shared_ptr<fertilized::IEntropyFunction<float> > & ent_calc,
        const float & gain_threshold=1,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>>(
     new fertilized::VarianceClassificationThresholdOptimizer<input_dtype,feature_dtype,annotation_dtype>(

         n_thresholds,
         n_classes,
         offset_dim,
         ent_calc,
         gain_threshold,
         random_seed
	   ));
  };

  auto volumefeatureselectionprovider_vec_t() -> std::vector<std::shared_ptr<fertilized::VolumeFeatureSelectionProvider>>;
  /**
* \brief This selection provider generates random selection combinations
* from a 3D feature volume.
*
* It may be seeded for reproducible results.
*
*
* \ingroup fertilizedfeaturesGroup
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
  std::shared_ptr<fertilized::VolumeFeatureSelectionProvider>
  VolumeFeatureSelectionProvider(

        const size_t & selection_dimension,
        const size_t & size_x,
        const size_t & size_y,
        const size_t & size_z,
        const size_t & how_many_per_node,
        const unsigned int & random_seed=1
    ) {
   return std::shared_ptr<fertilized::VolumeFeatureSelectionProvider>(
     new fertilized::VolumeFeatureSelectionProvider(

         selection_dimension,
         size_x,
         size_y,
         size_z,
         how_many_per_node,
         random_seed
	   ));
  };

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
  std::shared_ptr<fertilized::Forest<input_dtype , input_dtype , uint , std::vector<float> , std::vector<float> >> StandardClassificationForest(

        const unsigned int & n_classes,
        const size_t & n_features,
        const unsigned int & max_depth=0,
        const size_t & test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=0,
        const unsigned int & n_trees=10,
        const unsigned int & min_samples_per_leaf=1,
        const unsigned int & min_samples_per_split=2,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="induced",
        const float & entropy_p1=2,
        const unsigned int threshold_optimization_threads=1
    ) {
    return fertilized::construct_classifier_forest<input_dtype>(

         n_classes,
         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         n_trees,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         threshold_optimization_threads
       );
    };

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
  std::shared_ptr<fertilized::Tree<input_dtype , input_dtype , uint , std::vector<float> , std::vector<float> >> StandardClassificationTree(

        const unsigned int & n_classes,
        const size_t & n_features,
        unsigned int max_depth=0,
        size_t test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=0,
        const unsigned int & min_samples_per_leaf=1,
        const unsigned int & min_samples_per_split=2,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="induced",
        const float & entropy_p1=2,
        const unsigned int threshold_optimization_threads=1
    ) {
    return fertilized::construct_classifier_tree<input_dtype>(

         n_classes,
         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         threshold_optimization_threads
       );
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
  std::shared_ptr<fertilized::Forest<input_dtype , input_dtype , input_dtype , std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , float> >>> FastRegressionForest(

        const size_t & n_features,
        unsigned int max_depth=0,
        size_t test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=10,
        const size_t & n_trees=10,
        const unsigned int & min_samples_per_leaf=3,
        const unsigned int & min_samples_per_split=6,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="shannon",
        const float & entropy_p1=2,
        const float & numerical_zero_threshold=-1,
        const unsigned int & threshold_optimization_threads=1,
        const unsigned int & summary_mode=0
    ) {
    return fertilized::construct_fast_regression_forest<input_dtype>(

         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         n_trees,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         numerical_zero_threshold,
         threshold_optimization_threads,
         summary_mode
       );
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
  std::shared_ptr<fertilized::Tree<input_dtype , input_dtype , input_dtype , std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , float> >>> FastRegressionTree(

        const size_t & n_features,
        unsigned int max_depth=0,
        size_t test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=10,
        const unsigned int & min_samples_per_leaf=3,
        const unsigned int & min_samples_per_split=6,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="shannon",
        const float & entropy_p1=2,
        const float & numerical_zero_threshold=-1,
        const unsigned int & threshold_optimization_threads=1,
        const unsigned int & summary_mode=0
    ) {
    return fertilized::construct_fast_regression_tree<input_dtype>(

         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         numerical_zero_threshold,
         threshold_optimization_threads,
         summary_mode
       );
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
  std::shared_ptr<fertilized::Tree<input_dtype , feature_dtype , annotation_dtype , std::pair<float , std::shared_ptr<std::vector<annotation_dtype> >> , std::vector<std::pair<float , std::shared_ptr<std::vector<annotation_dtype> >> >>> StandardHoughTree(

        const std::vector<size_t> & patch_dimensions,
        const size_t & n_thresholds_per_split,
        const size_t & n_splits_per_node,
        unsigned int max_depth,
        const std::vector<fertilized::uint> & min_sample_counts,
        const unsigned int & random_seed,
        const std::vector<float> & min_gain_thresholds,
        const bool & patch_annot_luc=0,
        const bool & allow_redraw=1,
        const unsigned int & num_threads=1,
        const std::vector<std::string> & entropy_names=_DEFAULT_ENTROPY_VEC_2,
        const std::vector<float> & entropy_p1=_DEFAULT_ENTROPY_P1_2,
        const bool & use_hough_heuristic=1,
        const float & hough_heuristic_ratio=0.05,
        unsigned int hough_heuristic_maxd=0
    ) {
    return fertilized::construct_hough_tree<input_dtype,feature_dtype,annotation_dtype>(

         patch_dimensions,
         n_thresholds_per_split,
         n_splits_per_node,
         max_depth,
         min_sample_counts,
         random_seed,
         min_gain_thresholds,
         patch_annot_luc,
         allow_redraw,
         num_threads,
         entropy_names,
         entropy_p1,
         use_hough_heuristic,
         hough_heuristic_ratio,
         hough_heuristic_maxd
       );
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
  std::shared_ptr<fertilized::Forest<input_dtype , input_dtype , input_dtype , std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , float> >>> StandardRegressionForest(

        const size_t & n_features,
        unsigned int max_depth=0,
        size_t test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=10,
        const size_t & n_trees=10,
        const unsigned int & min_samples_per_leaf=3,
        const unsigned int & min_samples_per_split=6,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="shannon",
        const float & entropy_p1=2,
        const float & numerical_zero_threshold=-1,
        const unsigned int & threshold_optimization_threads=1,
        const unsigned int & summary_mode=0
    ) {
    return fertilized::construct_regression_forest<input_dtype>(

         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         n_trees,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         numerical_zero_threshold,
         threshold_optimization_threads,
         summary_mode
       );
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
  std::shared_ptr<fertilized::Tree<input_dtype , input_dtype , input_dtype , std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype> > , std::shared_ptr<std::vector<input_dtype> >> , float> >>> StandardRegressionTree(

        const size_t & n_features,
        unsigned int max_depth=0,
        size_t test_n_features_per_node=0,
        const size_t & n_thresholds_per_feature=10,
        const unsigned int & min_samples_per_leaf=3,
        const unsigned int & min_samples_per_split=6,
        const float & min_gain_threshold=1E-7,
        const bool & allow_redraw=1,
        const unsigned int & random_seed=1,
        std::string entropy_name="shannon",
        const float & entropy_p1=2,
        const float & numerical_zero_threshold=-1,
        const unsigned int & threshold_optimization_threads=1,
        const unsigned int & summary_mode=0
    ) {
    return fertilized::construct_regression_tree<input_dtype>(

         n_features,
         max_depth,
         test_n_features_per_node,
         n_thresholds_per_feature,
         min_samples_per_leaf,
         min_samples_per_split,
         min_gain_threshold,
         allow_redraw,
         random_seed,
         entropy_name,
         entropy_p1,
         numerical_zero_threshold,
         threshold_optimization_threads,
         summary_mode
       );
    };

  /**
* Extract the Hough forest features. If `full` is set, uses the 
* 32 feature channels used by Juergen Gall in his original publications,
* else use 15 feature channels as used by Matthias Dantone.
*
* The image must be in OpenCV (BGR) channel format!
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
* \param image Array<uint8_t>, row-major contiguous
*   The source image.
* \param full bool
*   Whether to return the full feature set (32 layers) or not (15 layers).
*   Default: false.
*/
  Array<uint8_t , 3 , 3> extract_hough_forest_features(

        const fertilized::Array<uint8_t const, 3, 3> & image,
        const bool & full=0
    ) {
    return fertilized::extract_hough_forest_features(

         image,
         full
       );
    };

  };
}  // namespace fertilized
#endif  // FERTILIZED_SOIL_H_