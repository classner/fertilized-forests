
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__trainings.h"
#include <fertilized/trainings/itraining.h>

using namespace fertilized;


// Destructor.
void delete_ITraining_d_d_d_rpd_vprpfd(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ITraining<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(ptr);
  delete storage;
}
