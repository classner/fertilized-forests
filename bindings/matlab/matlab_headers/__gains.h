
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
     void delete_IGainCalculator_f(void *ptr);
     void delete_IGainCalculator_uint(void *ptr);


     void * getEntropyGain_f (

        void * entropy_function
);
     void * getEntropyGain_uint (

        void * entropy_function
);


     int eqEntropyGain_f (void *__instance,

        void * rhs
);
     int eqEntropyGain_uint (void *__instance,

        void * rhs
);
     void delete_EntropyGain_f(void *ptr);
     void delete_EntropyGain_uint(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_GAINS_H_