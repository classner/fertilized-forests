/* Author: Moritz Einfalt, Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_REGRESSION_LINEARREGRESSIONCALCULATOR_H_
#define FERTILIZED_REGRESSION_LINEARREGRESSIONCALCULATOR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/LU>

#include "../global.h"
#include "../types.h"
#include "./iregressioncalculator.h"

namespace fertilized {
  /**
   * \brief Calculator for linear regression.
   *
   * This regression calculator uses a linear combination of the input dimensions
   * to predict the output value. Therefore it does not provide a constant prediction
   * or a constant prediction covariance matrix.
   * If there are multiple output values to be predicted, each output is produced
   * using its own linear model.
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float
   * - double
   * .
   *
   * -----
   */
  template<typename input_dtype>
  class LinearRegressionCalculator
    : public IRegressionCalculator<input_dtype> {

   public:
    typedef IRegressionCalculator<input_dtype> IRegressionCalculator_t;
    // gcc 4.8.1 doesn't like this typedef via a using declaration.
    typedef Eigen::Matrix<input_dtype,
                           Eigen::Dynamic,
                           Eigen::Dynamic,
                           Eigen::RowMajor,
                           Eigen::Dynamic,
                           Eigen::Dynamic> Matrix_regression_t;
    //using typename IRegressionCalculator_t::Matrix_regression_t;
    using typename IRegressionCalculator_t::Vector_regression_t;
    using typename IRegressionCalculator_t::interval_t;

   /**
    * \brief Constructor for a LinearRegressionCalculator
    *
    * Costructs a LinearRegressionCalculator.
    * If numberical stability is not forced, the linear models
    * in low dimensional cases are computed using a closed form.
    * This is faster but less accurate.
    * Otherwise, always matrix decomposition is used which provides
    * more accurate and stable solutions.
    * In order to prevent numerical issues, a threshold can be specified
    * to denote the smallest number that is distinct to zero.
    * Using the default value -1, this threshold is determined automatically
    * based on the data samples.
    *
    * \param force_numerical_stability Denotes, numerical stability is forced or not.
    * \param numerical_zero_threshold The threshold for the smallest number distinguished from zero.
    * \returns A new LinearRegressionCalculator.
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
    * \param force_numerical_stability bool
    *   Whether to enforce numerical stability or allow instable solutions. Default: true.
    * \param numerical_zero_threshold input_dtype >=0||-1
    *   Everything below this threshold is treated as zero. If set to -1.f, 
    *   use the value proposed by Eigen. Default: -1.f
    */
   LinearRegressionCalculator(const bool &force_numerical_stability = true,
                              const input_dtype &numerical_zero_threshold = static_cast<input_dtype>(-1.f))
      : force_numerical_stability(force_numerical_stability),
        numerical_zero_threshold(numerical_zero_threshold),
        solution_available(false),
        interval_freezed(false),
        sample_mat(std::shared_ptr<Matrix_regression_t>()),
        annotation_mat(std::shared_ptr<Matrix_regression_t>()),
        input_dim(0),
        annot_dim(0),
        n_samples(0),
        current_interval(std::make_pair(-1,-1)),
        solution(Matrix_regression_t()),
        param_covar_mat_template(Matrix_regression_t()),
        error_vars(std::vector<input_dtype>()) {
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");
      if (numerical_zero_threshold != static_cast<input_dtype>(-1.) &&
          numerical_zero_threshold < static_cast<input_dtype>(0.)) {
        throw Fertilized_Exception("Invalid numerical zero threhsold.");
      }
    };
    /**
   * \brief Empty constructor for a LinearRegressionCalculator
   *
   */
   LinearRegressionCalculator(const LinearRegressionCalculator<input_dtype> * other)
      : force_numerical_stability(other->force_numerical_stability),
        numerical_zero_threshold(other->numerical_zero_threshold),
        sample_mat(other->sample_mat),
        annotation_mat(other->annotation_mat),
        input_dim(other->input_dim),
        annot_dim(other->annot_dim),
        n_samples(other->n_samples),
        current_interval(other->current_interval),
        solution(other->solution),
        param_covar_mat_template(other->param_covar_mat_template),
        error_vars(other->error_vars),
        solution_available(other->solution_available),
        interval_freezed(other->interval_freezed) {
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");
    };

   /** Gets a deep copy. */
   IRegressionCalculator<input_dtype> * get_descendant_copy() const {
     return static_cast<IRegressionCalculator<input_dtype> *>(new LinearRegressionCalculator<input_dtype>(this));
   };

   /** Initializes for performing regression. */
   void initialize(std::shared_ptr<Matrix_regression_t> & sample_mat,
                   std::shared_ptr<Matrix_regression_t> & annotation_mat,
                   const interval_t & index_interval) {
     this->sample_mat = sample_mat;
     this->annotation_mat = annotation_mat;
     this->input_dim = sample_mat->cols();
     this->annot_dim = annotation_mat->cols();
     this->n_samples = sample_mat->rows();
     interval_freezed = false;
     FASSERT(this->sample_mat->rows() == this->annotation_mat->rows());
     FASSERT(check_interval_valid(index_interval));
     error_vars = std::vector<input_dtype> (annot_dim, static_cast<input_dtype>(0.f));
     current_interval = std::pair<int, int>(-1,-1);
     change_index_interval(index_interval);
   };

   /** Returns the input dimension used. */
   size_t get_input_dimension() const {
     return input_dim;
   };

   /** Returns the annotation dimensiton used. */
   size_t get_annotation_dimension() const {
     return annot_dim;
   };

   /** Returns the value as specified in the constructor. */
   bool forces_numerical_stability() {
     return force_numerical_stability;
   };

   /** Returns the threshold as specified in the constructor. */
   input_dtype get_numerical_zero_threshold() {
     return numerical_zero_threshold;
   };

   /** Changes the interval if allowed. Returns success. */
    bool change_index_interval(const interval_t & interval) {
      FASSERT(check_interval_valid(interval));
      if (interval_freezed)
        return false;
      if (interval != current_interval) {
        current_interval = interval;
        if ((current_interval.second - current_interval.first) < (input_dim + 1)) {
          this->solution_available = false;
          return false;
        } else {
          solution_available = calc_solution();
          return true;
        }
      } else {
          return (! ((current_interval.second - current_interval.first) < (input_dim + 1)));
      }
    };

    /** Whether the regression is well-defined in the specified range. */
    bool has_solution() const {
      return solution_available;
    };

    /** Returns true. */
    bool needs_input_data() const {return true;};

    /** Returns false. */
    bool has_constant_prediction_covariance() const {return false;};

    /** Predicts a vector, if a solution is available. Otherwise does nothing. */
    void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output) const {
      if (solution_available)
        prediction_output.noalias() = (input.transpose() * solution).transpose();
    };

    /** Predicts a vector and estimates the covariane matrix of the output, if a solution is available. Otherwise does nothing. */
    void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output, Matrix_regression_t &covar_output) const {
      if (solution_available) {
        predict(input, prediction_output);
        covar_output.fill(static_cast<input_dtype>(0.f));
        for (int i=0; i<annot_dim; i++) {
          covar_output(i,i) = (input.transpose() * param_covar_mat_template * input)(0,0) * error_vars[i];
        }
      }
    };

    /** Throws an exception! */
    void get_constant_prediction_covariance(Matrix_regression_t &covar_output) const {
      // this call is not allowed in the LinearRegressionCalculator, since there is not constant pred. covar.
      throw Fertilized_Exception("The linear regression calculator does not support a constant covariance matrix.");
    }

    /** Freezes the regression interval. */
    void freeze_interval() {
      interval_freezed = true;
      // release the data samples because they are no longer needed
      sample_mat = std::shared_ptr<Matrix_regression_t>();
      annotation_mat = std::shared_ptr<Matrix_regression_t>();
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
    bool operator==(const IRegressionCalculator<input_dtype> &rhs) const {
      const auto *rhs_c = dynamic_cast<LinearRegressionCalculator<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_frc = force_numerical_stability == rhs_c -> force_numerical_stability;
        bool eq_thresh = numerical_zero_threshold == rhs_c -> numerical_zero_threshold;
        bool eq_inp = input_dim == rhs_c -> input_dim;
        bool eq_adm = annot_dim == rhs_c -> annot_dim;
        bool eq_nsamples = n_samples == rhs_c -> n_samples;
        bool eq_int = current_interval == rhs_c -> current_interval;
        bool eq_sol = solution == rhs_c -> solution;
        bool eq_cmt = param_covar_mat_template == rhs_c -> param_covar_mat_template;
        bool eq_ev = error_vars == rhs_c -> error_vars;
        bool eq_av = solution_available == rhs_c -> solution_available;
        bool eq_frz = interval_freezed == rhs_c -> interval_freezed;
        return eq_frc && eq_thresh && eq_inp && eq_adm && eq_nsamples &&
               eq_int && eq_sol && eq_cmt && eq_ev && eq_av && eq_frz;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<
        IRegressionCalculator<input_dtype>>(*this);
      ar & force_numerical_stability;
      ar & numerical_zero_threshold;
      ar & input_dim;
      ar & annot_dim;
      ar & n_samples;
      ar & current_interval;
      ar & solution;
      ar & param_covar_mat_template;
      ar & error_vars;
      ar & solution_available;
      ar & interval_freezed;
    }
#endif


   private:

     bool check_interval_valid(const interval_t & interval) {
       return (interval.second >= interval.first &&
               interval.first >= 0 &&
               interval.second <= n_samples);
     };

     bool calc_solution() {
       // Notation:
       // sample_input_mat: X
       // sample_annotation_mat : Y
       // w_mat: W = X' * X
       // w_inverse_mat: W^(-1)

       auto current_sample_mat = sample_mat->block(current_interval.first, 0, current_interval.second-current_interval.first, input_dim);
       auto current_annot_mat = annotation_mat->block(current_interval.first, 0, current_interval.second-current_interval.first, annot_dim);
       Matrix_regression_t w_inverse_mat (input_dim,input_dim);
       // Regression models with less than five parameters can be computed fast without matrix decomposition
       if ((!force_numerical_stability) && input_dim < 5 ) {
         input_dtype numeric_threshold = (numerical_zero_threshold <= 0.f) ? (Eigen::NumTraits<input_dtype>::dummy_precision()) : (numerical_zero_threshold);
         input_dtype determinant;
         bool invertible = false;
         // For small matrices, the inverse calculation in Eigen is very fast for fixed-size matrices only.
         if (input_dim == 1) {
           Eigen::Matrix<input_dtype,1,1,Eigen::RowMajor> w_mat;
           w_mat.noalias() = current_sample_mat.transpose() * current_sample_mat;
           w_mat.computeInverseAndDetWithCheck(w_inverse_mat, determinant, invertible, numeric_threshold);
         } else if (input_dim == 2) {
           Eigen::Matrix<input_dtype,2,2,Eigen::RowMajor> w_mat;
           w_mat.noalias() = current_sample_mat.transpose() * current_sample_mat;

           w_mat.computeInverseAndDetWithCheck(w_inverse_mat, determinant, invertible, static_cast<input_dtype>(numeric_threshold));
         } else if (input_dim == 3) {
           Eigen::Matrix<input_dtype,3,3,Eigen::RowMajor> w_mat;
           w_mat.noalias() = current_sample_mat.transpose() * current_sample_mat;

           w_mat.computeInverseAndDetWithCheck(w_inverse_mat, determinant, invertible, static_cast<input_dtype>(numeric_threshold));
         } else if (input_dim == 4) {
           Eigen::Matrix<input_dtype,4,4,Eigen::RowMajor> w_mat;
           w_mat.noalias() = current_sample_mat.transpose() * current_sample_mat;
           w_mat.computeInverseAndDetWithCheck(w_inverse_mat, determinant, invertible, static_cast<input_dtype>(numeric_threshold));
         }


         if (! invertible) {
           return false;
         }

         // Calculate the least squares solution = W^(-1) * X' * Y
         solution.noalias() = w_inverse_mat * (current_sample_mat.transpose() * current_annot_mat);


       } else {
         // This is the case, where the regression model is calculated for more than four input dimensions
         // or a numerical stable solution is required
         // In order to check if a unique solution to the regression problem exists, a rank-revealing QR-decomposition is used.
         // Calculate the decomposition X*P = Q*R, where
         // P is a permutation matrix and
         // R is upper triangular.
         Eigen::ColPivHouseholderQR<Matrix_regression_t> decomposer;
         if (numerical_zero_threshold <= 0) {
           decomposer.setThreshold(Eigen::Default);
         } else {
           decomposer.setThreshold(numerical_zero_threshold);
         }
         decomposer.compute(current_sample_mat);
         size_t rank = decomposer.rank();
         if (rank < input_dim) {
           return false;
         }

         // Get the model params using the built-in solver
         solution = decomposer.solve(current_annot_mat);
         // In order to compute W^(-1) = (X' * X)^(-1), the equal expression P * R^(-1) * R^(-1)' * P' is calculated.
         // Since R is upper triangular, R^(-1) is too and can directly be calculated.
         auto r_mat = decomposer.matrixR();
         Matrix_regression_t r_inverse_mat = Matrix_regression_t::Zero(input_dim, input_dim);
         for (int j = static_cast<int>(input_dim - 1); j >= 0 ; j--) {
           r_inverse_mat(j,j) = static_cast<input_dtype>(1.f)/r_mat(j,j);
           for (int i = j-1; i >= 0; i--) {
             for (int k = i+1; k <= j; k++) {
               r_inverse_mat(i,j) -= r_mat(i,k) * r_inverse_mat(k,j) / r_mat(i,i);
             }
           }
         }

         w_inverse_mat.noalias() = decomposer.colsPermutation() * (r_inverse_mat * r_inverse_mat.transpose()) * decomposer.colsPermutation().transpose();
       }

        param_covar_mat_template = w_inverse_mat.eval();

        // Now, estimate the error variance (sigma^2) through the sum of squared residuals for each annotation dimension
        Matrix_regression_t prediction = current_sample_mat * solution;
        for (int i = 0; i < (current_interval.second - current_interval.first); i++) {
          for (int j = 0; j < annot_dim; j++) {
            if (i == 0)
              error_vars[j] = static_cast<input_dtype>(0.f);
            input_dtype residual = prediction(i,j) - current_annot_mat(i,j);
            error_vars[j] += (residual * residual) / static_cast<input_dtype>(n_samples - input_dim);
          }
        }
        //// The model-parameter covariance matrices are given by W^(-1) * (sigma^2)
        //param_covar_mats.resize(annotation_dim);
        //for (int i = 0; i < annotation_dim; i++) {
        //  param_covar_matrices[i] = std::make_shared<Matrix_regression_t>(input_dim,input_dim);
        //  (*(param_covar_matrices[i])).noalias() = w_inverse_mat * estimated_variances[i];
        //}

        return true;
     };

     bool force_numerical_stability;
     input_dtype numerical_zero_threshold;
     std::shared_ptr<Matrix_regression_t>sample_mat;
     std::shared_ptr<Matrix_regression_t>annotation_mat;
     size_t input_dim;
     size_t annot_dim;
     size_t n_samples;
     interval_t current_interval;
     Matrix_regression_t solution;
     Matrix_regression_t param_covar_mat_template;
     std::vector<input_dtype> error_vars;
     bool solution_available;
     bool interval_freezed;

  };
}; // namespace fertilized
#endif // FERTILIZED_REGRESSION_LINEARREGRESSIONCALCULATOR_H_