
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/global.h"

#include <vector>

#include <mex.h>

#include "../matlab_headers/__functions_standard_trees.h"
#include <fertilized/fertilized.h>

using namespace fertilized;


void * StandardHoughTree_uint8_int16_int16 (

        mxArray * patch_dimensions,
        size_t n_thresholds_per_split,
        size_t n_splits_per_node,
        unsigned int max_depth,
        mxArray * min_sample_counts,
        unsigned int random_seed,
        mxArray * min_gain_thresholds,
        int patch_annot_luc,
        int allow_redraw,
        unsigned int num_threads,
        void * entropy_names,
        mxArray * entropy_p1,
        int use_hough_heuristic,
        float hough_heuristic_ratio,
        unsigned int hough_heuristic_maxd
) {
  // From C types conversions.

    std::vector<size_t> __converted_patch_dimensions;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(patch_dimensions);
      const mxClassID _matlab_dtid = mxGetClassID(patch_dimensions);
      const mwSize* _matlab_shape = mxGetDimensions(patch_dimensions);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT64_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument patch_dimensions!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_patch_dimensions = std::vector<size_t>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      size_t *_iptr = reinterpret_cast<size_t*>(mxGetData(patch_dimensions));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_patch_dimensions[i] = _iptr[mxCalcSingleSubscript(patch_dimensions, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    std::vector<fertilized::uint> __converted_min_sample_counts;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(min_sample_counts);
      const mxClassID _matlab_dtid = mxGetClassID(min_sample_counts);
      const mwSize* _matlab_shape = mxGetDimensions(min_sample_counts);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT32_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument min_sample_counts!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_min_sample_counts = std::vector<fertilized::uint>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      fertilized::uint *_iptr = reinterpret_cast<fertilized::uint*>(mxGetData(min_sample_counts));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_min_sample_counts[i] = _iptr[mxCalcSingleSubscript(min_sample_counts, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    std::vector<float> __converted_min_gain_thresholds;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(min_gain_thresholds);
      const mxClassID _matlab_dtid = mxGetClassID(min_gain_thresholds);
      const mwSize* _matlab_shape = mxGetDimensions(min_gain_thresholds);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument min_gain_thresholds!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_min_gain_thresholds = std::vector<float>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_iptr = reinterpret_cast<float*>(mxGetData(min_gain_thresholds));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_min_gain_thresholds[i] = _iptr[mxCalcSingleSubscript(min_gain_thresholds, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    std::vector<std::string> __converted_entropy_names = *reinterpret_cast<std::vector<std::string>*>(entropy_names);
              

    std::vector<float> __converted_entropy_p1;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(entropy_p1);
      const mxClassID _matlab_dtid = mxGetClassID(entropy_p1);
      const mwSize* _matlab_shape = mxGetDimensions(entropy_p1);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument entropy_p1!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_entropy_p1 = std::vector<float>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_iptr = reinterpret_cast<float*>(mxGetData(entropy_p1));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_entropy_p1[i] = _iptr[mxCalcSingleSubscript(entropy_p1, _matlab_ndim, _idx)];
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
  auto libfunc_result = construct_hough_tree<
              uint8_t,
              int16_t,
              int16_t
>(
          __converted_patch_dimensions,
          n_thresholds_per_split,
          n_splits_per_node,
          max_depth,
          __converted_min_sample_counts,
          random_seed,
          __converted_min_gain_thresholds,
          patch_annot_luc,
          allow_redraw,
          num_threads,
          __converted_entropy_names,
          __converted_entropy_p1,
          use_hough_heuristic,
          hough_heuristic_ratio,
          hough_heuristic_maxd
          );
#pragma warning( pop )
  // Result conversion.

    void * __converted_return_value = copy_to_heap(libfunc_result);
    
  return __converted_return_value;
}

