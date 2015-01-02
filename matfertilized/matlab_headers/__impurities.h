
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_IMPURITIES_H_
#define MATFERTILIZED_MATLAB_HEADERS_IMPURITIES_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


    DllExport void * getClassificationError_f (

);
    DllExport void * getClassificationError_uint (

);


    DllExport int eqClassificationError_f (void *__instance,

        void * rhs
);
    DllExport int eqClassificationError_uint (void *__instance,

        void * rhs
);
    DllExport void delete_ClassificationError_f(void *ptr);
    DllExport void delete_ClassificationError_uint(void *ptr);
    DllExport void delete_IEntropyFunction_f(void *ptr);
    DllExport void delete_IEntropyFunction_uint(void *ptr);


    DllExport void * getInducedEntropy_f (

        float p
);
    DllExport void * getInducedEntropy_uint (

        float p
);


    DllExport float applyInducedEntropy_f (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);
    DllExport float applyInducedEntropy_uint (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);


    DllExport int eqInducedEntropy_f (void *__instance,

        void * rhs
);
    DllExport int eqInducedEntropy_uint (void *__instance,

        void * rhs
);
    DllExport void delete_InducedEntropy_f(void *ptr);
    DllExport void delete_InducedEntropy_uint(void *ptr);


    DllExport void * getRenyiEntropy_f (

        float alpha
);
    DllExport void * getRenyiEntropy_uint (

        float alpha
);


    DllExport int eqRenyiEntropy_f (void *__instance,

        void * rhs
);
    DllExport int eqRenyiEntropy_uint (void *__instance,

        void * rhs
);
    DllExport void delete_RenyiEntropy_f(void *ptr);
    DllExport void delete_RenyiEntropy_uint(void *ptr);


    DllExport void * getShannonEntropy_f (

);
    DllExport void * getShannonEntropy_uint (

);


    DllExport float applyShannonEntropy_f (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);
    DllExport float applyShannonEntropy_uint (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);


    DllExport int eqShannonEntropy_f (void *__instance,

        void * rhs
);
    DllExport int eqShannonEntropy_uint (void *__instance,

        void * rhs
);
    DllExport void delete_ShannonEntropy_f(void *ptr);
    DllExport void delete_ShannonEntropy_uint(void *ptr);


    DllExport void * getTsallisEntropy_f (

        float q
);
    DllExport void * getTsallisEntropy_uint (

        float q
);


    DllExport int eqTsallisEntropy_f (void *__instance,

        void * rhs
);
    DllExport int eqTsallisEntropy_uint (void *__instance,

        void * rhs
);
    DllExport void delete_TsallisEntropy_f(void *ptr);
    DllExport void delete_TsallisEntropy_uint(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_IMPURITIES_H_