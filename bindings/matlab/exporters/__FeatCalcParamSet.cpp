
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__features.h"
#include <../../include/fertilized/features/featcalcparamset.h>

using namespace fertilized;


// Destructor.
void delete_FeatCalcParamSet(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<FeatCalcParamSet>*>(ptr);
  delete storage;
}
