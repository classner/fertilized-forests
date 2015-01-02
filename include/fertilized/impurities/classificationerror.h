/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_IMPURITIES_CLASSIFICATIONERROR_H_
#define FERTILIZED_IMPURITIES_CLASSIFICATIONERROR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <vector>
#include <limits>

#include "../global.h"
#include "../types.h"
#include "../util/exponentials.h"
#include "./ientropyfunction.h"

namespace fertilized {
  /**
   * \brief Computes the classification error as 1-\max(p_i).
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
  class ClassificationError : public IEntropyFunction<input_dtype> {
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
    ClassificationError() { }
    ~ClassificationError() {}

    /**
     * The method is supposed to be fast and hence no checking for the validity
     * of fsum is done in release mode!
     *
     * \param class_member_numbers Class distribution histogram.
     * \return The calculated entropy value.
     */
    float operator()(const std::vector<input_dtype> &class_members_numbers,
                     const float &fsum) const {
      // Deal with the special case quickly.
      if (fsum == 0.f)
        return 0.f;

      return 1.f - static_cast<float>(*std::max_element(
                                        class_members_numbers.begin(),
                                         class_members_numbers.end())) / fsum;
    };

    /**
     * \brief Classification error equivalent for the normal distribution.
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
      return 1.f - 1.f / sqrtf(fpowi(TWO_PI, dimensions) * det);
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
      const auto *rhs_c = dynamic_cast<ClassificationError<input_dtype> const *>(&rhs);
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
    DISALLOW_COPY_AND_ASSIGN(ClassificationError<input_dtype>);
  };
}  // namespace fertilized
#endif  // FERTILIZED_IMPURITIES_CLASSIFICATIONERROR_H_