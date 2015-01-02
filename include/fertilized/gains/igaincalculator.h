/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_GAINS_IGAINCALCULATOR_H_
#define FERTILIZED_GAINS_IGAINCALCULATOR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <vector>

#include "../global.h"
#include "../types.h"

namespace fertilized {
  /**
   * \brief Interface for a gain calculator class.
   *
   * A gain calculator must have an overloaded () operator with the
   * according parameters and an approx function that returns a fast
   * approximation of the gain (can return the original gain if no
   * approximation is available). The approximation is used to find the
   * best split position and only for that the actual gain is computed.
   *
   * \param counting_dtype The datatype for counting class members. This might
   * be a float if sample weights are used.
   *
   * \ingroup fertilizedgainsGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float
   * - uint
   * .
   * Soil type always:
   * - float
   * .
   *
   * -----
   */
  template <typename counting_dtype>
  class IGainCalculator {
   public:
    virtual ~IGainCalculator() {}

    /** Calculates the exact gain for the two subsets. */
    virtual float operator()(
      const std::vector<counting_dtype> &members_numbers_left,
      const std::vector<counting_dtype> &members_numbers_right) VIRTUAL(float);

    /** Calculates the exact gain for the two subsets and uses the provided `current_entropy`. */
    virtual float operator()(const float &current_entropy,
      const std::vector<counting_dtype> &members_numbers_left,
      const std::vector<counting_dtype> &members_numbers_right) VIRTUAL(float);

    /** Calculates an approximation for the gain of the two subsets that gain be used inside an `argmax` function. */
    virtual float approx(
      const std::vector<counting_dtype> &members_numbers_left,
      const std::vector<counting_dtype> &members_numbers_right) VIRTUAL(float);

    /**
     * Deep equality comparison.
     */
    virtual bool operator==(const IGainCalculator<counting_dtype> &rhs)
      const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    IGainCalculator() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(IGainCalculator<counting_dtype>);
  };
};  // namespace fertilized
#endif  // FERTILIZED_GAINS_IGAINCALCULATOR_H_
