
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__threshold_optimizers.h"
#include <../../include/fertilized/threshold_optimizers/regressionthresholdoptimizer.h>

using namespace fertilized;




          void * getRegressionThresholdOptimizer_f_f (

        size_t n_thresholds,
        void * regression_calculator,
        void * entropy_function,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
) {
  // From C types conversions.

    auto __converted_regression_calculator = *reinterpret_cast<std::shared_ptr<fertilized::IRegressionCalculator<float>>*>(regression_calculator);
              

    auto __converted_entropy_function = *reinterpret_cast<std::shared_ptr<fertilized::IEntropyFunction<float>>*>(entropy_function);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<RegressionThresholdOptimizer<float,float>>(
    new RegressionThresholdOptimizer<
              float,
              float
>(
          n_thresholds,
          __converted_regression_calculator,
          __converted_entropy_function,
          gain_threshold,
          annotation_step,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqRegressionThresholdOptimizer_f_f (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<RegressionThresholdOptimizer<float,float>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IThresholdOptimizer<float, float, float>>*>(rhs);
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
void delete_RegressionThresholdOptimizer_f_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<RegressionThresholdOptimizer<float,float>>*>(ptr);
  delete storage;
}
