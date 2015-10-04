/* Author: Christoph Lassner. */
#pragma once
#ifndef MATFERTILIZED_MATLAB_HEADERS_GLOBAL_H_
#define MATFERTILIZED_MATLAB_HEADERS_GLOBAL_H_

// Library exports.
#if defined DllExport
#undef DllExport
#endif
#if !defined(_MSC_VER)
#define DllExport
#elif __BUILD_MATFERTILIZED_LIBRARY
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#endif  // MATFERTILIZED_MATLAB_HEADERS_GLOBAL_H_
