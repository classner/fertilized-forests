
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__threshold_optimizers.h"
#include <../../include/fertilized/threshold_optimizers/regressionthresholdoptimizer.h>

using namespace fertilized;




          void * getRegressionThresholdOptimizer_d_d (

        size_t n_thresholds,
        void * regression_calculator,
        void * entropy_function,
        float gain_threshold,
        size_t annotation_step,
        unsigned int random_seed
) {
  // From C types conversions.

    auto __converted_regression_calculator = *reinterpret_cast<std::shared_ptr<fertilized::IRegressionCalculator<double>>*>(regression_calculator);
              

    auto __converted_entropy_function = *reinterpret_cast<std::shared_ptr<fertilized::IEntropyFunction<float>>*>(entropy_function);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<RegressionThresholdOptimizer<double,double>>(
    new RegressionThresholdOptimizer<
              double,
              double
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


          int eqRegressionThresholdOptimizer_d_d (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<RegressionThresholdOptimizer<double,double>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IThresholdOptimizer<double, double, double>>*>(rhs);
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
void delete_RegressionThresholdOptimizer_d_d(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<RegressionThresholdOptimizer<double,double>>*>(ptr);
  delete storage;
}
