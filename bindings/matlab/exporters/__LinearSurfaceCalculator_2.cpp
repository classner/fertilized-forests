
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <../../include/fertilized/features/linearsurfacecalculator.h>

using namespace fertilized;




          void * getLinearSurfaceCalculator_f_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<LinearSurfaceCalculator<float,uint>>(
    new LinearSurfaceCalculator<
              float,
              uint
>(
          n_params_per_feat_sel,
          n_comb_dims,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqLinearSurfaceCalculator_f_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<LinearSurfaceCalculator<float,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ISurfaceCalculator<float, float, uint>>*>(rhs);
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
void delete_LinearSurfaceCalculator_f_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<LinearSurfaceCalculator<float,uint>>*>(ptr);
  delete storage;
}
