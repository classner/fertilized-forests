
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__bagging.h"
#include <fertilized/bagging/equaldistbagging.h>

using namespace fertilized;




          void * getEqualDistBagging_uint8_int16_int16_hp_vhp (

) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<EqualDistBagging<uint8_t,int16_t,int16_t,std::pair<float, std::shared_ptr<std::vector<int16_t>>>,std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>>>(
    new EqualDistBagging<
              uint8_t,
              int16_t,
              int16_t,
              std::pair<float, std::shared_ptr<std::vector<int16_t>>>,
              std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
>(
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqEqualDistBagging_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<EqualDistBagging<uint8_t,int16_t,int16_t,std::pair<float, std::shared_ptr<std::vector<int16_t>>>,std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IBaggingStrategy<uint8_t, int16_t, int16_t, std::pair<float, std::shared_ptr<std::vector<int16_t>>>, std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>>>*>(rhs);
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
void delete_EqualDistBagging_uint8_int16_int16_hp_vhp(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<EqualDistBagging<uint8_t,int16_t,int16_t,std::pair<float, std::shared_ptr<std::vector<int16_t>>>,std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>>>*>(ptr);
  delete storage;
}
