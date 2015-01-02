
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_EXECUTION_STRATEGIES_H_
#define MATFERTILIZED_MATLAB_HEADERS_EXECUTION_STRATEGIES_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif
    DllExport void delete_IExecutionStrategy_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_IExecutionStrategy_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_IExecutionStrategy_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_IExecutionStrategy_uint8_int16_uint_fv_fv(void *ptr);
    DllExport void delete_IExecutionStrategy_uint8_int16_int16_fv_fv(void *ptr);
    DllExport void delete_IExecutionStrategy_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_IExecutionStrategy_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_IExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr);


    DllExport void * getLocalExecutionStrategy_i_i_uint_fv_fv (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_f_f_uint_fv_fv (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_uint8_uint8_uint_fv_fv (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_uint8_int16_uint_fv_fv (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_uint8_int16_int16_fv_fv (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_uint8_int16_int16_hp_vhp (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_f_f_f_rpf_vprpff (

        int num_threads
);
    DllExport void * getLocalExecutionStrategy_d_d_d_rpd_vprpfd (

        int num_threads
);
    DllExport void delete_LocalExecutionStrategy_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_LocalExecutionStrategy_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_LocalExecutionStrategy_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_LocalExecutionStrategy_uint8_int16_uint_fv_fv(void *ptr);
    DllExport void delete_LocalExecutionStrategy_uint8_int16_int16_fv_fv(void *ptr);
    DllExport void delete_LocalExecutionStrategy_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_LocalExecutionStrategy_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_LocalExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_EXECUTION_STRATEGIES_H_