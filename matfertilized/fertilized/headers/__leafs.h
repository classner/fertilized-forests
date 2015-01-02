
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


    DllExport void * getClassificationLeafManager_i_uint (

        unsigned int n_classes
);
    DllExport void * getClassificationLeafManager_f_uint (

        unsigned int n_classes
);
    DllExport void * getClassificationLeafManager_uint8_uint (

        unsigned int n_classes
);
    DllExport void * getClassificationLeafManager_uint8_int16 (

        unsigned int n_classes
);


    DllExport int eqClassificationLeafManager_i_uint (void *__instance,

        void * rhs
);
    DllExport int eqClassificationLeafManager_f_uint (void *__instance,

        void * rhs
);
    DllExport int eqClassificationLeafManager_uint8_uint (void *__instance,

        void * rhs
);
    DllExport int eqClassificationLeafManager_uint8_int16 (void *__instance,

        void * rhs
);
    DllExport void delete_ClassificationLeafManager_i_uint(void *ptr);
    DllExport void delete_ClassificationLeafManager_f_uint(void *ptr);
    DllExport void delete_ClassificationLeafManager_uint8_uint(void *ptr);
    DllExport void delete_ClassificationLeafManager_uint8_int16(void *ptr);


    DllExport void * getHoughLeafManager_uint8_int16 (

        unsigned int n_classes,
        size_t annot_dim
);


    DllExport int eqHoughLeafManager_uint8_int16 (void *__instance,

        void * rhs
);
    DllExport void delete_HoughLeafManager_uint8_int16(void *ptr);


    DllExport void * getRegressionLeafManager_f (

        void * selection_provider,
        size_t n_valids_to_use,
        void * regression_calculator,
        void * entropy_function,
        int use_fallback_constant_regression,
        int num_threads
);
    DllExport void * getRegressionLeafManager_d (

        void * selection_provider,
        size_t n_valids_to_use,
        void * regression_calculator,
        void * entropy_function,
        int use_fallback_constant_regression,
        int num_threads
);


    DllExport int eqRegressionLeafManager_f (void *__instance,

        void * rhs
);
    DllExport int eqRegressionLeafManager_d (void *__instance,

        void * rhs
);
    DllExport void delete_RegressionLeafManager_f(void *ptr);
    DllExport void delete_RegressionLeafManager_d(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_LEAFS_H_