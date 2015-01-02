
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_TRAININGS_H_
#define MATFERTILIZED_MATLAB_HEADERS_TRAININGS_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


    DllExport void * getClassicTraining_i_i_uint_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_f_f_uint_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_d_d_uint_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_uint8_uint8_uint_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_uint8_int16_uint_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_uint8_int16_int16_fv_fv (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_uint8_int16_int16_hp_vhp (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_f_f_f_rpf_vprpff (

        void * bagging_strategy
);
    DllExport void * getClassicTraining_d_d_d_rpd_vprpfd (

        void * bagging_strategy
);


    DllExport int eqClassicTraining_i_i_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_f_f_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_d_d_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_uint8_int16_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_uint8_int16_int16_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_f_f_f_rpf_vprpff (void *__instance,

        void * rhs
);
    DllExport int eqClassicTraining_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
);
    DllExport void delete_ClassicTraining_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_d_d_uint_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_uint8_int16_uint_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_uint8_int16_int16_fv_fv(void *ptr);
    DllExport void delete_ClassicTraining_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_ClassicTraining_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_ClassicTraining_d_d_d_rpd_vprpfd(void *ptr);
    DllExport void delete_ITraining_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_ITraining_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_ITraining_d_d_uint_fv_fv(void *ptr);
    DllExport void delete_ITraining_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_ITraining_uint8_int16_uint_fv_fv(void *ptr);
    DllExport void delete_ITraining_uint8_int16_int16_fv_fv(void *ptr);
    DllExport void delete_ITraining_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_ITraining_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_ITraining_d_d_d_rpd_vprpfd(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_TRAININGS_H_