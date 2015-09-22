
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/global.h"

#include <vector>

#include <mex.h>

#include "../matlab_headers/__functions_feature_extraction.h"
#include <fertilized/fertilized.h>

using namespace fertilized;



mxArray * extract_hough_forest_features (

        mxArray * image,
        int full
) {
  // From C types conversions.

    fertilized::Array<uint8_t, 3, 3> __converted_image;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(image);
      const mxClassID _matlab_dtid = mxGetClassID(image);
      const mwSize* _matlab_shape = mxGetDimensions(image);
      // Dimensionality check.
      if (_matlab_ndim != 3) {
        mexErrMsgTxt(("Expected 3 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT8_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument image!");
      }
      Vector<std::size_t, 3> shape;
      for (int i = 0; i < 3; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_image = allocate(shape);
      mwIndex _idx [3];
      for (int i = 0; i < 3; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint8_t *_dptr = __converted_image.getData();
      uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(image));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(image, _matlab_ndim, _idx)];
        dimidx = 3-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = extract_hough_forest_features(
          __converted_image,
          full
          );
#pragma warning( pop ) 
  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 3;
      mwSize shape[ 3 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 3; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxUINT8_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [3];
      for (int i = 0; i < 3; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint8_t *_dptr = libfunc_result.getData();
      uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 3, _idx)] = _dptr[i];
        dimidx = 3-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}
