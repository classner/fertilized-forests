// Author: Christoph Lassner.
#include "./global.h"

#include <vector>

#include "./matlab_headers/objectvector.h"

void *createObjectVector() {
  return reinterpret_cast<void*>(new std::vector<void*>());
};

void deleteObjectVector(void *inst) {
  delete reinterpret_cast<std::vector<void*>*>(inst);
};

void appendToObjectVector(void *inst, void *obj) {
  reinterpret_cast<std::vector<void*>*>(inst) -> push_back(obj);
};
