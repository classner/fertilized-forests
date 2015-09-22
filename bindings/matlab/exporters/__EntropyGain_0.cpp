
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__gains.h"
#include <fertilized/gains/entropygain.h>

using namespace fertilized;




          void * getEntropyGain_f (

        void * entropy_function
) {
  // From C types conversions.

    auto __converted_entropy_function = *reinterpret_cast<std::shared_ptr<fertilized::EntropyGain<float>::entropy_func_t>*>(entropy_function);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<EntropyGain<float>>(
    new EntropyGain<
              float
>(
          __converted_entropy_function
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqEntropyGain_f (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<EntropyGain<float>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IGainCalculator<float>>*>(rhs);
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
void delete_EntropyGain_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<EntropyGain<float>>*>(ptr);
  delete storage;
}
