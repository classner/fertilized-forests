
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__feature_extraction.h"
#include <../../include/fertilized/feature_extraction/dnnfeatureextractor.h>

using namespace fertilized;




void * getDNNFeatureExtractor (

        int use_cpu,
        int device_id,
        char* net_layout_file,
        char* net_weights_file,
        char* net_outlayer,
        int load_mean,
        char* mean_file
) {
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<DNNFeatureExtractor>(
    new DNNFeatureExtractor(
          use_cpu,
          device_id,
          net_layout_file,
          net_weights_file,
          net_outlayer,
          load_mean,
          mean_file
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}


mxArray * extractDNNFeatureExtractor (void *__instance,

        mxArray * images,
        int subtract_mean
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<DNNFeatureExtractor>*>(__instance);
  // From C types conversions.

   std::vector<fertilized::Array<float, 3, 3>> __converted_images;
   {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(images);
      const mxClassID _matlab_dtid = mxGetClassID(images);
      const mwSize* _matlab_shape = mxGetDimensions(images);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions of the cell array, received " +
          std::to_string(_matlab_ndim) + " (images)").c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxCELL_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument images! Cell array of arrays required.");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector (images!");
      }
      __converted_images = std::vector<fertilized::Array<float, 3, 3>>(_matlab_shape[1]);
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        mxArray * cell = mxGetCell(images, i);
        const mwSize _cell_ndim = mxGetNumberOfDimensions(cell);
        const mxClassID _cell_dtid = mxGetClassID(cell);
        const mwSize* _cell_shape = mxGetDimensions(cell);
        // Dimensionality check.
        if (_cell_ndim !=  3) {
          mexErrMsgTxt(("Expected  3 dimensions of each cell, received " +
            std::to_string(_cell_ndim)).c_str());
        }
        // Dtype check.
        if (_cell_dtid != mxSINGLE_CLASS) {
          mexErrMsgTxt("Wrong MATLAB datatype while parsing cells of images!");
        }
        Vector<std::size_t,  3> shape;
        for (std::size_t j = 0; j <  3; ++j) {
          shape[j] = _cell_shape[j];
        }
        Array<float,  3,  3> __converted_cell = allocate(shape);
        mwIndex _idx [ 3];
        for (std::size_t j = 0; j <  3; ++j) {
          _idx[j] = 0;
        }
        int dimidx;
        float *_dptr = __converted_cell.getData();
        float *_iptr = reinterpret_cast<float*>(mxGetData(cell));
        for (std::size_t j = 0; j < shape.product(); ++j) {
          _dptr[j] = _iptr[mxCalcSingleSubscript(cell, _cell_ndim, _idx)];
          dimidx =  3-1;
          while (_idx[dimidx] == _cell_shape[dimidx]-1) {
            _idx[dimidx] = 0;
            dimidx -= 1;
          }
          _idx[dimidx]++;
        }
        __converted_images.push_back(__converted_cell);
      }
   }


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> extract(
          __converted_images,
          subtract_mean
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 4;
      mwSize shape[ 4 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 4; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxSINGLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [4];
      for (int i = 0; i < 4; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_dptr = libfunc_result.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 4, _idx)] = _dptr[i];
        dimidx = 4-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}
// Destructor.
void delete_DNNFeatureExtractor(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<DNNFeatureExtractor>*>(ptr);
  delete storage;
}
