/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_IMPURITIES_SHANNONENTROPY_H_
#define FERTILIZED_IMPURITIES_SHANNONENTROPY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <numeric>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/exponentials.h"
#include "./ientropyfunction.h"

namespace fertilized {
  /**
   * \brief Computes the classical Shannon-Entropy.
   *
   * Works correctly up to a total sum of elements of
   * numeric_limits<input_dtype>::max().
   *
   * For classes \f$C={c_1, \ldots, c_n}\f$, the Shannon entropy is defined as
   * \f[-\sum_{c\in C}p_z\cdot \log_2 p_z.\f]
   *
   * The differential Shannon entropy for a normal distribution with covariance
   * matrix \f$\Sigma\f$ in \f$n\f$ dimensions is defined as
   * \f[\frac{1}{2}\log\left((2\pi e)^n\left|\Sigma\right|\right).\f]
   *
   * \ingroup fertilizedimpuritiesGroup
   *
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
  class ShannonEntropy : public IEntropyFunction<input_dtype> {
   public:

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
    ShannonEntropy() {}

    ~ShannonEntropy() {}

    /**
     * The method is supposed to be fast and hence no checking for the validity
     * of fsum is done in release mode!
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param class_member_numbers Vector 
     *   The class member counts (class histogram).
     * \param fsum float 
     *   The total of the class_member_numbers Vector.
     * \return The calculated entropy value.
     */
    float operator()(const std::vector<input_dtype> &class_members_numbers,
                     const float &fsum) const {
      // In debug mode, run checks.
      FASSERT(static_cast<float>(
        std::accumulate(class_members_numbers.begin(),
                        class_members_numbers.end(),
                        static_cast<input_dtype>(0))) == fsum);
      FASSERT(safe_pos_sum_lessoe_than(class_members_numbers));

      // Deal with the special case quickly.
      if (fsum == 0.f)
        return 0.f;

      float entropy_sum = 0.f;
      float quot;
      // Calculate classical entropy.
      for (const auto &member_number : class_members_numbers) {
        // The value -0*log2(0) is defined to be 0, according to the limit
        // lim_{p->0}{p*log2(p)}.
        if (member_number == 0)
          continue;
        // All good, so calculate the normal parts.
        quot = static_cast<float>(member_number) / fsum;
        entropy_sum -= quot * logf(quot);
      }
      return entropy_sum / LOG2VAL;
    };

    /**
     * \brief Differential shannon entropy of the normal distribution.
     *
     * Calculates the differential entropy of a normal distribution with the
     * specified determinant value of the covariance matrix.
     */
    float differential_normal(const float &det, const uint &dimensions) const {
      FASSERT(dimensions > 0);
      if (det == 0.f) {
        return - std::numeric_limits<float>::infinity();
      }
      if (det < 0.f) {
        // This is complete bollocks.
        throw Fertilized_Exception("Covariance matrix with negative "
          "determinant occured.");
      }
      return 0.5f * logf(fpowi(TWO_PI_E, dimensions) * det);
    }

    using IEntropyFunction<input_dtype>::operator();
    using IEntropyFunction<input_dtype>::differential_normal;

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
    bool operator==(const IEntropyFunction<input_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<ShannonEntropy<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        return true;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const {
      ar << boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    template<class Archive>
    void load(Archive & ar, const unsigned int version) {
      ar >> boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
    }
#endif
   private:
    DISALLOW_COPY_AND_ASSIGN(ShannonEntropy<input_dtype>);
  };
}  // namespace fertilized
#endif  // FERTILIZED_IMPURITIES_SHANNONENTROPY_H_