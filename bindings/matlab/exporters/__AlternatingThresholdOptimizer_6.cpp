
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__threshold_optimizers.h"
#include <fertilized/threshold_optimizers/alternatingthresholdoptimizer.h>

using namespace fertilized;




          void * getAlternatingThresholdOptimizer_uint8_uint8_uint (

        void * opt1,
        void * opt2,
        unsigned int random_seed
) {
  // From C types conversions.

    auto __converted_opt1 = *reinterpret_cast<std::shared_ptr<fertilized::AlternatingThresholdOptimizer<uint8_t, uint8_t, uint>::IThresholdOptimizer_t>*>(opt1);
              

    auto __converted_opt2 = *reinterpret_cast<std::shared_ptr<fertilized::AlternatingThresholdOptimizer<uint8_t, uint8_t, uint>::IThresholdOptimizer_t>*>(opt2);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<AlternatingThresholdOptimizer<uint8_t,uint8_t,uint>>(
    new AlternatingThresholdOptimizer<
              uint8_t,
              uint8_t,
              uint
>(
          __converted_opt1,
          __converted_opt2,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqAlternatingThresholdOptimizer_uint8_uint8_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<AlternatingThresholdOptimizer<uint8_t,uint8_t,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IThresholdOptimizer<uint8_t, uint8_t, uint>>*>(rhs);
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
void delete_AlternatingThresholdOptimizer_uint8_uint8_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<AlternatingThresholdOptimizer<uint8_t,uint8_t,uint>>*>(ptr);
  delete storage;
}
