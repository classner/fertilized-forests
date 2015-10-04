/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_FEATCALCPARAMSET_H_
#define FERTILIZED_FEATURES_FEATCALCPARAMSET_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include "../global.h"
#include "../types.h"

namespace fertilized {
  /**
   * \brief Can be specialized to any necessary parameters used by a feature
   * calculator.
   *
   * This was planned as an implementable interface, however it must be a
   * single, plain POD object, since it might be transferred forth and back
   * between host and MIC device.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   *
   * -----
   */
  class FeatCalcParamSet {
   public:
    float weights[9];
    float offsets[2];

    /** Deep comparison operator. */
    bool operator==(const FeatCalcParamSet &rhs) const {
      bool equiv = true;
      for (int i = 0; i < 9; ++i) {
        if (weights[i] != rhs.weights[i]) {
          equiv = false;
          break;
        }
      }
      for (int i = 0; i < 2; ++i) {
        if (offsets[i] != rhs.offsets[i]) {
          equiv = false;
          break;
        }
      }
      return equiv;
    }

    #ifdef SERIALIZATION_ENABLED
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const uint file_version) {
          // Boost serialization automagically detects the array and serializes
          // all elements (http://www.boost.org/doc/libs/1_55_0/libs/serialization/doc/tutorial.html#arrays).
          ar & weights;
          ar & offsets;
        }
    #endif
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_FEATCALCPARAMSET_H_
