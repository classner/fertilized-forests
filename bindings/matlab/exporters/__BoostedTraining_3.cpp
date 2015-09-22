
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__trainings.h"
#include <fertilized/trainings/boostedtraining.h>

using namespace fertilized;




          void * getBoostedTraining_uint8_uint8_uint_fv_fv (

        void * boosting_strategy
) {
  // From C types conversions.

    auto __converted_boosting_strategy = *reinterpret_cast<std::shared_ptr<fertilized::BoostedTraining<uint8_t, uint8_t, uint, std::vector<float>, std::vector<float>>::boost_strat_t>*>(boosting_strategy);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<BoostedTraining<uint8_t,uint8_t,uint,std::vector<float>,std::vector<float>>>(
    new BoostedTraining<
              uint8_t,
              uint8_t,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          __converted_boosting_strategy
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqBoostedTraining_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<BoostedTraining<uint8_t,uint8_t,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ITraining<uint8_t, uint8_t, uint, std::vector<float>, std::vector<float>>>*>(rhs);
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
void delete_BoostedTraining_uint8_uint8_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<BoostedTraining<uint8_t,uint8_t,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
