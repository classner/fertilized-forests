
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_FEATURE_EXTRACTION_H_
#define MATFERTILIZED_MATLAB_HEADERS_FEATURE_EXTRACTION_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getDNNFeatureExtractor (

        char* net_layout_file,
        char* net_weights_file,
        char* net_outlayer,
        int use_cpu,
        int device_id,
        char* mean_file
);


     mxArray * extractDNNFeatureExtractor (void *__instance,

        mxArray * images,
        int subtract_mean
);
     void delete_DNNFeatureExtractor(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_FEATURE_EXTRACTION_H_