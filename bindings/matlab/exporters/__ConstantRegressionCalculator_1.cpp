
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__regression.h"
#include <fertilized/regression/constantregressioncalculator.h>

using namespace fertilized;




          void * getConstantRegressionCalculator_d (

) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<ConstantRegressionCalculator<double>>(
    new ConstantRegressionCalculator<
              double
>(
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqConstantRegressionCalculator_d (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ConstantRegressionCalculator<double>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IRegressionCalculator<double>>*>(rhs);
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
void delete_ConstantRegressionCalculator_d(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ConstantRegressionCalculator<double>>*>(ptr);
  delete storage;
}
