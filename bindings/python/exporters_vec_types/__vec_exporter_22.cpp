
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "./vec_exporter.h"

#include <vector>

#include "../global.h"
#include "../util.h"
#include <fertilized/forest.h>

using namespace fertilized;

namespace pyfertilized {
  void __export_vectors_22() {
    custom_vector_from_seq<typename fertilized::Forest<float,float,float,std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>>::tree_ptr_t>();
  };
}  // namespace pyfertilized