
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <../../include/fertilized/features/linearsurfacecalculator.h>

using namespace fertilized;




          void * getLinearSurfaceCalculator_d_d (

        size_t n_params_per_feat_sel,
        size_t n_comb_dims,
        unsigned int random_seed
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<LinearSurfaceCalculator<double,double>>(
    new LinearSurfaceCalculator<
              double,
              double
>(
          n_params_per_feat_sel,
          n_comb_dims,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqLinearSurfaceCalculator_d_d (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<LinearSurfaceCalculator<double,double>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ISurfaceCalculator<double, float, double>>*>(rhs);
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
void delete_LinearSurfaceCalculator_d_d(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<LinearSurfaceCalculator<double,double>>*>(ptr);
  delete storage;
}
