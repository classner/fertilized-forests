
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__threshold_optimizers.h"
#include <fertilized/threshold_optimizers/varianceclassificationthresholdoptimizer.h>

using namespace fertilized;




          void * getVarianceClassificationThresholdOptimizer_d_d_uint (

        size_t n_thresholds,
        size_t n_classes,
        size_t offset_dim,
        float gain_threshold,
        unsigned int random_seed
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<VarianceClassificationThresholdOptimizer<double,double,uint>>(
    new VarianceClassificationThresholdOptimizer<
              double,
              double,
              uint
>(
          n_thresholds,
          n_classes,
          offset_dim,
          gain_threshold,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqVarianceClassificationThresholdOptimizer_d_d_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VarianceClassificationThresholdOptimizer<double,double,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IThresholdOptimizer<double, double, uint>>*>(rhs);
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
void delete_VarianceClassificationThresholdOptimizer_d_d_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<VarianceClassificationThresholdOptimizer<double,double,uint>>*>(ptr);
  delete storage;
}
