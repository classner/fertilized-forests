
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_REGRESSION_H_
#define MATFERTILIZED_MATLAB_HEADERS_REGRESSION_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


     void * getLinearRegressionCalculator_f (

        int force_numerical_stability,
        void * numerical_zero_threshold
);
     void * getLinearRegressionCalculator_d (

        int force_numerical_stability,
        void * numerical_zero_threshold
);


     int eqLinearRegressionCalculator_f (void *__instance,

        void * rhs
);
     int eqLinearRegressionCalculator_d (void *__instance,

        void * rhs
);
     void delete_LinearRegressionCalculator_f(void *ptr);
     void delete_LinearRegressionCalculator_d(void *ptr);


     void * getConstantRegressionCalculator_f (

);
     void * getConstantRegressionCalculator_d (

);


     int eqConstantRegressionCalculator_f (void *__instance,

        void * rhs
);
     int eqConstantRegressionCalculator_d (void *__instance,

        void * rhs
);
     void delete_ConstantRegressionCalculator_f(void *ptr);
     void delete_ConstantRegressionCalculator_d(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_REGRESSION_H_