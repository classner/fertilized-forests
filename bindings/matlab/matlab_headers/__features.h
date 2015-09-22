
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_FEATURES_H_
#define MATFERTILIZED_MATLAB_HEADERS_FEATURES_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getStandardFeatureSelectionProvider (

        size_t n_selections_per_node,
        size_t selection_dimension,
        size_t how_many_available,
        size_t max_to_use,
        unsigned int random_seed
);


     int eqStandardFeatureSelectionProvider (void *__instance,

        void * rhs
);


     size_t get_n_available_featuresStandardFeatureSelectionProvider (void *__instance

);
     void delete_StandardFeatureSelectionProvider(void *ptr);


     void * getDifferenceSurfaceCalculator_i_i_uint (

);
     void * getDifferenceSurfaceCalculator_uint8_int16_uint (

);
     void * getDifferenceSurfaceCalculator_f_f_uint (

);
     void * getDifferenceSurfaceCalculator_f_f_f (

);
     void * getDifferenceSurfaceCalculator_d_d_uint (

);
     void * getDifferenceSurfaceCalculator_d_d_d (

);


     int eqDifferenceSurfaceCalculator_i_i_uint (void *__instance,

        void * rhs
);
     int eqDifferenceSurfaceCalculator_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqDifferenceSurfaceCalculator_f_f_uint (void *__instance,

        void * rhs
);
     int eqDifferenceSurfaceCalculator_f_f_f (void *__instance,

        void * rhs
);
     int eqDifferenceSurfaceCalculator_d_d_uint (void *__instance,

        void * rhs
);
     int eqDifferenceSurfaceCalculator_d_d_d (void *__instance,

        void * rhs
);
     void delete_DifferenceSurfaceCalculator_i_i_uint(void *ptr);
     void delete_DifferenceSurfaceCalculator_uint8_int16_uint(void *ptr);
     void delete_DifferenceSurfaceCalculator_f_f_uint(void *ptr);
     void delete_DifferenceSurfaceCalculator_f_f_f(void *ptr);
     void delete_DifferenceSurfaceCalculator_d_d_uint(void *ptr);
     void delete_DifferenceSurfaceCalculator_d_d_d(void *ptr);


     void * getVolumeFeatureSelectionProvider (

        size_t selection_dimension,
        size_t size_x,
        size_t size_y,
        size_t size_z,
        size_t how_many_per_node,
        unsigned int random_seed
);


     int eqVolumeFeatureSelectionProvider (void *__instance,

        void * rhs
);


     size_t get_size_xVolumeFeatureSelectionProvider (void *__instance

);


     size_t get_size_yVolumeFeatureSelectionProvider (void *__instance

);


     size_t get_size_zVolumeFeatureSelectionProvider (void *__instance

);


     size_t get_n_available_featuresVolumeFeatureSelectionProvider (void *__instance

);
     void delete_VolumeFeatureSelectionProvider(void *ptr);


     void * getLinearSurfaceCalculator_i_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);
     void * getLinearSurfaceCalculator_uint8_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);
     void * getLinearSurfaceCalculator_f_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);
     void * getLinearSurfaceCalculator_f_f (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);
     void * getLinearSurfaceCalculator_d_d (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);
     void * getLinearSurfaceCalculator_d_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
);


     int eqLinearSurfaceCalculator_i_uint (void *__instance,

        void * rhs
);
     int eqLinearSurfaceCalculator_uint8_uint (void *__instance,

        void * rhs
);
     int eqLinearSurfaceCalculator_f_uint (void *__instance,

        void * rhs
);
     int eqLinearSurfaceCalculator_f_f (void *__instance,

        void * rhs
);
     int eqLinearSurfaceCalculator_d_d (void *__instance,

        void * rhs
);
     int eqLinearSurfaceCalculator_d_uint (void *__instance,

        void * rhs
);
     void delete_LinearSurfaceCalculator_i_uint(void *ptr);
     void delete_LinearSurfaceCalculator_uint8_uint(void *ptr);
     void delete_LinearSurfaceCalculator_f_uint(void *ptr);
     void delete_LinearSurfaceCalculator_f_f(void *ptr);
     void delete_LinearSurfaceCalculator_d_d(void *ptr);
     void delete_LinearSurfaceCalculator_d_uint(void *ptr);


     void * getDirectPatchDifferenceSurfCalculator_uint8_int16_uint (

        size_t psx,
        size_t psy,
        size_t psz,
        int luc
);
     void * getDirectPatchDifferenceSurfCalculator_uint8_int16_int16 (

        size_t psx,
        size_t psy,
        size_t psz,
        int luc
);


     int eqDirectPatchDifferenceSurfCalculator_uint8_int16_uint (void *__instance,

        void * rhs
);
     int eqDirectPatchDifferenceSurfCalculator_uint8_int16_int16 (void *__instance,

        void * rhs
);
     void delete_DirectPatchDifferenceSurfCalculator_uint8_int16_uint(void *ptr);
     void delete_DirectPatchDifferenceSurfCalculator_uint8_int16_int16(void *ptr);
     void delete_FeatCalcParamSet(void *ptr);


     void * getAlignedSurfaceCalculator_i_uint (

);
     void * getAlignedSurfaceCalculator_uint8_uint (

);
     void * getAlignedSurfaceCalculator_f_uint (

);
     void * getAlignedSurfaceCalculator_f_f (

);
     void * getAlignedSurfaceCalculator_d_uint (

);
     void * getAlignedSurfaceCalculator_d_d (

);


     int eqAlignedSurfaceCalculator_i_uint (void *__instance,

        void * rhs
);
     int eqAlignedSurfaceCalculator_uint8_uint (void *__instance,

        void * rhs
);
     int eqAlignedSurfaceCalculator_f_uint (void *__instance,

        void * rhs
);
     int eqAlignedSurfaceCalculator_f_f (void *__instance,

        void * rhs
);
     int eqAlignedSurfaceCalculator_d_uint (void *__instance,

        void * rhs
);
     int eqAlignedSurfaceCalculator_d_d (void *__instance,

        void * rhs
);
     void delete_AlignedSurfaceCalculator_i_uint(void *ptr);
     void delete_AlignedSurfaceCalculator_uint8_uint(void *ptr);
     void delete_AlignedSurfaceCalculator_f_uint(void *ptr);
     void delete_AlignedSurfaceCalculator_f_f(void *ptr);
     void delete_AlignedSurfaceCalculator_d_uint(void *ptr);
     void delete_AlignedSurfaceCalculator_d_d(void *ptr);


     void * getQuadraticSurfaceCalculator_i_uint (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);
     void * getQuadraticSurfaceCalculator_uint8_uint (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);
     void * getQuadraticSurfaceCalculator_f_uint (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);
     void * getQuadraticSurfaceCalculator_f_f (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);
     void * getQuadraticSurfaceCalculator_d_uint (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);
     void * getQuadraticSurfaceCalculator_d_d (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
);


     int eqQuadraticSurfaceCalculator_i_uint (void *__instance,

        void * rhs
);
     int eqQuadraticSurfaceCalculator_uint8_uint (void *__instance,

        void * rhs
);
     int eqQuadraticSurfaceCalculator_f_uint (void *__instance,

        void * rhs
);
     int eqQuadraticSurfaceCalculator_f_f (void *__instance,

        void * rhs
);
     int eqQuadraticSurfaceCalculator_d_uint (void *__instance,

        void * rhs
);
     int eqQuadraticSurfaceCalculator_d_d (void *__instance,

        void * rhs
);
     void delete_QuadraticSurfaceCalculator_i_uint(void *ptr);
     void delete_QuadraticSurfaceCalculator_uint8_uint(void *ptr);
     void delete_QuadraticSurfaceCalculator_f_uint(void *ptr);
     void delete_QuadraticSurfaceCalculator_f_f(void *ptr);
     void delete_QuadraticSurfaceCalculator_d_uint(void *ptr);
     void delete_QuadraticSurfaceCalculator_d_d(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_FEATURES_H_