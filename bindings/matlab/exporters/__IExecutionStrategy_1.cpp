
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__execution_strategies.h"
#include <../../include/fertilized/execution_strategies/iexecutionstrategy.h>

using namespace fertilized;


// Destructor.
void delete_IExecutionStrategy_f_f_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IExecutionStrategy<float,float,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
