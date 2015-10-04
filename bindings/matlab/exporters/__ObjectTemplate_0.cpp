
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__rootdir.h"
#include <../../include/fertilized/./objecttemplate.h>

using namespace fertilized;




          void * getObjectTemplate_i_i_uint_fv_fv (

        unsigned int example_param
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<ObjectTemplate<int,int,uint,std::vector<float>,std::vector<float>>>(
    new ObjectTemplate<
              int,
              int,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          example_param
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		
// Destructor.
void delete_ObjectTemplate_i_i_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<ObjectTemplate<int,int,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
