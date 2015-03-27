/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_IMPURITIES_INDUCEDENTROPY_H_
#define FERTILIZED_IMPURITIES_INDUCEDENTROPY_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <limits>

#include "../global.h"
#include "../types.h"
#include "../util/checks.h"
#include "../util/exponentials.h"
#include "./ientropyfunction.h"
// Inclusion of ./tsallisentropy.h at the end of this file!

namespace fertilized {
  // Forward declaration.
  template <typename input_dtype>
  class TsallisEntropy;

  /**
   * \brief Computes the induced p entropy.
   *
   * Works correctly up to a total sum of elements of
   * numeric_limits<input_dtype>::max().
   *
   * This is the induced p-metric of the vector of \f$n\f$ class probabilities
   * and the point of maximum unorder (the vector with all entries
   * \f$\frac{1}{n}\f$) in the n-dimensional space without applying the root.
   * It is equal to the Gini-measure for \f$p=2\f$.
   *
   * The definition for \f$c\f$ classes:
   * \f[\sum_{i=1}^{c} \left\Vert p_i - 0.5\right\Vert ^p\f].
   *
   * The differential entropy for a normal distribution with covariance
   * matrix \f$\Sigma\f$ in \f$n\f$ dimensions is defined as:
   * \f[\frac{1}{\sqrt{p^n}}\cdot\left(\sqrt{2\pi}^n\cdot\sqrt{\left|\Sigma\right|}\right)^{-(p-1)}\f]
   *
   * In the differential normal case, the most useful values for \f$p\f$ are
   * very close to 1 (e.g. 1.00001)! \f$p=2\f$ is already equivalent to the
   * infinite norm!
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
  class InducedEntropy : public IEntropyFunction<input_dtype> {
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
   * \param p float>0.f
   *   The entropy parameter value.
   */
    InducedEntropy(const float &p)
      : p(p) {
      if (p <= 0.f) {
        throw Fertilized_Exception("p must be > 0.f.");
      }
      tsallis_entropy = std::unique_ptr<TsallisEntropy<input_dtype>>(
                            new TsallisEntropy<input_dtype>());
      tsallis_entropy -> q = p;
    }

    ~InducedEntropy() {};

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
     * \param class_member_numbers Vector  The class member counts (class histogram).
     * \param fsum float The total of the class_member_numbers Vector.
     * \return The calculated entropy value.
     */
    float operator()(const std::vector<input_dtype> &class_members_numbers,
                     const float &fsum) const {
      // In debug mode, run checks.
      FASSERT(static_cast<float>(
        std::accumulate(class_members_numbers.begin(),
                        class_members_numbers.end(),
                        static_cast<float>(0))) == fsum);
      FASSERT(safe_pos_sum_lessoe_than(class_members_numbers));

      // Deal with the special case quickly.
      if (fsum == 0.f)
        return 0.f;

      // T_2 has apparently "better" (more suited) numerical instabilities
      // leading to better scores. Both measures are theoretically equivalent
      // for q=2, so use this fact!
      if (p == 2.f)
        return tsallis_entropy -> operator()(class_members_numbers, fsum);

      // Cast only once and save time.
      float n_classes_f = static_cast<float>(class_members_numbers.size());
      float max_unorder_val = 1.f / n_classes_f;
      float entropy_sum;
      if (ceilf(p) == p || floorf(p) == p) {
        // p is a whole number. Use a faster implementation.
        const uint whole_p = static_cast<uint>(p);
        // Offset.
        entropy_sum = fpowi(1.f - max_unorder_val, whole_p) +
                      (n_classes_f - 1.f) * fpowi(max_unorder_val, whole_p);
        float quot;
        // Calculate.
        for (const auto &member_number : class_members_numbers) {
          quot = static_cast<float>(member_number) / fsum;
          entropy_sum -= fpowi(fabs(quot - max_unorder_val), whole_p);
        }
      } else {
        // p is not a whole number.
        // Offset.
        entropy_sum = powf(1.f - max_unorder_val, p) +
                      (n_classes_f - 1.f) * powf(max_unorder_val, p);
        float quot;
        // Calculate.
        for (const auto &member_number : class_members_numbers) {
          quot = static_cast<float>(member_number) / fsum;
          entropy_sum -= powf(fabs(quot - max_unorder_val), p);
        }
      }
      return entropy_sum;
    };

    /**
     * \brief Differential induced p entropy of the normal distribution.
     *
     * Calculates the differential entropy of a normal distribution with the
     * determinant value of the covariance matrix.
     */
    float differential_normal(const float &det, const uint &dimension) const {
      if (det == 0.f) {
        // Strictly spocken, covar_matrix must be positive definite. In this
        // case, it would be positive-semidefinite (maybe due to numerical
        // issues). Try to save it...
        return - std::numeric_limits<float>::infinity();
      }
      if (det < 0.f) {
        // This is complete bollocks.
        throw Fertilized_Exception("Covariance matrix with negative "
          "determinant occured.");
      }
      return 1.f-powf(p, -0.5f*static_cast<float>(dimension)) *
                 powf(powf(TWO_PI, static_cast<float>(dimension)) * det,
                      -0.5f*(p-1.f));
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
      const auto *rhs_c = dynamic_cast<InducedEntropy<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_p = p == rhs_c -> p;
        return eq_p;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const {
        ar.template register_type< InducedEntropy<input_dtype> >();
        ar << boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
        ar << p;
        ar << tsallis_entropy;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    template<class Archive>
    void load(Archive & ar, const unsigned int version) {
      ar.template register_type< InducedEntropy<input_dtype> >();
      ar >> boost::serialization::base_object<IEntropyFunction<input_dtype>>(*this);
      ar >> p;
      ar >> tsallis_entropy;
    }
#endif

    /** Returns the parameter value as set in the constructor. */
    float const get_p() const { return p; }

   private:
    InducedEntropy() {};

    std::unique_ptr<TsallisEntropy<input_dtype>> tsallis_entropy;
    float p;
    DISALLOW_COPY_AND_ASSIGN(InducedEntropy<input_dtype>);
  };
}  // namespace fertilized

// This include must be made after the definition of the InducedEntropy
// to break a dependency circle.
#include "./tsallisentropy.h"
#endif  // FERTILIZED_IMPURITIES_INDUCEDENTROPY_H_