
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


    DllExport void * getConstantRegressionCalculator_f (

);
    DllExport void * getConstantRegressionCalculator_d (

);
    DllExport void delete_ConstantRegressionCalculator_f(void *ptr);
    DllExport void delete_ConstantRegressionCalculator_d(void *ptr);


    DllExport void * getLinearRegressionCalculator_f (

        int force_numerical_stability,
        void * numerical_zero_threshold
);
    DllExport void * getLinearRegressionCalculator_d (

        int force_numerical_stability,
        void * numerical_zero_threshold
);
    DllExport void delete_LinearRegressionCalculator_f(void *ptr);
    DllExport void delete_LinearRegressionCalculator_d(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_REGRESSION_H_