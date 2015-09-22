
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <fertilized/features/linearsurfacecalculator.h>

using namespace fertilized;




          void * getLinearSurfaceCalculator_i_uint (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<LinearSurfaceCalculator<int,uint>>(
    new LinearSurfaceCalculator<
              int,
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


          int eqLinearSurfaceCalculator_i_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<LinearSurfaceCalculator<int,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ISurfaceCalculator<int, float, uint>>*>(rhs);
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
void delete_LinearSurfaceCalculator_i_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<LinearSurfaceCalculator<int,uint>>*>(ptr);
  delete storage;
}
