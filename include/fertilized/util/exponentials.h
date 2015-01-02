/* Author: Christoph Lassner */
#pragma once
#ifndef FERTILIZED_UTIL_EXPONENTIALS_H_
#define FERTILIZED_UTIL_EXPONENTIALS_H_

#include <cmath>

#include "../global.h"

namespace fertilized {
  /** Precomputed value for the calculation of log2. */
  static const float LOG2VAL = logf(2.f);

  /** Portable double pi value. */
  static const double D_PI = 4. * atan(1.);

  /** Precomputed value for the computatio of the differential induced
   * entropy. */
  static const float TWO_PI = static_cast<float>(2. * D_PI);

  /** Precomputed value for the computation of the differential
   * shannon entropy. */
  static const float TWO_PI_E = TWO_PI * expf(1.f);

  /**
   * \brief Computes an int power by an int.
   *
   * Fast implementation using in-place
   * multiplication and bit-shifts only. Original version can be found
   * here: http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int/101613#101613,
   * the signature of the method has been adjusted to unsigned int exp to
   * avoid the mentioned problems with possible negative exponents.
   *
   * \return \f$base^{exp}\f$.
   */
  inline int ipow(int base, unsigned int exp) {
    int result = 1;
    while (exp) {
      if (exp & 1)
        result *= base;
      exp >>= 1;
      base *= base;
    }

    return result;
  };

  /**
   * \brief Computes a float power by an unsigned int.
   *
   * Fast implementation similar
   * to the cryptographic fast int pow ipow. For exp values up to including
   * 5, the calculation is explicitly hard coded.
   *
   * \return \f$base^{exp}\f$.
   */
  inline float fpowi(float base, unsigned int exp) {
    switch (exp) {
    case 0:
      return 1.f;
    case 1:
      return base;
    case 2:
      return base * base;
    case 3:
      return base * base * base;
    case 4:
      return base * base * base * base;
    case 5:
      return base * base * base * base * base;
    default:
      // This version is already a lot faster than fpow.
      float result = 1.f;
      while (exp) {
        if (exp & 1)
          result *= base;
        exp >>= 1;
        base *= base;
      }
      return result;
    }
  };
};  // namespace fertilized
#endif  // FERTILIZED_UTIL_EXPONENTIALS_H_
