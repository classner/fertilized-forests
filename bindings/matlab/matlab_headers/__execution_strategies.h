
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
     void delete_IExecutionStrategy_i_i_uint_fv_fv(void *ptr);
     void delete_IExecutionStrategy_f_f_uint_fv_fv(void *ptr);
     void delete_IExecutionStrategy_d_d_uint_fv_fv(void *ptr);
     void delete_IExecutionStrategy_uint8_uint8_uint_fv_fv(void *ptr);
     void delete_IExecutionStrategy_uint8_int16_uint_fv_fv(void *ptr);
     void delete_IExecutionStrategy_uint8_int16_int16_fv_fv(void *ptr);
     void delete_IExecutionStrategy_uint8_int16_int16_hp_vhp(void *ptr);
     void delete_IExecutionStrategy_f_f_f_rpf_vprpff(void *ptr);
     void delete_IExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr);


     void * getLocalExecutionStrategy_i_i_uint_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_f_f_uint_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_d_d_uint_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_uint8_uint8_uint_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_uint8_int16_uint_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_uint8_int16_int16_fv_fv (

        int num_threads
);
     void * getLocalExecutionStrategy_uint8_int16_int16_hp_vhp (

        int num_threads
);
     void * getLocalExecutionStrategy_f_f_f_rpf_vprpff (

        int num_threads
);
     void * getLocalExecutionStrategy_d_d_d_rpd_vprpfd (

        int num_threads
);
     void delete_LocalExecutionStrategy_i_i_uint_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_f_f_uint_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_d_d_uint_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_uint8_uint8_uint_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_uint8_int16_uint_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_uint8_int16_int16_fv_fv(void *ptr);
     void delete_LocalExecutionStrategy_uint8_int16_int16_hp_vhp(void *ptr);
     void delete_LocalExecutionStrategy_f_f_f_rpf_vprpff(void *ptr);
     void delete_LocalExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_EXECUTION_STRATEGIES_H_