
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__leafs.h"
#include <../../include/fertilized/leafs/regressionleafmanager.h>

using namespace fertilized;




          void * getRegressionLeafManager_f (

        void * selection_provider,
        size_t n_valids_to_use,
        void * regression_calculator,
        void * entropy_function,
        int use_fallback_constant_regression,
        int num_threads,
        unsigned int summary_mode
) {
  // From C types conversions.

    auto __converted_selection_provider = *reinterpret_cast<std::shared_ptr<fertilized::IFeatureSelectionProvider>*>(selection_provider);
              

    auto __converted_regression_calculator = *reinterpret_cast<std::shared_ptr<fertilized::IRegressionCalculator<float>>*>(regression_calculator);
              

    auto __converted_entropy_function = *reinterpret_cast<std::shared_ptr<fertilized::IEntropyFunction<float>>*>(entropy_function);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<RegressionLeafManager<float>>(
    new RegressionLeafManager<
              float
>(
          __converted_selection_provider,
          n_valids_to_use,
          __converted_regression_calculator,
          __converted_entropy_function,
          use_fallback_constant_regression,
          num_threads,
          summary_mode
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqRegressionLeafManager_f (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<RegressionLeafManager<float>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ILeafManager<float, float, std::pair<std::shared_ptr<std::vector<float> >, std::shared_ptr<std::vector<float> > >, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float> >, std::shared_ptr<std::vector<float> > >, float> > >>*>(rhs);
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
void delete_RegressionLeafManager_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<RegressionLeafManager<float>>*>(ptr);
  delete storage;
}
