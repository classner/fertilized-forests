
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_DATA_PROVIDERS_H_
#define MATFERTILIZED_MATLAB_HEADERS_DATA_PROVIDERS_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getNoCopyPatchSampleManager_uint8_int16 (

        mxArray * images,
        mxArray * patch_descs,
        size_t n_positives,
        size_t patch_size_z,
        size_t patch_size_y,
        size_t patch_size_x,
        int patches_luc
);
     void * getNoCopyPatchSampleManager_uint8_uint (

        mxArray * images,
        mxArray * patch_descs,
        size_t n_positives,
        size_t patch_size_z,
        size_t patch_size_y,
        size_t patch_size_x,
        int patches_luc
);
     void delete_NoCopyPatchSampleManager_uint8_int16(void *ptr);
     void delete_NoCopyPatchSampleManager_uint8_uint(void *ptr);
     void delete_IDataProvider_f_uint(void *ptr);
     void delete_IDataProvider_i_uint(void *ptr);
     void delete_IDataProvider_uint8_uint(void *ptr);
     void delete_IDataProvider_uint8_int16(void *ptr);
     void delete_IDataProvider_d_uint(void *ptr);
     void delete_IDataProvider_d_d(void *ptr);
     void delete_IDataProvider_f_f(void *ptr);


     void * getSubsamplingDataProvider_uint8_int16 (

        size_t max_samples_per_node,
        void * sample_manager,
        unsigned int random_seed
);
     void * getSubsamplingDataProvider_uint8_uint (

        size_t max_samples_per_node,
        void * sample_manager,
        unsigned int random_seed
);
     void delete_SubsamplingDataProvider_uint8_int16(void *ptr);
     void delete_SubsamplingDataProvider_uint8_uint(void *ptr);


     void * getUnchangedFDataProvider_f_uint (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_i_uint (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_uint8_uint (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_uint8_int16 (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_d_uint (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_d_d (

        mxArray * data_array,
        mxArray * annotation_array
);
     void * getUnchangedFDataProvider_f_f (

        mxArray * data_array,
        mxArray * annotation_array
);
     void delete_UnchangedFDataProvider_f_uint(void *ptr);
     void delete_UnchangedFDataProvider_i_uint(void *ptr);
     void delete_UnchangedFDataProvider_uint8_uint(void *ptr);
     void delete_UnchangedFDataProvider_uint8_int16(void *ptr);
     void delete_UnchangedFDataProvider_d_uint(void *ptr);
     void delete_UnchangedFDataProvider_d_d(void *ptr);
     void delete_UnchangedFDataProvider_f_f(void *ptr);


     void * getUnchangedDataProvider_f_uint (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_i_uint (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_uint8_uint (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_uint8_int16 (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_d_uint (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_d_d (

        mxArray * data,
        mxArray * annotations
);
     void * getUnchangedDataProvider_f_f (

        mxArray * data,
        mxArray * annotations
);
     void delete_UnchangedDataProvider_f_uint(void *ptr);
     void delete_UnchangedDataProvider_i_uint(void *ptr);
     void delete_UnchangedDataProvider_uint8_uint(void *ptr);
     void delete_UnchangedDataProvider_uint8_int16(void *ptr);
     void delete_UnchangedDataProvider_d_uint(void *ptr);
     void delete_UnchangedDataProvider_d_d(void *ptr);
     void delete_UnchangedDataProvider_f_f(void *ptr);
     void delete_IForestDataProvider_f_uint(void *ptr);
     void delete_IForestDataProvider_i_uint(void *ptr);
     void delete_IForestDataProvider_uint8_uint(void *ptr);
     void delete_IForestDataProvider_uint8_int16(void *ptr);
     void delete_IForestDataProvider_d_uint(void *ptr);
     void delete_IForestDataProvider_d_d(void *ptr);
     void delete_IForestDataProvider_f_f(void *ptr);


     void * getPatchSampleManager_uint8_int16 (

        mxArray * images,
        mxArray * patch_descs,
        size_t n_positives,
        size_t patch_size_z,
        size_t patch_size_y,
        size_t patch_size_x,
        int patches_luc
);
     void * getPatchSampleManager_uint8_uint (

        mxArray * images,
        mxArray * patch_descs,
        size_t n_positives,
        size_t patch_size_z,
        size_t patch_size_y,
        size_t patch_size_x,
        int patches_luc
);
     void delete_PatchSampleManager_uint8_int16(void *ptr);
     void delete_PatchSampleManager_uint8_uint(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_DATA_PROVIDERS_H_