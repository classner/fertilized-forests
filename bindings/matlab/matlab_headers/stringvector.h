/* Author: Christoph Lassner. */
#pragma once
#ifndef MATFERTILIZED_MATLAB_HEADERS_STRINGVECTOR_H_
#define MATFERTILIZED_MATLAB_HEADERS_STRINGVECTOR_H_

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif
DllExport void *createStringVector();
DllExport void deleteStringVector(void *);
DllExport void appendToStringVector(void *, char *);
#ifdef __cplusplus
}
#endif

#endif  // MATFERTILIZED_MATLAB_HEADERS_STRINGVECTOR_H_
