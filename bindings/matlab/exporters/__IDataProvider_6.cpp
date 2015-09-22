
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__data_providers.h"
#include <fertilized/data_providers/idataprovider.h>

using namespace fertilized;


// Destructor.
void delete_IDataProvider_f_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IDataProvider<float,float>>*>(ptr);
  delete storage;
}
