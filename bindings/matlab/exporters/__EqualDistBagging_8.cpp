
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__bagging.h"
#include <fertilized/bagging/equaldistbagging.h>

using namespace fertilized;




          void * getEqualDistBagging_d_d_d_rpd_vprpfd (

) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<EqualDistBagging<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>(
    new EqualDistBagging<
              double,
              double,
              double,
              std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,
              std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
>(
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          int eqEqualDistBagging_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<EqualDistBagging<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::IBaggingStrategy<double, double, double, std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>, std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(rhs);
    auto &__converted_rhs = *(__shptr_rhs.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> operator==(
          __converted_rhs
  );
#pragma warning( pop )

  return libfunc_result;
}		
// Destructor.
void delete_EqualDistBagging_d_d_d_rpd_vprpfd(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<EqualDistBagging<double,double,double,std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>>>*>(ptr);
  delete storage;
}
