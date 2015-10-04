
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */#pragma once
#ifndef FERTILIZED_FERTILIZED_H_
#define FERTILIZED_FERTILIZED_H_

/// \defgroup ndarrayPackageGroup ndarray

/// \defgroup fertilizedbaggingGroup Bagging

/// \defgroup fertilizedboostingGroup Boosting

/// \defgroup fertilizeddata_providersGroup Data Providers

/// \defgroup fertilizeddecidersGroup Deciders

/// \defgroup fertilizedexecution_strategiesGroup Execution Strategies

/// \defgroup fertilizedfeaturesGroup Features

/// \defgroup fertilizedgainsGroup Gains

/// \defgroup fertilizedimpuritiesGroup Impurity Measures

/// \defgroup fertilizedleafsGroup Leafs

/// \defgroup fertilizedthreshold_optimizersGroup Threshold Optimizers

/// \defgroup fertilizedtrainingsGroup Trainings

#include "./global.h"
#include "./ndarray.h"
#include "./bagging/equaldistbagging.h"
#include "./bagging/ibaggingstrategy.h"
#include "./bagging/nobagging.h"
#include "./boosting/adaboost.h"
#include "./boosting/iboostingstrategy.h"
#include "./boosting/samme.h"
#include "./boosting/samme_r.h"
#include "./data_providers/idataprovider.h"
#include "./data_providers/iforestdataprovider.h"
#include "./data_providers/isamplemanager.h"
#include "./data_providers/nocopypatchsamplemanager.h"
#include "./data_providers/patchsamplemanager.h"
#include "./data_providers/patchtoimagecoordinatetransformer.h"
#include "./data_providers/sample.h"
#include "./data_providers/subsamplingdataprovider.h"
#include "./data_providers/unchangeddataprovider.h"
#include "./data_providers/unchangedfdataprovider.h"
#include "./deciders/idecider.h"
#include "./deciders/thresholddecider.h"
#include "./execution_strategies/iexecutionstrategy.h"
#include "./execution_strategies/localexecutionstrategy.h"
#include "./execution_strategies/trainingaction.h"
#include "./feature_extraction/dnnfeatureextractor.h"
#include "./feature_extraction/feature_extraction.h"
#include "./feature_extraction/feature_extraction_vision.h"
#include "./feature_extraction/hog_extractor.h"
#include "./features/_issubsdprov_dpdsc.h"
#include "./features/alignedsurfacecalculator.h"
#include "./features/differencesurfacecalculator.h"
#include "./features/directpatchdifferencesurfcalculator.h"
#include "./features/featcalcparamset.h"
#include "./features/ifeatureselectiongenerator.h"
#include "./features/ifeatureselectionprovider.h"
#include "./features/isurfacecalculator.h"
#include "./features/linearsurfacecalculator.h"
#include "./features/quadraticsurfacecalculator.h"
#include "./features/standardfeatureselectiongenerator.h"
#include "./features/standardfeatureselectionprovider.h"
#include "./features/volumefeatureselectiongenerator.h"
#include "./features/volumefeatureselectionprovider.h"
#include "./forest.h"
#include "./gains/entropygain.h"
#include "./gains/igaincalculator.h"
#include "./impurities/classificationerror.h"
#include "./impurities/ientropyfunction.h"
#include "./impurities/inducedentropy.h"
#include "./impurities/renyientropy.h"
#include "./impurities/shannonentropy.h"
#include "./impurities/tsallisentropy.h"
#include "./leafs/boostingleafmanager.h"
#include "./leafs/classificationleafmanager.h"
#include "./leafs/houghleafmanager.h"
#include "./leafs/ileafmanager.h"
#include "./leafs/regressionleafmanager.h"
#include "./objecttemplate.h"
#include "./regression/constantregressioncalculator.h"
#include "./regression/iregressioncalculator.h"
#include "./regression/linearregressioncalculator.h"
#include "./standard_forests.h"
#include "./standard_trees.h"
#include "./threshold_optimizers/alternatingthresholdoptimizer.h"
#include "./threshold_optimizers/classificationthresholdoptimizer.h"
#include "./threshold_optimizers/feature_value_selection.h"
#include "./threshold_optimizers/ithresholdoptimizer.h"
#include "./threshold_optimizers/randomizedclassificationthresholdoptimizer.h"
#include "./threshold_optimizers/regressionthresholdoptimizer.h"
#include "./threshold_optimizers/twosideclassificationthresholdoptimizer.h"
#include "./threshold_optimizers/varianceclassificationthresholdoptimizer.h"
#include "./trainings/boostedtraining.h"
#include "./trainings/classictraining.h"
#include "./trainings/itraining.h"
#include "./tree.h"
#include "./util/argsort.h"
#include "./util/checks.h"
#include "./util/exponentials.h"
#include "./util/mat.h"
#include "./util/sampling.h"
#include "./soil.h"

#endif  // FERTILIZED_FERTILIZED_H_