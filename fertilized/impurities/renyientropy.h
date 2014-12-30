/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_IMPURITIES_RENYIENTROPY_H_
#define FERTILIZED_IMPURITIES_RENYIENTROPY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <numeric>
#include <limits>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/exponentials.h"
#include "./ientropyfunction.h"
#include "./shannonentropy.h"
#include "./inducedentropy.h"
#include "./classificationerror.h"

namespace fertilized {
  /**
   * \brief Computes the Renyi entropy.
   *
   * Works correctly up to a total sum of elements of
   * numeric_limits<input_dtype>::max().
   *
   * This is the Renyi entropy, as introduced by Alfred Renyi
   * (see http://en.wikipedia.org/wiki/R%C3%A9nyi_entropy).
   *
   * \ingroup fertilizedimpuritiesGroup
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
  class RenyiEntropy : public IEntropyFunction<input_dtype> {
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
     *
     * \param alpha float>0.f
     *   The entropy parameter.
     */
    explicit RenyiEntropy(const float &alpha)
      : q(alpha) {
      if (q <= 0.f) {
        throw Fertilized_Exception("alpha must be > 0.f.");
      }

      shannon_entropy = std::unique_ptr<ShannonEntropy<input_dtype>>(
                            new ShannonEntropy<input_dtype>());
      induced_p = std::unique_ptr<InducedEntropy<input_dtype>>(
                            new InducedEntropy<input_dtype>(q));
      classification_error = std::unique_ptr<ClassificationError<input_dtype>>(
                            new ClassificationError<input_dtype>());
    }

    ~RenyiEntropy() {};

    /**
     * The method is supposed to be fast and hence no checking for the validity
     * of fsum is done in release mode!
     *
     * \param class_member_numbers Class distribution histogram.
     * \return The calculated entropy value.
     */
    float operator()(const std::vector<input_dtype> &class_members_numbers,
                     const float &fsum) const {
      if (q == 1.f) {
        return shannon_entropy -> operator()(class_members_numbers, fsum);
      }
      if (q == std::numeric_limits<float>::infinity()) {
        return -logf(-(classification_error -> operator()(class_members_numbers, fsum)-1.f));
      }
      // In debug mode, run checks.
      FASSERT(static_cast<float>(
        std::accumulate(class_members_numbers.begin(),
                        class_members_numbers.end(),
                        static_cast<float>(0))) == fsum);
      FASSERT(safe_pos_sum_lessoe_than(class_members_numbers));

      // Deal with the special case quickly.
      if (fsum == 0.f)
        return 0.f;

      // Cast only once and save time.
      float entropy_sum = 0.f;
      float quot;
      if (ceilf(q) == q || floorf(q) == q) {
        // q is a whole number. Use a faster implementation.
        const uint whole_q = static_cast<uint>(q);
        // Calculate.
        for (const auto &member_number : class_members_numbers) {
          quot = static_cast<float>(member_number) / fsum;
          entropy_sum += fpowi(quot, whole_q);
        }
      } else {
        // p is not a whole number.
        // Calculate.
        for (const auto &member_number : class_members_numbers) {
          quot = static_cast<float>(member_number) / fsum;
          entropy_sum += powf(quot, q);
        }
      }
      return logf(entropy_sum) / (1.f - q);
    };

    /**
     * \brief Differential Renyi entropy of the normal distribution.
     *
     * Calculates the differential entropy of a normal distribution with the
     * determinant value of the covariance matrix.
     */
    float differential_normal(const float &det, const uint &dimension) const {
      if (q == 1.f) {
        return shannon_entropy -> differential_normal(det, dimension);
      } else {
        if (q == std::numeric_limits<float>::infinity()) {
          return -logf(-(classification_error -> differential_normal(det, dimension)-1.f));
        } else {
          return logf(-(induced_p -> differential_normal(det, dimension)-1.f))/(1.f-q);
        }
      }
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
      const auto *rhs_c = dynamic_cast<RenyiEntropy<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_q = q == rhs_c -> q;
        return eq_q;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const {
      ar.template register_type< RenyiEntropy<input_dtype> >();
      ar << boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
      ar << q;
      ar << shannon_entropy;
      ar << induced_p;
      ar << classification_error;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    template<class Archive>
    void load(Archive & ar, const unsigned int version) {
      ar.template register_type< RenyiEntropy<input_dtype> >();
      ar >> boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
      ar >> q;
      ar >> shannon_entropy;
      ar >> induced_p;
      ar >> classification_error;
    }
#endif
    /** Returns the alpha value set in the constructor. */
    float const get_alpha() const { return q; }

   private:
    /** \brief DON'T USE. Non-initializing constructor for serialization purposes. */
    RenyiEntropy() {};

    float q;
    std::unique_ptr<ShannonEntropy<input_dtype>> shannon_entropy;
    std::unique_ptr<InducedEntropy<input_dtype>> induced_p;
    std::unique_ptr<ClassificationError<input_dtype>> classification_error;
    DISALLOW_COPY_AND_ASSIGN(RenyiEntropy<input_dtype>);
  };
}  // namespace fertilized
#endif  // FERTILIZED_IMPURITIES_RENYIENTROPY_H_