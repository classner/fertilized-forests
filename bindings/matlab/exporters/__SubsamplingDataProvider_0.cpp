
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <../../include/fertilized/data_providers/subsamplingdataprovider.h>

using namespace fertilized;




          void * getSubsamplingDataProvider_uint8_int16 (

        size_t max_samples_per_node,
        void * sample_manager,
        unsigned int random_seed
) {
  // From C types conversions.

    auto __converted_sample_manager = *reinterpret_cast<std::shared_ptr<fertilized::ISampleManager<uint8_t, int16_t>>*>(sample_manager);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<SubsamplingDataProvider<uint8_t,int16_t>>(
    new SubsamplingDataProvider<
              uint8_t,
              int16_t
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
void delete_SubsamplingDataProvider_uint8_int16(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<SubsamplingDataProvider<uint8_t,int16_t>>*>(ptr);
  delete storage;
}
