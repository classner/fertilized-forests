
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__regression.h"
#include <fertilized/regression/linearregressioncalculator.h>

using namespace fertilized;




          void * getLinearRegressionCalculator_f (

        int force_numerical_stability,
        void * numerical_zero_threshold
) {
  // From C types conversions.

    auto __shptr_numerical_zero_threshold = *reinterpret_cast<std::shared_ptr<float>*>(numerical_zero_threshold);
    auto &__converted_numerical_zero_threshold = *(__shptr_numerical_zero_threshold.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<LinearRegressionCalculator<float>>(
    new LinearRegressionCalculator<
              float
>(
          force_numerical_stability,
          __converted_numerical_zero_threshold
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqLinearRegressionCalculator_f (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<LinearRegressionCalculator<float>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IRegressionCalculator<float>>*>(rhs);
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
void delete_LinearRegressionCalculator_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<LinearRegressionCalculator<float>>*>(ptr);
  delete storage;
}
