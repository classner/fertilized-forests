
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__bagging.h"
#include <fertilized/bagging/ibaggingstrategy.h>

using namespace fertilized;


// Destructor.
void delete_IBaggingStrategy_d_d_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IBaggingStrategy<double,double,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
