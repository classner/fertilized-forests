
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <fertilized/data_providers/subsamplingdataprovider.h>

using namespace fertilized;




          void * getSubsamplingDataProvider_uint8_uint (

        size_t max_samples_per_node,
        void * sample_manager,
        unsigned int random_seed
) {
  // From C types conversions.

    auto __converted_sample_manager = *reinterpret_cast<std::shared_ptr<fertilized::ISampleManager<uint8_t, uint>>*>(sample_manager);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<SubsamplingDataProvider<uint8_t,uint>>(
    new SubsamplingDataProvider<
              uint8_t,
              uint
>(
          max_samples_per_node,
          __converted_sample_manager,
          random_seed
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_SubsamplingDataProvider_uint8_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<SubsamplingDataProvider<uint8_t,uint>>*>(ptr);
  delete storage;
}
