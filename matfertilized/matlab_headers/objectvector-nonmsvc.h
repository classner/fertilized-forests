/* Author: Christoph Lassner. */
#pragma once
#ifndef MATFERTILIZED_MATLAB_HEADERS_OBJECTVECTOR_H_
#define MATFERTILIZED_MATLAB_HEADERS_OBJECTVECTOR_H_

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif
void *createObjectVector();
void deleteObjectVector(void *);
void appendToObjectVector(void *, void *);
#ifdef __cplusplus
}
#endif

#endif  // MATFERTILIZED_MATLAB_HEADERS_OBJECTVECTOR_H_
