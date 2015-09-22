
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__leafs.h"
#include <fertilized/leafs/boostingleafmanager.h>

using namespace fertilized;




          void * getBoostingLeafManager_uint8_int16 (

        unsigned int n_classes
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<BoostingLeafManager<uint8_t,int16_t>>(
    new BoostingLeafManager<
              uint8_t,
              int16_t
>(
          n_classes
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqBoostingLeafManager_uint8_int16 (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<BoostingLeafManager<uint8_t,int16_t>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ILeafManager<uint8_t, int16_t, std::vector<float>, std::vector<float> >>*>(rhs);
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
void delete_BoostingLeafManager_uint8_int16(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<BoostingLeafManager<uint8_t,int16_t>>*>(ptr);
  delete storage;
}
