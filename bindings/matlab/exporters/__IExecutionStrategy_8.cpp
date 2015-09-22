
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__execution_strategies.h"
#include <fertilized/execution_strategies/iexecutionstrategy.h>

using namespace fertilized;


// Destructor.
void delete_IExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IExecutionStrategy<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(ptr);
  delete storage;
}
