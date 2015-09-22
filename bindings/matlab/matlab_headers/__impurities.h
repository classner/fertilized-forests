
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


     void * getInducedEntropy_f (

        float p
);
     void * getInducedEntropy_uint (

        float p
);


     float applyInducedEntropy_f (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);
     float applyInducedEntropy_uint (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);


     int eqInducedEntropy_f (void *__instance,

        void * rhs
);
     int eqInducedEntropy_uint (void *__instance,

        void * rhs
);
     void delete_InducedEntropy_f(void *ptr);
     void delete_InducedEntropy_uint(void *ptr);


     void * getRenyiEntropy_f (

        float alpha
);
     void * getRenyiEntropy_uint (

        float alpha
);


     int eqRenyiEntropy_f (void *__instance,

        void * rhs
);
     int eqRenyiEntropy_uint (void *__instance,

        void * rhs
);
     void delete_RenyiEntropy_f(void *ptr);
     void delete_RenyiEntropy_uint(void *ptr);


     void * getShannonEntropy_f (

);
     void * getShannonEntropy_uint (

);


     float applyShannonEntropy_f (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);
     float applyShannonEntropy_uint (void *__instance,

        mxArray * class_members_numbers,
        float fsum
);


     int eqShannonEntropy_f (void *__instance,

        void * rhs
);
     int eqShannonEntropy_uint (void *__instance,

        void * rhs
);
     void delete_ShannonEntropy_f(void *ptr);
     void delete_ShannonEntropy_uint(void *ptr);


     void * getClassificationError_f (

);
     void * getClassificationError_uint (

);


     int eqClassificationError_f (void *__instance,

        void * rhs
);
     int eqClassificationError_uint (void *__instance,

        void * rhs
);
     void delete_ClassificationError_f(void *ptr);
     void delete_ClassificationError_uint(void *ptr);


     void * getTsallisEntropy_f (

        float q
);
     void * getTsallisEntropy_uint (

        float q
);


     int eqTsallisEntropy_f (void *__instance,

        void * rhs
);
     int eqTsallisEntropy_uint (void *__instance,

        void * rhs
);
     void delete_TsallisEntropy_f(void *ptr);
     void delete_TsallisEntropy_uint(void *ptr);
     void delete_IEntropyFunction_f(void *ptr);
     void delete_IEntropyFunction_uint(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_IMPURITIES_H_