
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__impurities.h"
#include <fertilized/impurities/shannonentropy.h>

using namespace fertilized;




          void * getShannonEntropy_f (

) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<ShannonEntropy<float>>(
    new ShannonEntropy<
              float
>(
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          float applyShannonEntropy_f (void *__instance,

        mxArray * class_members_numbers,
        float fsum
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ShannonEntropy<float>>*>(__instance);
  // From C types conversions.

    std::vector<float> __converted_class_members_numbers;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(class_members_numbers);
      const mxClassID _matlab_dtid = mxGetClassID(class_members_numbers);
      const mwSize* _matlab_shape = mxGetDimensions(class_members_numbers);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxSINGLE_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument class_members_numbers!");
      }
      // Shape check.
      if (_matlab_shape[0] != 1) {
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }
      __converted_class_members_numbers = std::vector<float>(_matlab_shape[1]);
      mwIndex _idx [2];
      for (std::size_t i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_iptr = reinterpret_cast<float*>(mxGetData(class_members_numbers));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {
        __converted_class_members_numbers[i] = _iptr[mxCalcSingleSubscript(class_members_numbers, _matlab_ndim, _idx)];
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
  auto libfunc_result = __instance_unpacked -> operator()(
          __converted_class_members_numbers,
          fsum
  );
#pragma warning( pop )

  return libfunc_result;
}		


          int eqShannonEntropy_f (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ShannonEntropy<float>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IEntropyFunction<float>>*>(rhs);
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
void delete_ShannonEntropy_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ShannonEntropy<float>>*>(ptr);
  delete storage;
}
