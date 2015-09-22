
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__execution_strategies.h"
#include <fertilized/execution_strategies/localexecutionstrategy.h>

using namespace fertilized;




          void * getLocalExecutionStrategy_d_d_d_rpd_vprpfd (

        int num_threads
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<LocalExecutionStrategy<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>(
    new LocalExecutionStrategy<
              double,
              double,
              double,
              std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,
              std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
>(
          num_threads
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_LocalExecutionStrategy_d_d_d_rpd_vprpfd(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<LocalExecutionStrategy<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(ptr);
  delete storage;
}
