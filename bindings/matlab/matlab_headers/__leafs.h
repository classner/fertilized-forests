
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_LEAFS_H_
#define MATFERTILIZED_MATLAB_HEADERS_LEAFS_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getBoostingLeafManager_i_uint (

        unsigned int n_classes
);
     void * getBoostingLeafManager_f_uint (

        unsigned int n_classes
);
     void * getBoostingLeafManager_d_uint (

        unsigned int n_classes
);
     void * getBoostingLeafManager_uint8_uint (

        unsigned int n_classes
);
     void * getBoostingLeafManager_uint8_int16 (

        unsigned int n_classes
);


     int eqBoostingLeafManager_i_uint (void *__instance,

        void * rhs
);
     int eqBoostingLeafManager_f_uint (void *__instance,

        void * rhs
);
     int eqBoostingLeafManager_d_uint (void *__instance,

        void * rhs
);
     int eqBoostingLeafManager_uint8_uint (void *__instance,

        void * rhs
);
     int eqBoostingLeafManager_uint8_int16 (void *__instance,

        void * rhs
);
     void delete_BoostingLeafManager_i_uint(void *ptr);
     void delete_BoostingLeafManager_f_uint(void *ptr);
     void delete_BoostingLeafManager_d_uint(void *ptr);
     void delete_BoostingLeafManager_uint8_uint(void *ptr);
     void delete_BoostingLeafManager_uint8_int16(void *ptr);


     void * getClassificationLeafManager_i_uint (

        unsigned int n_classes
);
     void * getClassificationLeafManager_f_uint (

        unsigned int n_classes
);
     void * getClassificationLeafManager_d_uint (

        unsigned int n_classes
);
     void * getClassificationLeafManager_uint8_uint (

        unsigned int n_classes
);
     void * getClassificationLeafManager_uint8_int16 (

        unsigned int n_classes
);


     int eqClassificationLeafManager_i_uint (void *__instance,

        void * rhs
);
     int eqClassificationLeafManager_f_uint (void *__instance,

        void * rhs
);
     int eqClassificationLeafManager_d_uint (void *__instance,

        void * rhs
);
     int eqClassificationLeafManager_uint8_uint (void *__instance,

        void * rhs
);
     int eqClassificationLeafManager_uint8_int16 (void *__instance,

        void * rhs
);
     void delete_ClassificationLeafManager_i_uint(void *ptr);
     void delete_ClassificationLeafManager_f_uint(void *ptr);
     void delete_ClassificationLeafManager_d_uint(void *ptr);
     void delete_ClassificationLeafManager_uint8_uint(void *ptr);
     void delete_ClassificationLeafManager_uint8_int16(void *ptr);


     void * getHoughLeafManager_uint8_int16 (

        unsigned int n_classes,
        size_t annot_dim
);


     int eqHoughLeafManager_uint8_int16 (void *__instance,

        void * rhs
);
     void delete_HoughLeafManager_uint8_int16(void *ptr);


     void * getRegressionLeafManager_f (

        void * selection_provider,
        size_t n_valids_to_use,
        void * regression_calculator,
        void * entropy_function,
        int use_fallback_constant_regression,
        int num_threads,
        unsigned int summary_mode
);
     void * getRegressionLeafManager_d (

        void * selection_provider,
        size_t n_valids_to_use,
        void * regression_calculator,
        void * entropy_function,
        int use_fallback_constant_regression,
        int num_threads,
        unsigned int summary_mode
);


     int eqRegressionLeafManager_f (void *__instance,

        void * rhs
);
     int eqRegressionLeafManager_d (void *__instance,

        void * rhs
);
     void delete_RegressionLeafManager_f(void *ptr);
     void delete_RegressionLeafManager_d(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_LEAFS_H_