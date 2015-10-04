
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__threshold_optimizers.h"
#include <../../include/fertilized/threshold_optimizers/classificationthresholdoptimizer.h>

using namespace fertilized;




          void * getClassificationThresholdOptimizer_i_i_uint (

        int use_fast_search_approximation,
        size_t n_classes,
        void * gain_calculator,
        float gain_threshold,
        size_t annotation_step
) {
  // From C types conversions.

    auto __converted_gain_calculator = *reinterpret_cast<std::shared_ptr<fertilized::IGainCalculator<float>>*>(gain_calculator);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<ClassificationThresholdOptimizer<int,int,uint>>(
    new ClassificationThresholdOptimizer<
              int,
              int,
              uint
>(
          use_fast_search_approximation,
          n_classes,
          __converted_gain_calculator,
          gain_threshold,
          annotation_step
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqClassificationThresholdOptimizer_i_i_uint (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<ClassificationThresholdOptimizer<int,int,uint>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IThresholdOptimizer<int, int, uint>>*>(rhs);
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
void delete_ClassificationThresholdOptimizer_i_i_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ClassificationThresholdOptimizer<int,int,uint>>*>(ptr);
  delete storage;
}
