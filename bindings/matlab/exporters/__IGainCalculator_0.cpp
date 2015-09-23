
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__gains.h"
#include <../../include/fertilized/gains/igaincalculator.h>

using namespace fertilized;


// Destructor.
void delete_IGainCalculator_f(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<IGainCalculator<float>>*>(ptr);
  delete storage;
}
