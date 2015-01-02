/* Author: Moritz Einfalt, Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_REGRESSION_IREGRESSIONCALCULATOR_H_
#define FERTILIZED_REGRESSION_IREGRESSIONCALCULATOR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/LU>

#include "../global.h"
#include "../types.h"

namespace fertilized {
  /**
   * \brief The interface for a regression calculator.
   *
   * Given a set of annotated samples, it calculates a model that explains the dependency
   * between the input variables and the response variables of the sampels.
   * This model is chosen as good as its parameters allow it to fit the data.
   * With this model, a prediction for the response variables on a single sample
   * can be calculated. 
   * Additionally, the probability distribution for a specific output value 
   * given a single sample can be computed.
   * Often, samples have to be incrementally added or removed from the sample set.
   * This can be done by initializing a IRegressionCalculator with
   * the complete set of samples and afterwards specify an interval as the index-range
   * denoting which sample are actually used for the regression model.
   * Depending on the type of regression calculator, this can lead to a major
   * performance increase.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * .
   * Instantiations:
   * - float
   * - double
   * .
   * 
   * -----
   */
  template <typename input_dtype>
  class IRegressionCalculator {
   public:
    typedef Eigen::Matrix<input_dtype, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor, Eigen::Dynamic, Eigen::Dynamic> Matrix_regression_t;
    typedef Eigen::Matrix<input_dtype, Eigen::Dynamic, 1, Eigen::ColMajor, Eigen::Dynamic, 1> Vector_regression_t;
    typedef std::pair<int, int> interval_t;

    virtual ~IRegressionCalculator(){};

    /**
    * \brief Workaround for a copy constructor respecting inheritance
    *
    * Constructors can not be declared virtual in C++.
    * Using the copy constructor on a base class object, only the constructor of the base class is called.
    * Possible inheritance is ignored. This method provieds a workaround. 
    * Called on a base class object, it provieds a copy of the object as its true sub-class.
    * 
    * \returns A copy of the object respecting its true sub-class.
    */
    virtual IRegressionCalculator<input_dtype> * get_descendant_copy() const VIRTUAL_PTR;
    /**
    * \brief Initializes the regression calculator.
    *
    * In order to initialize a IRegressionCalulator, the complete set of samples and their annotations
    * has to be specified. Furthermore, a initial interval \f$\left[a,b\right)$\f has to be provided. The samples with indices
    * in this interval are then used to calcualate a initial regression model.
    *
    * \param sample_mat The complete set of samples. It needs to be valid only if \ref needs_input_data is true.
    * \param annotation_mat The complete set of annotations.
    * \param index_interval The initial index interval \f$\left[a,b\right)$\f on which the regression model is calculated.
    */
    virtual void initialize(std::shared_ptr<Matrix_regression_t> & sample_mat,
                            std::shared_ptr<Matrix_regression_t> & annotation_mat,
                            const interval_t & index_interval) 
                            VIRTUAL(void);

    /**
    * \brief Returns the dimensionality of the samples used in the regression calculator.
    *
    * \return The number of dimensions the samples consist of.
    */
    virtual size_t get_input_dimension() const VIRTUAL(size_t);

    /**
    * \brief Returns the dimensionality of the annotations used in the regression calculator.
    *
    * \return The number of dimensions the annotations consist of.
    */
    virtual size_t get_annotation_dimension() const VIRTUAL(size_t);

    /**
    * \brief Changes the subset of samples used in the regression model.
    *
    * The provided interval specifies a new index range denoting the subset of samples used in the regression model.
    * The regression model is updated or recomputed afterwards. The maximum interval is \f$\left[0,n_samples\right)$\f
    * 
    * \return Whether the given interval is valid or not.
    */
    virtual bool change_index_interval(const interval_t & interval) VIRTUAL(bool);

    /**
    * \brief Checks, if a regression model is available.
    *
    * Returns, whether a regression model is available based on the samples specified by the current interval.
    * 
    * \return Whether a regression model is available or not.
    */
    virtual bool has_solution() const VIRTUAL(bool);

    /**
    * \brief Checks, if the regression calculator needs input data.
    *
    * Returns, whether the regression calculator needs data samples or not.
    * This does only relate to the input samples, NOT the annotations.
    * 
    * \return Whether input data is needed or not.
    */
    virtual bool needs_input_data() const VIRTUAL(bool);

    /**
    * \brief Checks, if the regression calculator provides a constant prediciton covariance.
    *
    * Returns, whether the regression calculator supports a constant prediction covariance 
    * or each prediction covariance depends on the specific input. Usually, this coincides wiht
    * \ref needs_input_data.
    * 
    * \return Whether a constant prediction covariance can be provided.
    */
    virtual bool has_constant_prediction_covariance() const VIRTUAL(bool);

    /**
    * \brief Predicts the output for a given sample.
    *
    * The regression calculator predicts the output based on the given input.
    * The input is only used, if \ref needs_input_data is true.
    * 
    * \param input The input sample.
    * \param prediction_output The output for the prediction.
    */
    virtual void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output) const VIRTUAL(void);

    /**
    * \brief Predicts the output for a given sample.
    *
    * The regression calculator predicts the output based on the given input.
    * The input is only used, if \ref needs_input_data is true.
    * Additionally, the covariance matrix of the predicted output 
    * specifying the uncertainty of the prediction is calculated.
    * 
    * \param input The input sample.
    * \param prediction_output The output for the prediction.
    * \param covar_output The output for the covariance matrix.
    */
    virtual void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output, Matrix_regression_t &covar_output) const VIRTUAL(void);

    /**
    * \brief Get the constant prediction covariance
    *
    * Returns the constant covariance matrix of the predictions. 
    * This is not supported by all regression calculators. See \ref has_constant_prediction_covariance
    * \param covar_output The output for the covariance matrix.
    */
    virtual void get_constant_prediction_covariance(Matrix_regression_t &covar_output) const VIRTUAL(void);

    /**
    * \brief Freezes the currently set index interval.
    *
    * The currently set index interval is locked.
    * It can not be changed afterwards.
    * The solution based on this interval is preserved.
    * The main effect of this method is to release all unnecessary data.
    * Call this method before serializing!
    */
    virtual void freeze_interval() VIRTUAL(void);

    /**
     * Deep comparison operator.
     */
    virtual bool operator==(const IRegressionCalculator<input_dtype> &rhs) 
      const VIRTUAL(bool);

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {}
#endif

   protected:
    IRegressionCalculator(){};

   private:
  };
}; // namespace fertilized
#endif // FERTILIZED_REGRESSION_IREGRESSIONCALCULATOR_H_