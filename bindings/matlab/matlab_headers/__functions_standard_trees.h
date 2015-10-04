
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_TREES_H_
#define MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_TREES_H_

#include "global.h"
#include "mex.h"

#ifdef __cplusplus
extern "C"
{
#endif


   void * StandardClassificationTree_i (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

   void * StandardClassificationTree_f (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

   void * StandardClassificationTree_d (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);

   void * StandardClassificationTree_uint8 (

        unsigned int n_classes,
        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
        unsigned int min_samples_per_leaf,
        unsigned int min_samples_per_split,
        float min_gain_threshold,
        int allow_redraw,
        unsigned int random_seed,
        char* entropy_name,
        float entropy_p1,
        unsigned int threshold_optimization_threads
);


   void * FastRegressionTree_f (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
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

   void * FastRegressionTree_d (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
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


   void * StandardHoughTree_uint8_int16_int16 (

        mxArray * patch_dimensions,
        size_t n_thresholds_per_split,
        size_t n_splits_per_node,
        unsigned int max_depth,
        mxArray * min_sample_counts,
        unsigned int random_seed,
        mxArray * min_gain_thresholds,
        int patch_annot_luc,
        int allow_redraw,
        unsigned int num_threads,
        void * entropy_names,
        mxArray * entropy_p1,
        int use_hough_heuristic,
        float hough_heuristic_ratio,
        unsigned int hough_heuristic_maxd
);


   void * StandardRegressionTree_f (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
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

   void * StandardRegressionTree_d (

        size_t n_features,
        unsigned int max_depth,
        size_t test_n_features_per_node,
        size_t n_thresholds_per_feature,
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

#endif  // MATFERTILIZED_MATLAB_HEADERS___FUNCTIONS_STANDARD_TREES_H_