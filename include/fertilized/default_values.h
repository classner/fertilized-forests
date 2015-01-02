// Author: Christoph Lassner
#pragma once
#ifndef FERTILIZED_DEFAULT_VALUES_H_
#define FERTILIZED_DEFAULT_VALUES_H_

#include <vector>
#include <string>
#include <memory>

#include "./global.h"
#include "./fertilized_fwd.h"

namespace fertilized {
  // Library internal (do not need to be defined in exported languages.
  static const float _HOUGH_DEFAULT_INDUCED_VALUES[] = {2.f, 1.1f};
  static const std::shared_ptr<IEntropyFunction<float>> _NULL_ENTROPY_PTR(std::shared_ptr<IEntropyFunction<float>>(nullptr, [](void*){}));

  // These are used as default arguments for functions. They have to be
  // redefined in other language interfaces.
  static const std::vector<std::string> _DEFAULT_ENTROPY_VEC_2(2, "induced");
  static const std::vector<float> _DEFAULT_ENTROPY_P1_2(_HOUGH_DEFAULT_INDUCED_VALUES, _HOUGH_DEFAULT_INDUCED_VALUES+2);
}  // namespace fertilized
#endif  // FERTILIZED_DEFAULT_VALUES_H_