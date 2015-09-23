
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <../../include/fertilized/data_providers/nocopypatchsamplemanager.h>

using namespace fertilized;




          void * getNoCopyPatchSampleManager_uint8_uint (

        mxArray * images,
        mxArray * patch_descs,
        size_t n_positives,
        size_t patch_size_z,
        size_t patch_size_y,
        size_t patch_size_x,
        int patches_luc
) {
  // From C types conversions.

   std::vector<fertilized::Array<const uint8_t, 3, 3>> __converted_images;
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
      __converted_images = std::vector<fertilized::Array<const uint8_t, 3, 3>>(_matlab_shape[1]);
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
        if (_cell_dtid != mxUINT8_CLASS) {
          mexErrMsgTxt("Wrong MATLAB datatype while parsing cells of images!");
        }
        Vector<std::size_t,  3> shape;
        for (std::size_t j = 0; j <  3; ++j) {
          shape[j] = _cell_shape[j];
        }
        Array<uint8_t,  3,  3> __converted_cell = allocate(shape);
        mwIndex _idx [ 3];
        for (std::size_t j = 0; j <  3; ++j) {
          _idx[j] = 0;
        }
        int dimidx;
        uint8_t *_dptr = __converted_cell.getData();
        uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(cell));
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

    fertilized::Array<uint, 2, 2> __converted_patch_descs;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(patch_descs);
      const mxClassID _matlab_dtid = mxGetClassID(patch_descs);
      const mwSize* _matlab_shape = mxGetDimensions(patch_descs);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT32_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument patch_descs!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_patch_descs = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint *_dptr = __converted_patch_descs.getData();
      uint *_iptr = reinterpret_cast<uint*>(mxGetData(patch_descs));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(patch_descs, _matlab_ndim, _idx)];
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
  auto *libfunc_result = new std::shared_ptr<NoCopyPatchSampleManager<uint8_t,uint>>(
    new NoCopyPatchSampleManager<
              uint8_t,
              uint
>(
          __converted_images,
          __converted_patch_descs,
          n_positives,
          patch_size_z,
          patch_size_y,
          patch_size_x,
          patches_luc
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_NoCopyPatchSampleManager_uint8_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<NoCopyPatchSampleManager<uint8_t,uint>>*>(ptr);
  delete storage;
}
