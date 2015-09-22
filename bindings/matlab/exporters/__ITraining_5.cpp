
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__trainings.h"
#include <fertilized/trainings/itraining.h>

using namespace fertilized;


// Destructor.
void delete_ITraining_uint8_int16_int16_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ITraining<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
