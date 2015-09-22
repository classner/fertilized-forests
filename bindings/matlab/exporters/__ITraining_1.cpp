
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__trainings.h"
#include <fertilized/trainings/itraining.h>

using namespace fertilized;


// Destructor.
void delete_ITraining_f_f_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ITraining<float,float,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
