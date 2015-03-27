/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_IMPURITIES_IENTROPYFUNCTION_H_
#define FERTILIZED_IMPURITIES_IENTROPYFUNCTION_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

#include <vector>
#include <numeric>

#include <Eigen/Dense>

#include "../global.h"
#include "../types.h"

namespace fertilized {

  /**
   * \brief Interface for an entropy calculation functor.
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
  class IEntropyFunction {
   public:
    virtual ~IEntropyFunction() {}

    /**
     * \brief The interface function that must be implemented.
     *
     * Calculates the entropy from a given class distribution. For maximum
     * efficiency, the number of total samples may be provided as float.
     *
     * \param class_member_numbers Class distribution histogram.
     * \param fsum The total number of samples.
     * \return The calculated entropy value.
     */
    virtual float operator()(
      const std::vector<input_dtype> &class_members_numbers, const float &fsum)
      const VIRTUAL(float);

    /**
     * \brief Classical entropy calculation function.
     *
     * Is implemented already and provides a shortcut for for the standard
     * function by calculating the sum of the class distribution.
     *
     * \param class_member_numbers Class distribution histogram.
     * \return The calculated entropy value.
     */
    virtual float operator()(
      const std::vector<input_dtype> &class_members_numbers) const {
        return operator()(class_members_numbers,
          static_cast<float>(
            std::accumulate(class_members_numbers.begin(),
                            class_members_numbers.end(),
                            static_cast<input_dtype>(0))));
    };

    /**
     * \brief Differential entropy of the normal distribution.
     *
     * Calculates the differential entropy of a normal distribution with the
     * specified covariance matrix.
     */
    virtual float differential_normal(const Eigen::Matrix<float,
                                                          Eigen::Dynamic,
                                                          Eigen::Dynamic,
                                                          Eigen::RowMajor> &covar_matrix)
      const {
      FASSERT(covar_matrix.rows() == covar_matrix.cols());
      float det = covar_matrix.determinant();
      return differential_normal(det, static_cast<uint>(covar_matrix.rows()));
    };

    /**
     * \brief Differential entropy of the normal distribution.
     *
     * Calculates the differential entropy of a normal distribution with the
     * specified determinant and dimension of the covariance matrix.
     */
    virtual float differential_normal(const float &det, const uint &dim)
      const VIRTUAL(float);

    /**
     * Deep equality comparison.
     */
    virtual bool operator==(const IEntropyFunction<input_dtype> &rhs)
      const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint &file_version) {}
#endif

   protected:
    IEntropyFunction() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(IEntropyFunction);
  };
}  // namespace fertilized
#endif  // FERTILIZED_IMPURITIES_IENTROPYFUNCTION_H_
