
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_THRESHOLD_OPTIMIZERS_H_
#define MATFERTILIZED_MATLAB_HEADERS_THRESHOLD_OPTIMIZERS_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getAlternatingThresholdOptimizer_f_f_f (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_d_d_d (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_i_i_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_i_f_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_f_i_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_uint8_i_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_uint8_uint8_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_uint8_f_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_uint8_int16_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_f_f_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_d_d_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);
     void * getAlternatingThresholdOptimizer_uint8_int16_int16 (

        void * opt1,
        void * opt2,
        unsigned int random_seed
);


     int eqAlternatingThresholdOptimizer_f_f_f (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_d_d_d (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_i_f_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_f_i_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_uint8_i_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_uint8_f_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_f_f_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
);
     int eqAlternatingThresholdOptimizer_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_AlternatingThresholdOptimizer_f_f_f(void *ptr);
     void delete_AlternatingThresholdOptimizer_d_d_d(void *ptr);
     void delete_AlternatingThresholdOptimizer_i_i_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_i_f_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_f_i_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_uint8_i_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_uint8_uint8_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_uint8_f_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_uint8_int16_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_f_f_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_d_d_uint(void *ptr);
     void delete_AlternatingThresholdOptimizer_uint8_int16_int16(void *ptr);


     void * getClassificationThresholdOptimizer_i_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_i_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_f_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_uint8_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_uint8_uint8_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_uint8_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_uint8_int16_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_f_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_d_d_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getClassificationThresholdOptimizer_uint8_int16_int16 (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);


     int eqClassificationThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_i_f_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_f_i_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_uint8_i_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_uint8_f_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_f_f_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
);
     int eqClassificationThresholdOptimizer_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_ClassificationThresholdOptimizer_i_i_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_i_f_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_f_i_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_uint8_i_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_uint8_uint8_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_uint8_f_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_uint8_int16_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_f_f_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_d_d_uint(void *ptr);
     void delete_ClassificationThresholdOptimizer_uint8_int16_int16(void *ptr);


     void * getRandomizedClassificationThresholdOptimizer_i_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_i_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_f_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_uint8_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_uint8_uint8_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_uint8_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_uint8_int16_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_f_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_d_d_uint (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRandomizedClassificationThresholdOptimizer_uint8_int16_int16 (

        size_t n_thresholds,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);


     int eqRandomizedClassificationThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_i_f_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_f_i_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_uint8_i_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_uint8_f_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_f_f_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
);
     int eqRandomizedClassificationThresholdOptimizer_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_RandomizedClassificationThresholdOptimizer_i_i_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_i_f_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_f_i_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_uint8_i_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_uint8_uint8_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_uint8_f_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_uint8_int16_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_f_f_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_d_d_uint(void *ptr);
     void delete_RandomizedClassificationThresholdOptimizer_uint8_int16_int16(void *ptr);


     void * getRegressionThresholdOptimizer_f_f (

        size_t n_thresholds,
        void * regression_calculator,
        void * entropy_function,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);
     void * getRegressionThresholdOptimizer_d_d (

        size_t n_thresholds,
        void * regression_calculator,
        void * entropy_function,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
);


     int eqRegressionThresholdOptimizer_f_f (void *__instance,

        void * rhs
);
     int eqRegressionThresholdOptimizer_d_d (void *__instance,

        void * rhs
);
     void delete_RegressionThresholdOptimizer_f_f(void *ptr);
     void delete_RegressionThresholdOptimizer_d_d(void *ptr);


     void * getTwoSideClassificationThresholdOptimizer_i_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_i_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_f_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_uint8_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_uint8_uint8_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_uint8_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_uint8_int16_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_f_f_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_d_d_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);
     void * getTwoSideClassificationThresholdOptimizer_uint8_int16_int16 (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
);


     int eqTwoSideClassificationThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_i_f_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_f_i_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_uint8_i_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_uint8_f_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_f_f_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
);
     int eqTwoSideClassificationThresholdOptimizer_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_TwoSideClassificationThresholdOptimizer_i_i_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_i_f_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_f_i_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_uint8_i_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_uint8_uint8_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_uint8_f_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_uint8_int16_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_f_f_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_d_d_uint(void *ptr);
     void delete_TwoSideClassificationThresholdOptimizer_uint8_int16_int16(void *ptr);


     void * getVarianceClassificationThresholdOptimizer_i_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_i_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_f_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_uint8_i_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_uint8_uint8_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_uint8_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_uint8_int16_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_f_f_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_d_d_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);
     void * getVarianceClassificationThresholdOptimizer_uint8_int16_int16 (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
);


     int eqVarianceClassificationThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_i_f_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_f_i_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_uint8_i_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_uint8_f_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_f_f_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
);
     int eqVarianceClassificationThresholdOptimizer_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_VarianceClassificationThresholdOptimizer_i_i_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_i_f_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_f_i_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_uint8_i_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_uint8_uint8_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_uint8_f_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_uint8_int16_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_f_f_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_d_d_uint(void *ptr);
     void delete_VarianceClassificationThresholdOptimizer_uint8_int16_int16(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_THRESHOLD_OPTIMIZERS_H_