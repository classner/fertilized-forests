
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__trainings.h"
#include <../../include/fertilized/trainings/itraining.h>

using namespace fertilized;


// Destructor.
void delete_ITraining_i_i_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ITraining<int,int,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
