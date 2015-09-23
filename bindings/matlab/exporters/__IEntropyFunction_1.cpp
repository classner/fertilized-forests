
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__impurities.h"
#include <../../include/fertilized/impurities/ientropyfunction.h>

using namespace fertilized;


// Destructor.
void delete_IEntropyFunction_uint(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IEntropyFunction<uint>>*>(ptr);
  delete storage;
}
