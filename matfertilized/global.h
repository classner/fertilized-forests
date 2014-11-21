/* Author: Christoph Lassner. */
#pragma once
#ifndef MATFERTILIZED_GLOBAL_H_
#define MATFERTILIZED_GLOBAL_H_

#ifdef __cplusplus
#include <fertilized/global.h>
#endif
#include "matlab_headers/global.h"
#include <memory>
#include <cstddef>
#include <vector>

template <typename T>
void *copy_to_heap(T &t) {
  return static_cast<void*>(new T(t));
}

template <typename T>
std::shared_ptr<T> copy_from_heap(void * t) {
  auto * convptr = static_cast<std::shared_ptr<T>*>(t);
  return *convptr;
}

template <typename T>
std::vector<T> recover_vec_types(const std::vector<void*> &target) {
  std::vector<T> result;
  for (std::size_t i = 0; i < target.size(); ++i) {
    result.push_back(*reinterpret_cast<T*>(target[i]));
  }
  return result;
}

#endif  // MATFERTILIZED_GLOBAL_H_
