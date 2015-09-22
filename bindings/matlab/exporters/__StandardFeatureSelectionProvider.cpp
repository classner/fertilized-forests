
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <fertilized/features/standardfeatureselectionprovider.h>

using namespace fertilized;




void * getStandardFeatureSelectionProvider (

        size_t n_selections_per_node,
        size_t selection_dimension,
        size_t how_many_available,
        size_t max_to_use,
        unsigned int random_seed
) {
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<StandardFeatureSelectionProvider>(
    new StandardFeatureSelectionProvider(
          n_selections_per_node,
          selection_dimension,
          how_many_available,
          max_to_use,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}


int eqStandardFeatureSelectionProvider (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<StandardFeatureSelectionProvider>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IFeatureSelectionProvider>*>(rhs);
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


size_t get_n_available_featuresStandardFeatureSelectionProvider (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<StandardFeatureSelectionProvider>*>(__instance);
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_n_available_features(
  );
#pragma warning( pop )

  return libfunc_result;
}
// Destructor.
void delete_StandardFeatureSelectionProvider(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<StandardFeatureSelectionProvider>*>(ptr);
  delete storage;
}
