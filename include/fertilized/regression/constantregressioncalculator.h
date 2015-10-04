/* Author: Moritz Einfalt, Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_REGRESSION_CONSTANTREGRESSIONCALCULATOR_H_
#define FERTILIZED_REGRESSION_CONSTANTREGRESSIONCALCULATOR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include "../global.h"
#include "../types.h"
#include "./iregressioncalculator.h"

namespace fertilized {
  /**
   * \brief Calculator for constant regression.
   *
   * This regression calculator uses a constant value to predict the output value.
   * Therefore, it provides a constant prediction and a constant prediction covariance matrix.
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
  template <typename input_dtype>
  class ConstantRegressionCalculator
    :public IRegressionCalculator<input_dtype> {
   public:
    typedef IRegressionCalculator<input_dtype> IRegressionCalculator_t;
    using typename IRegressionCalculator_t::Matrix_regression_t;
    using typename IRegressionCalculator_t::Vector_regression_t;
    using typename IRegressionCalculator_t::interval_t;

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
    ConstantRegressionCalculator()
      : solution_available(false),
        interval_freezed(false),
        annotation_mat(std::shared_ptr<Matrix_regression_t>()),
        annot_dim(0),
        n_samples(0),
        current_interval(std::make_pair(-1,-1)),
        solution(Vector_regression_t()),
        error_vars(Vector_regression_t()) {
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");
    };

    /**
    * \brief Copy constructor for a ConstantRegressionCalculator
    *
    */
    ConstantRegressionCalculator(const ConstantRegressionCalculator<input_dtype> * other)
      : annotation_mat(other->annotation_mat),
        annot_dim(other->annot_dim),
        n_samples(other->n_samples),
        current_interval(other->current_interval),
        solution(other->solution),
        error_vars(other->error_vars),
        solution_available(other->solution_available),
        interval_freezed(other->interval_freezed){
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");
    }

    /** Gets a deep copy of this regression calculator. */
    IRegressionCalculator<input_dtype> * get_descendant_copy() const {
      return static_cast<IRegressionCalculator<input_dtype> *>(new ConstantRegressionCalculator<input_dtype>(this));
    };

    /** Initializes for processing. */
    void initialize(std::shared_ptr<Matrix_regression_t> & sample_mat,
                            std::shared_ptr<Matrix_regression_t> & annotation_mat,
                            const interval_t & index_interval) {
      this->annotation_mat = annotation_mat;
      this->annot_dim = annotation_mat->cols();
      this->n_samples = annotation_mat->rows();
      interval_freezed = false;
      FASSERT(check_interval_valid(index_interval));
      solution = Vector_regression_t(annot_dim);
      error_vars = Vector_regression_t(annot_dim);
      current_interval = std::pair<int, int>(-1,-1);
      change_index_interval(index_interval);
    };

    /** Always returns 0. */
    size_t get_input_dimension() const {return 0;};

    /** Returns the annotation dimension specified in the constructor. */
    size_t get_annotation_dimension() const {return annot_dim;};

    /** Adjusts the data interval and updates whether a solution is available. */
    bool change_index_interval(const interval_t & interval) {
      FASSERT(check_interval_valid(interval));
      if (interval_freezed)
        return false;
      if (interval != current_interval) {
        if ((interval.second - interval.first) < (1)) {
          this->solution_available = false;
          current_interval = interval;
          return false;
        } else {
          while(current_interval != interval) {
            if (solution_available) {
              // right interval increase
              if (current_interval.first == interval.first && interval.second > current_interval.second) {
                solution_available = increment_right_interval_boundary();
              // left interval decrease
              } else if (current_interval.second == interval.second && current_interval.first < interval.first) {
                solution_available = increment_left_interval_boundary();
              // recalculation
              } else {
                current_interval = interval;
                solution_available = calc_solution();
              }
            } else {
              current_interval = interval;
              solution_available = calc_solution();
            }
          }
          return true;
        }
      } else {
          return ((interval.second - interval.first) > (0));
      }
    };

    /** Whether the regression is well-defined for the data. */
    bool has_solution() const {return solution_available;};

    /** Returns false. */
    bool needs_input_data() const {return false;};

    /** Returns true. */
    bool has_constant_prediction_covariance() const {return true;};

    /** Predicts a vector if a solution is available.
     *
     * This can be checked using \ref has_solution. Otherwise does nothing.
     */
    void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output) const {
      if (solution_available)
        prediction_output = solution;
    };

    /**
     * Predicts a vector and estimates the covariance matrix for the output, if a solution is available.
     */
    void predict(const Vector_regression_t &input, Vector_regression_t & prediction_output, Matrix_regression_t &covar_output) const {
      if (solution_available) {
        predict(input, prediction_output);
        covar_output.fill(static_cast<input_dtype>(0.f));
        for (int i=0; i<annot_dim; i++) {
          covar_output(i,i) = error_vars(i); // / static_cast<input_dtype>(current_interval.second - current_interval.first);
        }
      }
    };

    /** Gets the matrix used for output covariance estimation. */
    void get_constant_prediction_covariance(Matrix_regression_t &covar_output) const {
      FASSERT(has_constant_prediction_covariance());
      if (solution_available) {
        covar_output.fill(static_cast<input_dtype>(0.f));
        for (int i=0; i<annot_dim; i++) {
          covar_output(i,i) = error_vars(i); // / static_cast<input_dtype>(current_interval.second - current_interval.first);
        }
      }
    };

    /** Does not allow an interval change anymore. */
    void freeze_interval(){interval_freezed = true;};

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
      const auto *rhs_c = dynamic_cast<ConstantRegressionCalculator<input_dtype> const *>(&rhs);
      if (rhs_c == nullptr) {
        return false;
      } else {
        bool eq_adim = annot_dim == rhs_c -> annot_dim;
        bool eq_nsamples = n_samples == rhs_c -> n_samples;
        bool eq_int = current_interval == rhs_c -> current_interval;
        bool eq_sol = solution == rhs_c -> solution;
        bool eq_ev = error_vars == rhs_c -> error_vars;
        bool eq_av = solution_available == rhs_c -> solution_available;
        bool eq_frz = interval_freezed == rhs_c -> interval_freezed;
        return eq_adim && eq_nsamples && eq_int && eq_sol && eq_ev &&
               eq_av && eq_frz;
      }
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<
        IRegressionCalculator<input_dtype>>(*this);
      ar & annot_dim;
      ar & n_samples;
      ar & current_interval;
      ar & solution;
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

     bool calc_solution () {
       int current_n_sample = current_interval.second - current_interval.first;
       if (current_n_sample < 1)
         return false;
       // calculate the mean annotation
       for (int i=current_interval.first; i<current_interval.second; i++) {
         for (int j=0; j<annot_dim; j++) {
           if (i==current_interval.first)
             solution(j) = static_cast<input_dtype>(0.f);
           solution(j) = solution(j) + ((*annotation_mat)(i,j) / static_cast<input_dtype>(current_n_sample));
         }
       }
       // calculate the error variances
       if (current_n_sample == 1) {
         error_vars.fill(static_cast<input_dtype>(0.f));
       } else {
         for (int i=current_interval.first; i<current_interval.second; i++) {
           for (int j=0; j<annot_dim; j++) {
             if (i==current_interval.first)
               error_vars(j) = static_cast<input_dtype>(0.f);
             error_vars(j) = error_vars(j) + ((*annotation_mat)(i,j) - solution(j)) * ((*annotation_mat)(i,j) - solution(j)) / static_cast<input_dtype>(current_n_sample - 1);
           }
         }
       }
       return true;
     };

     bool increment_right_interval_boundary () {
       int added_index = current_interval.second;
       int old_n_samples = current_interval.second - current_interval.first;
       int new_n_samples = old_n_samples + 1;
       current_interval.second ++;
       if (current_interval.second > n_samples ||
           new_n_samples < 1)
           return false;
       if (old_n_samples < 1)
         return calc_solution();
       // update the mean annotation and error variances
       for (int j=0; j<annot_dim; j++) {
         input_dtype mean_new = solution(j) + (((*annotation_mat)(added_index,j) - solution(j)) / (static_cast<input_dtype>(new_n_samples)));
         error_vars(j) *= ((static_cast<input_dtype>(old_n_samples - 1)) / (static_cast<input_dtype>(old_n_samples)));
         error_vars(j) += ((*annotation_mat)(added_index,j) - solution(j))*((*annotation_mat)(added_index,j) - mean_new)
                          / (static_cast<input_dtype>(old_n_samples));
         solution(j) = mean_new;
       }

       return true;
     };

     bool increment_left_interval_boundary () {
       int removed_index = current_interval.first;
       int old_n_samples = current_interval.second - current_interval.first;
       int new_n_samples = old_n_samples - 1;
       current_interval.first ++;
       if (current_interval.first >= n_samples ||
           new_n_samples < 1)
           return false;
       if (old_n_samples < 3)
         return calc_solution();
       // update the mean annotation and error variances
       for (int j=0; j<annot_dim; j++) {
         input_dtype mean_new  = solution(j) + ((solution(j) - (*annotation_mat)(removed_index,j)) / static_cast<input_dtype>(new_n_samples));
         error_vars(j) *= ((static_cast<input_dtype>(old_n_samples - 1)) / (static_cast<input_dtype>(new_n_samples - 1)));
         error_vars(j) -= ((*annotation_mat)(removed_index,j) - solution(j))*((*annotation_mat)(removed_index,j) - mean_new)
                          / (static_cast<input_dtype>(new_n_samples - 1));
         solution(j) = mean_new;
         // check for numerical error with var < 0
         error_vars(j) = std::max(error_vars(j), static_cast<input_dtype>(0));
       }

       return true;
     };

     std::shared_ptr<Matrix_regression_t>annotation_mat;
     size_t annot_dim;
     size_t n_samples;
     interval_t current_interval;
     Vector_regression_t solution;
     Vector_regression_t error_vars;
     bool solution_available;
     bool interval_freezed;

  };
}; // namespace fertilized
#endif // FERTILIZED_REGRESSION_CONSTANTREGRESSIONCALCULATOR_H_
