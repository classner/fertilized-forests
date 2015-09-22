
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <fertilized/features/quadraticsurfacecalculator.h>

using namespace fertilized;




          void * getQuadraticSurfaceCalculator_i_uint (

        size_t n_params_per_feat_sel,
        mxArray * min_max_vals,
        unsigned int random_seed
) {
  // From C types conversions.

    std::vector<float> __converted_min_max_vals;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(min_max_vals);
      const mxClassID _matlab_dtid = mxGetClassID(min_max_vals);
      const mwSize* _matlab_shape = mxGetDimensions(min_max_vals);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument min_max_vals!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_min_max_vals = std::vector<float>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_iptr = reinterpret_cast<float*>(mxGetData(min_max_vals));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_min_max_vals[i] = _iptr[mxCalcSingleSubscript(min_max_vals, _matlab_ndim, _idx)];
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
  auto *libfunc_result = new std::shared_ptr<QuadraticSurfaceCalculator<int,uint>>(
    new QuadraticSurfaceCalculator<
              int,
              uint
>(
          n_params_per_feat_sel,
          __converted_min_max_vals,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqQuadraticSurfaceCalculator_i_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<QuadraticSurfaceCalculator<int,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ISurfaceCalculator<int, float, uint>>*>(rhs);
    auto &__converted_rhs = *(__shptr_rhs.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> operator==(
          __converted_rhs
  );
#pragma warning( pop )

  return libfunc_result;
}		
// Destructor.
void delete_QuadraticSurfaceCalculator_i_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<QuadraticSurfaceCalculator<int,uint>>*>(ptr);
  delete storage;
}
