
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__deciders.h"
#include <../../include/fertilized/deciders/thresholddecider.h>

using namespace fertilized;




          void * getThresholdDecider_uint8_int16_uint (

        void * selection_provider,
        void * feature_calculator,
        void * threshold_optimizer,
        size_t n_valid_features_to_use,
        int num_threads,
        int use_hough_heuristic,
        float hough_heuristic_ratio,
        unsigned int hough_heuristic_maxd,
        int allow_early_stopping
) {
  // From C types conversions.

    auto __converted_selection_provider = *reinterpret_cast<std::shared_ptr<fertilized::IFeatureSelectionProvider>*>(selection_provider);
              

    auto __converted_feature_calculator = *reinterpret_cast<std::shared_ptr<fertilized::ThresholdDecider<uint8_t, int16_t, uint>::feat_calc_t>*>(feature_calculator);
              

    auto __converted_threshold_optimizer = *reinterpret_cast<std::shared_ptr<fertilized::ThresholdDecider<uint8_t, int16_t, uint>::thresh_opt_t>*>(threshold_optimizer);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<ThresholdDecider<uint8_t,int16_t,uint>>(
    new ThresholdDecider<
              uint8_t,
              int16_t,
              uint
>(
          __converted_selection_provider,
          __converted_feature_calculator,
          __converted_threshold_optimizer,
          n_valid_features_to_use,
          num_threads,
          use_hough_heuristic,
          hough_heuristic_ratio,
          hough_heuristic_maxd,
          allow_early_stopping
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          mxArray * compute_feature_importancesThresholdDecider_uint8_int16_uint (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ThresholdDecider<uint8_t,int16_t,uint>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> compute_feature_importances(
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 1;
      mwSize shape[ 1 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 1; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxDOUBLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [1];
      for (int i = 0; i < 1; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      double *_dptr = libfunc_result.getData();
      double *_iptr = reinterpret_cast<double*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 1, _idx)] = _dptr[i];
        dimidx = 1-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}		


          int eqThresholdDecider_uint8_int16_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ThresholdDecider<uint8_t,int16_t,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IDecider<uint8_t, int16_t, uint>>*>(rhs);
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
void delete_ThresholdDecider_uint8_int16_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ThresholdDecider<uint8_t,int16_t,uint>>*>(ptr);
  delete storage;
}
