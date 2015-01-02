/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_GAINS_ENTROPYGAIN_H_
#define FERTILIZED_GAINS_ENTROPYGAIN_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

#include "../global.h"
#include "../impurities/ientropyfunction.h"
#include "../util/checks.h"
#include "./igaincalculator.h"

namespace fertilized {
  /**
   * \brief Calculates the gain as difference of current entropy and the
   * weighted sum of subgroup entropies.
   *
   * Works correctly up to a total sum of elements of
   * min(numeric_limits<float>::max(), numeric_limits<input_dtype>::max())
   * and the limitations of the selected entropy function.
   * Speed optimized function that does no checks in release mode!
   *
   * \param input_dtype The datatype for counting class members. This might
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
  template <typename input_dtype>
  class EntropyGain : public IGainCalculator<input_dtype> {
   public:
    typedef IEntropyFunction<input_dtype> entropy_func_t;

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param entropy_function shared(IEntropyFunction<float>)
     *   The entropy to use for gain calculation.
     */
    explicit EntropyGain(const std::shared_ptr<entropy_func_t> &entropy_function)
      : entropy_function(entropy_function) {}

    /** Gets a gain approximation that can be used inside an `argmax` function. */
    float approx(const std::vector<input_dtype> &members_numbers_left,
                 const std::vector<input_dtype> &members_numbers_right) {
      FASSERT(safe_pos_sum_lessoe_than(members_numbers_left));
      FASSERT(safe_pos_sum_lessoe_than(members_numbers_right));
      FASSERT(std::numeric_limits<input_dtype>::max() <=
             std::numeric_limits<float>::max());
      float sum_left = static_cast<float>(
        std::accumulate(members_numbers_left.begin(),
                        members_numbers_left.end(),
                        static_cast<input_dtype>(0)));
      FASSERT(sum_left >= 0.f);
      float sum_right = static_cast<float>(
        std::accumulate(members_numbers_right.begin(),
                        members_numbers_right.end(),
                        static_cast<input_dtype>(0)));
      FASSERT(sum_right >= 0.f);
      FASSERT(std::numeric_limits<float>::max() - sum_left >= sum_right);

      auto sum_complete = sum_left + sum_right;
      if (sum_complete == 0.f)
        return 0.f;
      FASSERT(sum_complete > 0.f);
      return - (sum_left  / sum_complete * (*entropy_function)(members_numbers_left,  sum_left)
               +sum_right / sum_complete * (*entropy_function)(members_numbers_right, sum_right));
    };

    /** Calculates the information gain. */
    float operator()(const float &current_entropy,
      const std::vector<input_dtype> &members_numbers_left,
      const std::vector<input_dtype> &members_numbers_right) {
        return current_entropy +
                approx(members_numbers_left, members_numbers_right);
    };

    /** Calculates the information gain. */
    float operator()(
        const std::vector<input_dtype> &members_numbers_left,
        const std::vector<input_dtype> &members_numbers_right) {
      FASSERT(safe_pos_sum_lessoe_than(members_numbers_left,
                                      members_numbers_right));
      std::vector<input_dtype> combined;
      // OPTIMIZE: This is a clear hotspot: it takes about half of the
      // gain calculation time. It is avoided where possible anyway by
      // calling either approx or the other operator() overload.
      combined.reserve(members_numbers_left.size());
      std::transform(members_numbers_left.begin(),
                     members_numbers_left.end(),
                     members_numbers_right.begin(),
                     std::back_inserter(combined),
                     std::plus<input_dtype>());
      float entropy = (*entropy_function)(combined);

      return operator()(entropy, members_numbers_left, members_numbers_right);
    };

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    bool operator==(const IGainCalculator<input_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<EntropyGain<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_ef = *entropy_function == *(rhs_c -> entropy_function);
        return eq_ef;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<IGainCalculator<input_dtype>>(*this);
      ar & entropy_function;
    }
#endif

   protected:
    EntropyGain() {}

   private:
    std::shared_ptr<entropy_func_t> entropy_function;
  };
};  // namespace fertilized
#endif  // FERTILIZED_GAINS_ENTROPYGAIN_H_