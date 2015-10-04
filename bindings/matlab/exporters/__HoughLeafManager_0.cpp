
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__leafs.h"
#include <../../include/fertilized/leafs/houghleafmanager.h>

using namespace fertilized;




          void * getHoughLeafManager_uint8_int16 (

        unsigned int n_classes,
        size_t annot_dim
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<HoughLeafManager<uint8_t,int16_t>>(
    new HoughLeafManager<
              uint8_t,
              int16_t
>(
          n_classes,
          annot_dim
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqHoughLeafManager_uint8_int16 (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<HoughLeafManager<uint8_t,int16_t>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::ILeafManager<uint8_t, int16_t, std::pair<float, std::shared_ptr<std::vector<int16_t> > >, std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t> > > > >>*>(rhs);
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
void delete_HoughLeafManager_uint8_int16(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<HoughLeafManager<uint8_t,int16_t>>*>(ptr);
  delete storage;
}
