
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <fertilized/features/directpatchdifferencesurfcalculator.h>

using namespace fertilized;




          void * getDirectPatchDifferenceSurfCalculator_uint8_int16_int16 (

        size_t psx,
        size_t psy,
        size_t psz,
        int luc
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<DirectPatchDifferenceSurfCalculator<uint8_t,int16_t,int16_t>>(
    new DirectPatchDifferenceSurfCalculator<
              uint8_t,
              int16_t,
              int16_t
>(
          psx,
          psy,
          psz,
          luc
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqDirectPatchDifferenceSurfCalculator_uint8_int16_int16 (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<DirectPatchDifferenceSurfCalculator<uint8_t,int16_t,int16_t>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ISurfaceCalculator<uint8_t, int16_t, int16_t>>*>(rhs);
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
void delete_DirectPatchDifferenceSurfCalculator_uint8_int16_int16(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<DirectPatchDifferenceSurfCalculator<uint8_t,int16_t,int16_t>>*>(ptr);
  delete storage;
}
