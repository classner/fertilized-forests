
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <fertilized/features/volumefeatureselectionprovider.h>

using namespace fertilized;




void * getVolumeFeatureSelectionProvider (

        size_t selection_dimension,
        size_t size_x,
        size_t size_y,
        size_t size_z,
        size_t how_many_per_node,
        unsigned int random_seed
) {
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<VolumeFeatureSelectionProvider>(
    new VolumeFeatureSelectionProvider(
          selection_dimension,
          size_x,
          size_y,
          size_z,
          how_many_per_node,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}


int eqVolumeFeatureSelectionProvider (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(__instance);
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


size_t get_size_xVolumeFeatureSelectionProvider (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(__instance);
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_size_x(
  );
#pragma warning( pop )

  return libfunc_result;
}


size_t get_size_yVolumeFeatureSelectionProvider (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(__instance);
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_size_y(
  );
#pragma warning( pop )

  return libfunc_result;
}


size_t get_size_zVolumeFeatureSelectionProvider (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(__instance);
  // From C types conversions.


#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_size_z(
  );
#pragma warning( pop )

  return libfunc_result;
}


size_t get_n_available_featuresVolumeFeatureSelectionProvider (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(__instance);
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
void delete_VolumeFeatureSelectionProvider(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<VolumeFeatureSelectionProvider>*>(ptr);
  delete storage;
}
