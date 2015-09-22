
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <fertilized/data_providers/unchangedfdataprovider.h>

using namespace fertilized;




          void * getUnchangedFDataProvider_d_d (

        mxArray * data_array,
        mxArray * annotation_array
) {
  // From C types conversions.

    fertilized::Array<double, 2, 2> __converted_data_array;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(data_array);
      const mxClassID _matlab_dtid = mxGetClassID(data_array);
      const mwSize* _matlab_shape = mxGetDimensions(data_array);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxDOUBLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument data_array!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_data_array = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      double *_dptr = __converted_data_array.getData();
      double *_iptr = reinterpret_cast<double*>(mxGetData(data_array));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(data_array, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    fertilized::Array<double, 2, 2> __converted_annotation_array;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(annotation_array);
      const mxClassID _matlab_dtid = mxGetClassID(annotation_array);
      const mwSize* _matlab_shape = mxGetDimensions(annotation_array);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxDOUBLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument annotation_array!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_annotation_array = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      double *_dptr = __converted_annotation_array.getData();
      double *_iptr = reinterpret_cast<double*>(mxGetData(annotation_array));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(annotation_array, _matlab_ndim, _idx)];
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
  auto *libfunc_result = new std::shared_ptr<UnchangedFDataProvider<double,double>>(
    new UnchangedFDataProvider<
              double,
              double
>(
          __converted_data_array,
          __converted_annotation_array
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_UnchangedFDataProvider_d_d(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<UnchangedFDataProvider<double,double>>*>(ptr);
  delete storage;
}
