
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_FORESTS_H_
#define MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_FORESTS_H_

#include "global.h"
#include "mex.h"

#ifdef __cplusplus
extern "C"
{
#endif


  DllExport void * StandardClassificationForest_i (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

  DllExport void * StandardClassificationForest_f (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

  DllExport void * StandardClassificationForest_d (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

  DllExport void * StandardClassificationForest_uint8 (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);


  DllExport void * StandardRegressionForest_f (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        size_t n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        float numerical_zero_threshold,
        unsigned int threshold_optimization_threads,
        unsigned int summary_mode
);

  DllExport void * StandardRegressionForest_d (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        size_t n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        float numerical_zero_threshold,
        unsigned int threshold_optimization_threads,
        unsigned int summary_mode
);


  DllExport void * FastRegressionForest_f (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        size_t n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        float numerical_zero_threshold,
        unsigned int threshold_optimization_threads,
        unsigned int summary_mode
);

  DllExport void * FastRegressionForest_d (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        size_t n_trees,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        float numerical_zero_threshold,
        unsigned int threshold_optimization_threads,
        unsigned int summary_mode
);
#ifdef __cplusplus
}
#endif 

#endif  // MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_FORESTS_H_