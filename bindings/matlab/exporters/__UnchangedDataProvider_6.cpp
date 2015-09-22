
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <fertilized/data_providers/unchangeddataprovider.h>

using namespace fertilized;




          void * getUnchangedDataProvider_f_f (

        mxArray * data,
        mxArray * annotations
) {
  // From C types conversions.

    fertilized::Array<float, 2, 2> __converted_data;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(data);
      const mxClassID _matlab_dtid = mxGetClassID(data);
      const mwSize* _matlab_shape = mxGetDimensions(data);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument data!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_data = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_dptr = __converted_data.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(data));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(data, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    fertilized::Array<float, 2, 2> __converted_annotations;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(annotations);
      const mxClassID _matlab_dtid = mxGetClassID(annotations);
      const mwSize* _matlab_shape = mxGetDimensions(annotations);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument annotations!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_annotations = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_dptr = __converted_annotations.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(annotations));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(annotations, _matlab_ndim, _idx)];
        dimidx = 2-1;
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
  auto *libfunc_result = new std::shared_ptr<UnchangedDataProvider<float,float>>(
    new UnchangedDataProvider<
              float,
              float
>(
          __converted_data,
          __converted_annotations
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_UnchangedDataProvider_f_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<UnchangedDataProvider<float,float>>*>(ptr);
  delete storage;
}
