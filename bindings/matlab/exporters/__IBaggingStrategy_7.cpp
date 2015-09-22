
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__bagging.h"
#include <fertilized/bagging/ibaggingstrategy.h>

using namespace fertilized;


// Destructor.
void delete_IBaggingStrategy_f_f_f_rpf_vprpff(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IBaggingStrategy<float,float,float,std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>>>*>(ptr);
  delete storage;
}
