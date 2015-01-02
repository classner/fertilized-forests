
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_GAINS_H_
#define MATFERTILIZED_MATLAB_HEADERS_GAINS_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


    DllExport void * getEntropyGain_f (

        void * entropy_function
);
    DllExport void * getEntropyGain_uint (

        void * entropy_function
);
    DllExport void delete_EntropyGain_f(void *ptr);
    DllExport void delete_EntropyGain_uint(void *ptr);
    DllExport void delete_IGainCalculator_f(void *ptr);
    DllExport void delete_IGainCalculator_uint(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_GAINS_H_