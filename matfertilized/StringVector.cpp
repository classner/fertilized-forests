// Author: Christoph Lassner.
#include "./global.h"

#include <vector>
#include <string>
#include <cstdint>

#include "./matlab_headers/stringvector.h"

void *createStringVector() {
  return reinterpret_cast<void*>(new std::vector<std::string>());
};

void deleteStringVector(void *inst) {
  delete reinterpret_cast<std::vector<std::string>*>(inst);
};

void appendToStringVector(void *inst, char *str) {
  reinterpret_cast<std::vector<std::string>*>(inst) -> push_back(std::string(str));
};
