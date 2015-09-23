
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__impurities.h"
#include <../../include/fertilized/impurities/ientropyfunction.h>

using namespace fertilized;


// Destructor.
void delete_IEntropyFunction_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IEntropyFunction<float>>*>(ptr);
  delete storage;
}
