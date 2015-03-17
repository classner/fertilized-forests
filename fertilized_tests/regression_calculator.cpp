/* Author: Moritz Einfalt, Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

//#include "boost\python.hpp"

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <fstream>
#include <iostream>

#include "fertilized/types.h"
#include "fertilized/regression/iregressioncalculator.h"
#include "fertilized/regression/linearregressioncalculator.h"
#include "fertilized/regression/constantregressioncalculator.h"
#include "fertilized/types.h"
#include "fertilized/threshold_optimizers/ithresholdoptimizer.h"
#include "fertilized/threshold_optimizers/regressionthresholdoptimizer.h"
#include "fertilized/features/ifeatureselectionprovider.h"
#include "fertilized/features/standardfeatureselectionprovider.h"
#include "fertilized/data_providers/unchangeddataprovider.h"
#include "fertilized/data_providers/unchangedfdataprovider.h"
#include "fertilized/impurities/ientropyfunction.h"
#include "fertilized/impurities/shannonentropy.h"
#include "fertilized/leafs/regressionleafmanager.h"
#include "fertilized/execution_strategies/localexecutionstrategy.h"
#include "fertilized/tree.h"
#include "fertilized/forest.h"
#include "fertilized/standard_trees.h"
#include "fertilized/standard_forests.h"
#include <fertilized/ndarray.h>

#include "./setup.h"
#include "./timeit.h"

using fertilized::IRegressionCalculator;
using fertilized::LinearRegressionCalculator;
using fertilized::ConstantRegressionCalculator;
using fertilized::RegressionThresholdOptimizer;
using fertilized::IGainCalculator;
using fertilized::IThresholdOptimizer;
using fertilized::EThresholdSelection;
using fertilized::IFeatureSelectionProvider;
using fertilized::StandardFeatureSelectionProvider;
using fertilized::IDataProvider;
using fertilized::UnchangedDataProvider;
using fertilized::IEntropyFunction;
using fertilized::ShannonEntropy;
using fertilized::RegressionLeafManager;
using fertilized::Tree;
using fertilized::Forest;
using fertilized::UnchangedFDataProvider;
using fertilized::LocalExecutionStrategy;
using ndarray::Array;
using ndarray::Vector;
using ndarray::makeVector;
using ndarray::external;

typedef std::tuple<std::pair<float, float>,
                       EThresholdSelection,
                       unsigned int, unsigned int, float>
                       optimization_tuple_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix_t;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector_t;


BOOST_AUTO_TEST_SUITE(Correctness_RegressionCalculator);

BOOST_AUTO_TEST_CASE(Correctness_1d_constant_regression) {
  // initialized it randomly since it is unused
  auto mat = std::make_shared<Matrix_t> (5,2);
  (*mat).setRandom();

  auto annotations = std::make_shared<Matrix_t>(5,1);
  (*annotations) << 2, 4, 5, 8, 10;
  int n_samples = 5;
  int lower_boundary = 0;
  int upper_boundary = n_samples;
  auto calculator_ptr = std::make_shared<ConstantRegressionCalculator<float>>();
  calculator_ptr->initialize(mat, annotations, std::make_pair(lower_boundary, 0));
  auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
                      serialize_deserialize(calculator_ptr);
#else
                      calculator_ptr;
#endif

  // increment the right interval boundary
  // compare the returned mean ndvariance with the manually computed one
  Matrix_t pred_var(1,1);
  Vector_t pred_mean(1);
  // input is unused due to the constant regression
  Vector_t input = Vector_t::Random(2);
  for (int i=lower_boundary; i<=n_samples; i++) {
    int current_n_samples = i - lower_boundary;
    // manual computation of mean and error variance
    Vector_t mean (1);
    mean.fill(0.f);
    Vector_t error_var(1);
    error_var.fill(0.f);
    if (i >= 1) {
      for (int j=lower_boundary; j<i; j++) {
        mean(0) += (*annotations)(j,0) / current_n_samples;
      }
      if (current_n_samples == 1)
        error_var(0) = 0.f;
      else {
        for (int j=lower_boundary; j<i; j++) {
          error_var(0) += ((*annotations)(j,0) - mean(0)) * ((*annotations)(j,0) - mean(0)) / (current_n_samples -1);
        }
      }

    }

    // use the regression calculator
    calculator_ptr->change_index_interval(std::make_pair(lower_boundary, i));
    if (i<1) {
      BOOST_CHECK(! calculator_ptr->has_solution());
    } else {
      BOOST_CHECK(calculator_ptr->has_solution());
      // check for equal results
      calculator_ptr->predict(input,pred_mean,pred_var);
      CHECK_CLOSE_(mean(0), pred_mean(0));
      CHECK_CLOSE_(error_var(0), pred_var(0,0));
    }

  }

  // decrement the right interval boundary
  // compare the returned mean and variance with the manually computed one
  calculator_ptr->change_index_interval(std::make_pair(lower_boundary,upper_boundary));
  for (int i=lower_boundary; i<=upper_boundary; i++) {
    int current_n_samples = upper_boundary - i;
    // manual computation of mean and error variance
    Vector_t mean (1);
    mean.fill(0.f);
    Vector_t error_var(1);
    error_var.fill(0.f);
    if (i < upper_boundary) {
      for (int j=i; j<upper_boundary; j++) {
        mean(0) += (*annotations)(j,0) / current_n_samples;
      }
      if (current_n_samples == 1)
        error_var(0) = 0.f;
      else {
        for (int j=i; j<upper_boundary; j++) {
          error_var(0) += ((*annotations)(j,0) - mean(0)) * ((*annotations)(j,0) - mean(0)) / (current_n_samples -1);
        }
      }

    }
    calculator_ptr->change_index_interval(std::make_pair(i, upper_boundary));

    // use the regression calculator
    if (i == upper_boundary) {
      BOOST_CHECK(! calculator_ptr->has_solution());
    } else {
      BOOST_CHECK(calculator_ptr->has_solution());
      // check for equal results
      calculator_ptr->predict(input,pred_mean,pred_var);
      CHECK_CLOSE_(mean(0), pred_mean(0));
      CHECK_CLOSE(error_var(0), pred_var(0,0), 0.001f, 0.0001f);
    }

  }
}

BOOST_AUTO_TEST_CASE(Correctness_1d_1d_linear_regression) {
  auto mat = std::make_shared<Matrix_t> (4,2);
  (*mat) <<  1, 1,
          3, 1,
          5, 1,
          10, 1;
  auto annotations = std::make_shared<Matrix_t>(4,1);
  (*annotations) << 2.0001f, 4.0001f, 5.9998f, 10.9997f;

  auto calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(false, 1E-6f);
  calculator_ptr->initialize(mat, annotations, std::make_pair(0, 4));
  auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
                      serialize_deserialize(calculator_ptr);
#else
                      calculator_ptr;
#endif

  bool success = restored_ptr->has_solution();

  BOOST_CHECK(success);
  // Check for valid results
  Vector_t test_vec_1 (2);
  test_vec_1 << 4,1;
  Vector_t pred_1 (1);
  Matrix_t covar_1 (1,1);
  restored_ptr->predict(test_vec_1, pred_1, covar_1);
  CHECK_CLOSE(pred_1(0), 5.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  BOOST_CHECK(covar_1(0,0) < 1e-7);
  Vector_t test_vec_2 (2);
  test_vec_2 << 10,1;
  Vector_t pred_2 (1);
  Matrix_t covar_2 (1,1);
  restored_ptr->predict(test_vec_2, pred_2, covar_2);
  CHECK_CLOSE(pred_2(0), 11.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  BOOST_CHECK(covar_2(0,0) < 1e-7);
  // Check, that samples further away from the training samples produce a higher variance (lower confidence).
  BOOST_CHECK(covar_1(0,0) < covar_2(0,0));
}

BOOST_AUTO_TEST_CASE(Correctness_QR_1d_1d_linear_regression) {
  // Test settings equal to the previous test
  // This time, force a numerically stable solution
  auto mat = std::make_shared<Matrix_t> (4,2);
  (*mat) <<  1, 1,
          3, 1,
          5, 1,
          10, 1;
  auto annotations = std::make_shared<Matrix_t>(4,1);
  (*annotations) << 2.0001f, 4.0001f, 5.9998f, 10.9997f;

  // Force numerical stability
  bool force_numerical_stability = true;
  auto calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(force_numerical_stability, 1E-6f);
  calculator_ptr->initialize(mat, annotations, std::make_pair(0, 4));
  auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
                      serialize_deserialize(calculator_ptr);
#else
                      calculator_ptr;
#endif

  bool success = restored_ptr->has_solution();

  BOOST_CHECK(success);
  // Check for valid results
  Vector_t test_vec_1 (2);
  test_vec_1 << 4,1;
  Vector_t pred_1 (1);
  Matrix_t covar_1 (1,1);
  restored_ptr->predict(test_vec_1, pred_1, covar_1);
  CHECK_CLOSE(pred_1(0), 5.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  BOOST_CHECK(covar_1(0,0) < 1e-7);
  Vector_t test_vec_2 (2);
  test_vec_2 << 10,1;
  Vector_t pred_2 (1);
  Matrix_t covar_2 (1,1);
  restored_ptr->predict(test_vec_2, pred_2, covar_2);
  CHECK_CLOSE(pred_2(0), 11.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  BOOST_CHECK(covar_2(0,0) < 1e-7);
  // Check, that samples further away from the training samples produce a higher variance (lower confidence).
  BOOST_CHECK(covar_1(0,0) < covar_2(0,0));
}

BOOST_AUTO_TEST_CASE(Correctness_1d_2d_linear_regression) {
  // test linear regression with multiple outputs
  auto mat = std::make_shared<Matrix_t>(4,2);
  (*mat) <<  1, 1,
          3, 1,
          5, 1,
          10, 1;
  auto annotations = std::make_shared<Matrix_t>(4,2);
  (*annotations) << 2.0001f, 0.9999f,
                 4.0001f, 3.0001f,
                 5.9998f, 5.f,
                 10.9997f, 10.0001f;

  auto calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(false, 1E-5f);
  calculator_ptr->initialize(mat, annotations, std::make_pair(0,4));
  bool success = calculator_ptr->has_solution();

  BOOST_CHECK(success);
  // Check for valid results
  Vector_t test_vec_1 (2);
  test_vec_1 << 4,1;
  Vector_t pred_1 (2);
  Matrix_t covar_1 (2,2);
  calculator_ptr->predict(test_vec_1, pred_1, covar_1);
  CHECK_CLOSE(pred_1(0), 5.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  CHECK_CLOSE(pred_1(1), 4.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  Vector_t test_vec_2 (2);
  test_vec_2 << 10,1;
  Vector_t pred_2 (2);
  Matrix_t covar_2 (2,2);
  calculator_ptr->predict(test_vec_2, pred_2, covar_2);
  CHECK_CLOSE(pred_2(0), 11.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  CHECK_CLOSE(pred_2(1), 10.f, 0.05f, 0.0001f);  // cppcheck-suppress variableScope
  BOOST_CHECK(covar_1(0,0) < 1e-7);
  BOOST_CHECK(covar_2(0,0) < 1e-7);
  // Check, that samples further away from the training samples produce a higher variance (lower confidence).
  BOOST_CHECK(covar_1(0,0) < covar_2(0,0));

  BOOST_CHECK(covar_1(1,1) < 1e-7);
  BOOST_CHECK(covar_2(1,1) < 1e-7);
  // Check, that samples further away from the training samples produce a higher variance (lower confidence).
  BOOST_CHECK(covar_1(1,1) < covar_2(1,1));
}

BOOST_AUTO_TEST_CASE(Reject_non_full_rank_2d_1d_linear_regression) {
  // Test the rejection of ill-conditioned data for linear regression
  auto mat = std::make_shared<Matrix_t>(5,3);
  (*mat).setRandom();
  (*mat).col(2).fill(1.f);
  // Decrease the rank
  (*mat).col(1) = 2.0000001f * (*mat).col(0);
  // Annotations don't matter
  auto annotations = std::make_shared<Matrix_t>(5,1);
  (*annotations).setRandom();

  auto calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(false, 1E-5f);
  calculator_ptr->initialize(mat, annotations, std::make_pair(0,5));
  bool success = calculator_ptr->has_solution();
  BOOST_CHECK(success == false);
}

//BOOST_AUTO_TEST_CASE(Speed_2d_1d_linear_regression) {
//
//  struct regression_calc_timer : Utility::ITimefunc {
//    regression_calc_timer(std::shared_ptr<Matrix_t> sample_mat,
//                          std::shared_ptr<Matrix_t> annotation_mat,
//                          std::shared_ptr<LinearRegressionCalculator<float>> reg_calc)
//    : sample_mat(sample_mat), annotation_mat (annotation_mat), reg_calc(reg_calc){
//      line_params = std::shared_ptr<Matrix_t>();
//      covar_mats = std::vector<std::shared_ptr<Matrix_t>>();
//      error_vars = std::vector<float>();
//    }
//
//    int operator () () {
//      reg_calc->initialize(sample_mat, annotation_mat, std::make_pair(0, static_cast<int>(annotation_mat->rows())));
//      return (reg_calc->has_solution() ? (1) : (0));
//    }
//
//    private:
//      std::shared_ptr<Matrix_t> sample_mat;
//      std::shared_ptr<Matrix_t> annotation_mat;
//      std::shared_ptr<Matrix_t> line_params;
//      std::vector<std::shared_ptr<Matrix_t>> covar_mats;
//      std::vector<float> error_vars;
//      std::shared_ptr<LinearRegressionCalculator<float>> reg_calc;
//  };
//
//
//  auto mat = std::shared_ptr<Matrix_t>(new Matrix_t(50,3));
//  mat->setRandom();
//  mat->col(2).fill(1.f);
//  auto annotations = std::shared_ptr<Matrix_t>(new Matrix_t(50,1));
//  annotations->setRandom();
//
//  auto fast_calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(false);
//  auto slow_calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(true);
//
//  float first_time_meassurement = Utility::timeit<std::chrono::nanoseconds>(
//    & regression_calc_timer(mat, annotations, fast_calculator_ptr), false, 3, 2);
//
//  float second_time_meassurement = Utility::timeit<std::chrono::nanoseconds>(
//    & regression_calc_timer(mat, annotations, slow_calculator_ptr), false, 3, 2);
//
//
//  BOOST_CHECK(second_time_meassurement >= first_time_meassurement);
//}


BOOST_AUTO_TEST_CASE(Reject_non_full_rank_QR_4d_1d_linear_regression) {
  auto mat = std::make_shared<Matrix_t>(10,5);
  (*mat).setRandom();
  (*mat).col(4).fill(1.f);
  // Decrease the rank
  (*mat).col(3) = (*mat).col(0) + 2.0000001f * (*mat).col(2);
  auto annotations = std::make_shared<Matrix_t>(10,1);
  (*annotations).setRandom();
  // Use QR decomposition
  bool force_numerical_stability = true;
  auto calculator_ptr = std::make_shared<LinearRegressionCalculator<float>>(force_numerical_stability, 1E-6f);
  calculator_ptr->initialize(mat, annotations, std::make_pair(0,5));
  bool success = calculator_ptr->has_solution();
  BOOST_CHECK(success == false);
}




BOOST_AUTO_TEST_CASE(Correctness_1d_1d_linear_regression_threshold_optimizer) {
  //std::cout << "Testing 1D-1D Regression Threshold Optimizer" << std::endl;
  size_t node_id = 1;
  const int n_threads = 1;
  const unsigned int random_seed = 3001;
  int suggestion_index = 0;
  size_t min_samples_at_leaf = 2;
  size_t n_samples = 7;
  size_t n_thresholds = 40;
  float selected_data [] = {1,2,4,5,8,9,11};
  size_t data_dimension = 1;
  float * features = selected_data;
  float annotations [] = {1,2.5f,4,5,0.1f,-0.5f,-0.9f};
  size_t annotation_dimension = 1;
  float weights [] = {1,1,1,1,1,1,1};
  bool valid = true;

  auto entropy = std::make_shared<ShannonEntropy<float>>();
  auto linear_reg_calc = std::make_shared<LinearRegressionCalculator<float>>(true, 1E-5f);
  auto optimizer = new RegressionThresholdOptimizer<float, float>(n_thresholds,
                                                                  linear_reg_calc,
                                                                  entropy,
                                                                  static_cast<float>(1E-7f),
                                                                  1,
                                                                  random_seed);

  auto optimizer_ptr = std::shared_ptr<RegressionThresholdOptimizer<float, float>>(optimizer);
  auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
                        serialize_deserialize(optimizer_ptr);
#else
                        optimizer_ptr;
#endif
  restored_ptr->prepare_for_optimizing(node_id, n_threads);
  optimization_tuple_t result;
  result = restored_ptr->optimize(node_id,suggestion_index,min_samples_at_leaf,n_samples,
                      selected_data,data_dimension,annotations,annotation_dimension,weights,features,&valid);
  BOOST_CHECK(valid);
  unsigned int samples_left = std::get<2>(result);
  unsigned int samples_right = std::get<3>(result);
  BOOST_CHECK((samples_left == 4) && (samples_right == 3));
}

BOOST_AUTO_TEST_CASE(Correctness_1d_1d_constant_regression_threshold_optimizer) {
  size_t node_id = 1;
  const int n_threads = 1;
  const unsigned int random_seed = 3001;
  int suggestion_index = 0;
  size_t min_samples_at_leaf = 2;
  size_t n_samples = 7;
  size_t n_thresholds = 40;
  float selected_data [] = {1,2,4,5,8,9,11};
  size_t data_dimension = 1;
  float * features = selected_data;
  float annotations [] = {1,2.5f,4,5,0.1f,-0.5f,-0.9f};
  size_t annotation_dimension = 1;
  float weights [] = {1,1,1,1,1,1,1};
  bool valid = true;

  auto entropy = std::make_shared<ShannonEntropy<float>>();
  auto linear_reg_calc = std::make_shared<ConstantRegressionCalculator<float>>();
  auto optimizer = new RegressionThresholdOptimizer<float, float>(n_thresholds,
                                                                  linear_reg_calc,
                                                                  entropy,
                                                                  static_cast<float>(1E-7f),
                                                                  1,
                                                                  random_seed);

  auto optimizer_ptr = std::shared_ptr<RegressionThresholdOptimizer<float, float>>(optimizer);
  auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
                        serialize_deserialize(optimizer_ptr);
#else
                        optimizer_ptr;
#endif
  restored_ptr->prepare_for_optimizing(node_id, n_threads);
  optimization_tuple_t result;
  result = restored_ptr->optimize(node_id,suggestion_index,min_samples_at_leaf,n_samples,
                      selected_data,data_dimension,annotations,annotation_dimension,weights,features,&valid);
  BOOST_CHECK(valid);
  unsigned int samples_left = std::get<2>(result);
  unsigned int samples_right = std::get<3>(result);
  BOOST_CHECK((samples_left == 4) && (samples_right == 3));
}

//BOOST_AUTO_TEST_CASE(Correctness_1d_2d_linear_regression_threshold_optimizer) {
//  size_t node_id = 1;
//  const int n_threads = 1;
//  unsigned int random_seed = 2001;
//  int suggestion_index = 0;
//  size_t min_samples_at_leaf = 2;
//  size_t n_samples = 7;
//  size_t n_thresholds = 40;
//  float selected_data [] = {1,2,4,5,8,9,11};
//  size_t data_dimension = 1;
//  float * features = selected_data;
//  float annotations [] = {3,10, 4.5f,12.5f, 6,13.5f, 7,14.8f, 0.1f,19, -0.5f,18.7f, -0.9f,21};
//  size_t annotation_dimension = 2;
//  float weights [] = {1,1,1,1,1,1,1};
//  bool valid = false;
//
//  size_t annotation_step = 1;
//  auto entropy = std::make_shared<ShannonEntropy<float>>();
//  auto linear_reg_calc = std::make_shared<LinearRegressionCalculator<float>>(true, 1E-5f);
//  auto optimizer = std::make_shared<RegressionThresholdOptimizer<float,float>> (n_thresholds, linear_reg_calc,entropy);
//  optimizer->prepare_for_optimizing(node_id, n_threads);
//  optimization_tuple_t result;
//  result = optimizer->optimize(node_id,suggestion_index,min_samples_at_leaf,n_samples,
//                      selected_data,data_dimension,annotations,annotation_dimension,weights,features,&valid);
//  BOOST_CHECK(valid);
//  unsigned int samples_left = std::get<2>(result);
//  unsigned int samples_right = std::get<3>(result);
//  BOOST_CHECK((samples_left == 4) && (samples_right == 3));
//}
//
//BOOST_AUTO_TEST_CASE(Correctness_1d_2d_constant_regression_threshold_optimizer) {
//  size_t node_id = 1;
//  const int n_threads = 1;
//  unsigned int random_seed = 2001;
//  int suggestion_index = 0;
//  size_t min_samples_at_leaf = 2;
//  size_t n_samples = 7;
//  size_t n_thresholds = 40;
//  float selected_data [] = {1,2,4,5,8,9,11};
//  size_t data_dimension = 1;
//  float * features = selected_data;
//  float annotations [] = {3,10, 4.5f,12.5f, 6,13.5f, 7,14.8f, 0.1f,19, -0.5f,18.7f, -0.9f,21};
//  size_t annotation_dimension = 2;
//  float weights [] = {1,1,1,1,1,1,1};
//  bool valid = false;
//
//  size_t annotation_step = 1;
//  auto entropy = std::make_shared<ShannonEntropy<float>>();
//  auto linear_reg_calc = std::make_shared<ConstantRegressionCalculator<float>>();
//  auto optimizer = std::make_shared<RegressionThresholdOptimizer<float,float>> (n_thresholds, linear_reg_calc,entropy);
//  optimizer->prepare_for_optimizing(node_id, n_threads);
//  optimization_tuple_t result;
//  result = optimizer->optimize(node_id,suggestion_index,min_samples_at_leaf,n_samples,
//                      selected_data,data_dimension,annotations,annotation_dimension,weights,features,&valid);
//  BOOST_CHECK(valid);
//  unsigned int samples_left = std::get<2>(result);
//  unsigned int samples_right = std::get<3>(result);
//  BOOST_CHECK((samples_left == 4) && (samples_right == 3));
//}


BOOST_AUTO_TEST_CASE(Correctness_regression_leaf_manager) {
   StandardFeatureSelectionProvider *selection_provider  = new StandardFeatureSelectionProvider(2,1,2,2);
   std::shared_ptr<StandardFeatureSelectionProvider> selection_prov_ptr (selection_provider);
   size_t annotation_dimension = 1;
   size_t input_dimension = 2;
   size_t n_samples = 6;
   float * input_data  = new float [input_dimension * n_samples];
   input_data[0] = 1;
   input_data[1] = 10;
   input_data[2] = 2;
   input_data[3] = 5;
   input_data[4] = 4;
   input_data[5] = 13;
   input_data[6] = 5;
   input_data[7] = 2;
   input_data[8] = 8;
   input_data[9] = -5;
   input_data[10] = 11;
   input_data[11] = 2;
   std::shared_ptr<const float> input_ptr (input_data, []( float *p ) { delete[] p; });

   size_t ids[] = {0,1,2,3,4,5};
   std::vector<size_t> element_ids (ids, ids + sizeof(ids) / sizeof(size_t) );

   float *annotations = new float[annotation_dimension * n_samples];
   annotations[0] = 1;
   annotations[1] = 3;
   annotations[2] = 4;
   annotations[3] = 4.1f;
   annotations[4] = 7;
   annotations[5] = 12;
   std::shared_ptr<const float> annot_ptr (annotations, []( float *p ) { delete[] p; });

   size_t node_id = 1;
   auto input_array = external(input_data,
                               makeVector(n_samples,
                                          input_dimension));
   auto annot_array = external(annotations,
                               makeVector(n_samples,
                                          annotation_dimension));
   UnchangedDataProvider<float,float> data_prov (input_array, annot_array);
   auto entropy = std::make_shared<ShannonEntropy<float>>();
   auto linear_reg_calc = std::make_shared<LinearRegressionCalculator<float>>(true, 1E-6f);
   auto leaf_manager_ptr = std::make_shared<RegressionLeafManager<float>>(selection_prov_ptr, static_cast<size_t>(2), linear_reg_calc, entropy);
   auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
     serialize_deserialize(leaf_manager_ptr);
#else
     leaf_manager_ptr;
#endif

   leaf_manager_ptr->make_leaf(node_id,element_ids,data_prov);

   restored_ptr =
#ifdef SERIALIZATION_ENABLED
     serialize_deserialize(restored_ptr);
#else
     restored_ptr;
#endif

   float test_sample [] = {6,300};

   auto result = leaf_manager_ptr->get_result(node_id,test_sample,1);

   std::shared_ptr<std::vector<float>> prediction = result.first;
   CHECK_CLOSE_((* prediction)[0],6.01647f);
   CHECK_CLOSE_((* result.second)[0],0.168014571f);
}


BOOST_AUTO_TEST_CASE(Correctness_constant_regression_leaf_manager) {
   StandardFeatureSelectionProvider *selection_provider  = new StandardFeatureSelectionProvider(2,1,2,2);
   std::shared_ptr<StandardFeatureSelectionProvider> selection_prov_ptr (selection_provider);
   size_t annotation_dimension = 1;
   size_t input_dimension = 2;
   size_t n_samples = 6;
   // input data is irrelevant
   float * input_data  = new float [input_dimension * n_samples];
   std::shared_ptr<const float> input_ptr (input_data, []( float *p ) { delete[] p; });

   size_t ids[] = {0,1,2,3,4,5};
   std::vector<size_t> element_ids (ids, ids + sizeof(ids) / sizeof(size_t) );

   float *annotations = new float[annotation_dimension * n_samples];
   annotations[0] = 1;
   annotations[1] = 3;
   annotations[2] = 4;
   annotations[3] = 4.1f;
   annotations[4] = 7;
   annotations[5] = 12;
   std::shared_ptr<const float> annot_ptr (annotations, []( float *p ) { delete[] p; });

   float mean = 0.f;
   for (int i=0; i<n_samples; i++) {
     mean += annotations[i] / static_cast<float>(n_samples);
   }
   float error_var = 0.f;
   for (int i=0; i<n_samples; i++) {
     error_var += (annotations[i] - mean)* (annotations[i] - mean) / static_cast<float>(n_samples -1);
   }
   float pred_var = error_var;

   size_t node_id = 1;
   auto input_array = external(input_data,
                               makeVector(n_samples,
                                          input_dimension));
   auto annot_array = external(annotations,
                               makeVector(n_samples,
                                          annotation_dimension));
   UnchangedDataProvider<float,float> data_prov (input_array, annot_array);
   auto entropy = std::make_shared<ShannonEntropy<float>>();
   auto linear_reg_calc = std::make_shared<ConstantRegressionCalculator<float>>();
   auto leaf_manager_ptr = std::make_shared<RegressionLeafManager<float>>(selection_prov_ptr, static_cast<size_t>(1), linear_reg_calc, entropy);
   auto restored_ptr =
#ifdef SERIALIZATION_ENABLED
     serialize_deserialize(leaf_manager_ptr);
#else
     leaf_manager_ptr;
#endif

   restored_ptr->make_leaf(node_id,element_ids,data_prov);

   restored_ptr =
#ifdef SERIALIZATION_ENABLED
     serialize_deserialize(restored_ptr);
#else
     restored_ptr;
#endif

   float test_sample [] = {6,300};

   auto result = restored_ptr->get_result(node_id,test_sample,1);

   std::shared_ptr<std::vector<float>> prediction = result.first;
   CHECK_CLOSE_((* prediction)[0],mean);
   CHECK_CLOSE_((* result.second)[0],pred_var);
}


BOOST_AUTO_TEST_CASE(Correctness_regression_tree) {
  size_t annot_dim = 2;
  size_t input_dim = 1;
  size_t n_samples = 8;
  float * input_data  = new float [input_dim * n_samples];
  input_data[0] = 1;
  input_data[1] = 2;
  input_data[2] = 4;
  input_data[3] = 5;
  input_data[4] = 8;
  input_data[5] = 9;
  input_data[6] = 11;
  input_data[7] = 14;
  std::shared_ptr<const float> input_ptr (input_data, []( float *p ) { delete[] p; });

  float *annotations = new float[annot_dim * n_samples];
  annotations[0] = 1;
  annotations[1] = 10;
  annotations[2] = 2.5f;
  annotations[3] = 11.5f;
  annotations[4] = 4;
  annotations[5] = 14.5f;
  annotations[6] = 5;
  annotations[7] = 14.8f;
  annotations[8] = 0.1f;
  annotations[9] = 19;
  annotations[10] = -0.5f;
  annotations[11] = 18.7f;
  annotations[12] = -0.9f;
  annotations[13] = 21;
  annotations[14] = -1.5f;
  annotations[15] = 24;
  std::shared_ptr<const float> annot_ptr (annotations, []( float *p ) { delete[] p; });

  size_t n_features = input_dim;
  unsigned int max_depth = 2;
  size_t test_n_features_per_node = input_dim;
  size_t n_thresholds = 20;
  unsigned int random_seed = 3001;

  auto tree = fertilized::construct_regression_tree<float>(n_features, max_depth, test_n_features_per_node, n_thresholds, 4, 8, static_cast<float>(1E-7), true,random_seed);

   auto input_array = external(input_data,
                               makeVector(n_samples,
                                          input_dim));
   auto annot_array = external(annotations,
                               makeVector(n_samples,
                                          annot_dim));
   UnchangedDataProvider<float,float> data_prov (input_array, annot_array);

  tree->fit_dprov(&data_prov,true);

  auto restored_tree =
#ifdef SERIALIZATION_ENABLED
    serialize_deserialize(tree);
#else
    tree;
#endif

  BOOST_CHECK(restored_tree->get_n_nodes() == 3);

  float sample1 [] = {3,200};
  float sample2 [] = {4.5,200};
  float sample3 [] = {19.5,200};
  auto result1 = tree->predict_leaf_result(sample1,1);
  auto result2 = tree->predict_leaf_result(sample2,1);
  auto result3 = tree->predict_leaf_result(sample3,1);
  // Assure, that the regression model has non-linear behavior in the first annotation dimension:
  // sample1[0] < sample2[0] < sample3[0]
  // => result1[0] < result2[0] > result3[0]
  BOOST_CHECK((* result1.first)[0] < (* result2.first)[0]);
  BOOST_CHECK((* result2.first)[0] > (* result3.first)[0]);
  // but also linear behavior in the second annotation dimension:
  // sample1[0] < sample2[0] < sample3[0]
  // => result1[1] < result2[1] < result3[1]
  BOOST_CHECK((* result1.first)[1] < (* result2.first)[1]);
  BOOST_CHECK((* result2.first)[1] < (* result3.first)[1]);
}


BOOST_AUTO_TEST_CASE(Correctness_regression_forest) {
  size_t annot_dim = 2;
  size_t input_dim = 1;
  size_t n_samples = 8;
  float * input_data  = new float [input_dim * n_samples];
  input_data[0] = 1;
  input_data[1] = 2;
  input_data[2] = 4;
  input_data[3] = 5;
  input_data[4] = 8;
  input_data[5] = 9;
  input_data[6] = 11;
  input_data[7] = 14;
  std::shared_ptr<const float> input_ptr (input_data, []( float *p ) { delete[] p; });

  float *annotations = new float[annot_dim * n_samples];
  annotations[0] = 1;
  annotations[1] = 10;
  annotations[2] = 2.5f;
  annotations[3] = 11.5f;
  annotations[4] = 4;
  annotations[5] = 14.5f;
  annotations[6] = 5;
  annotations[7] = 14.8f;
  annotations[8] = 0.1f;
  annotations[9] = 19;
  annotations[10] = -0.5f;
  annotations[11] = 18.7f;
  annotations[12] = -0.9f;
  annotations[13] = 21;
  annotations[14] = -1.5f;
  annotations[15] = 24;
  std::shared_ptr<const float> annot_ptr (annotations, []( float *p ) { delete[] p; });
#ifdef SERIALIZATION_ENABLED
  auto restored_ent = serialize_deserialize(std::make_shared<fertilized::ShannonEntropy<float>>());
  auto rest_reg_cal = serialize_deserialize(std::make_shared<fertilized::LinearRegressionCalculator<float>>());
  auto rest_thr_opt = serialize_deserialize(std::make_shared<fertilized::RegressionThresholdOptimizer<float, float>>(100, rest_reg_cal, restored_ent));
  auto rest_feat_cal = serialize_deserialize(std::make_shared<fertilized::AlignedSurfaceCalculator<float, float>>());
  auto rest_fsp_cal = serialize_deserialize(std::make_shared<fertilized::StandardFeatureSelectionProvider>(1, 1, 100, 100, 1));
  auto rest_class = serialize_deserialize(std::make_shared<fertilized::ThresholdDecider<float, float, float>>(rest_fsp_cal, rest_feat_cal, rest_thr_opt, 0, 1));
  auto rest_lm = serialize_deserialize(std::shared_ptr<RegressionLeafManager<float>>(new RegressionLeafManager<float>(rest_fsp_cal, 100, rest_reg_cal, restored_ent, true, 1)));
  auto rest_t = serialize_deserialize(fertilized::construct_regression_tree<float>(10, 10, 2, 2));
  auto rest_f = serialize_deserialize(fertilized::construct_regression_forest<float>(10, 10, 2, 2, 10));
#endif
  size_t n_features = input_dim;
  unsigned int max_depth = 2;
  size_t n_trees = 4;
  unsigned int num_threads = 1;
  size_t test_n_features_per_node = input_dim;
  size_t n_thresholds = 20;
  unsigned int random_seed = 3001;

  auto forest = fertilized::construct_regression_forest<float>(n_features, max_depth, test_n_features_per_node, n_thresholds ,n_trees, 4, 8, static_cast<float>(1E-7), true, random_seed);

   auto input_array = external(input_data,
                               makeVector(n_samples,
                                          input_dim));
   auto annot_array = external(annotations,
                               makeVector(n_samples,
                                          annot_dim));
   UnchangedFDataProvider<float,float> *data_prov = new UnchangedFDataProvider<float, float>(input_array, annot_array);
  std::shared_ptr<UnchangedFDataProvider<float,float>> data_prov_ptr (data_prov);
  LocalExecutionStrategy<float, float, float,
                        std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,
                        std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>> exec_strategy (num_threads);
  forest->fit_dprov(data_prov_ptr,&exec_strategy);

  auto restored_forest =
#ifdef SERIALIZATION_ENABLED
    serialize_deserialize(forest);
#else
    forest;
#endif

  float sample1 [] = {3,200};
  float sample2 [] = {4.5,200};
  float sample3 [] = {8.5,200};
  auto result1 = forest->predict_forest_result(sample1,1);
  auto result2 = forest->predict_forest_result(sample2,1);
  auto result3 = forest->predict_forest_result(sample3,1);
  for (int tree_num = 0; tree_num < n_trees; tree_num++) {
    auto single_result1 = result1[tree_num].first;
    auto single_result2 = result2[tree_num].first;
    auto single_result3 = result3[tree_num].first;
    // Assure, that the regression model has non-linear behavior in the first annotation dimension:
    // sample1[0] < sample2[0] < sample3[0]
    // => result1[0] < result2[0] > result3[0]
    BOOST_CHECK((* single_result1.first)[0] < (* single_result2.first)[0]);
    BOOST_CHECK((* single_result2.first)[0] > (* single_result3.first)[0]);
    // but also linear behavior in the second annotation dimension:
    // sample1[0] < sample2[0] < sample3[0]
    // => result1[1] < result2[1] < result3[1]
    BOOST_CHECK((* single_result1.first.get())[1] < (* single_result2.first)[1]);
    BOOST_CHECK((* single_result2.first.get())[1] < (* single_result3.first)[1]);

  }

}




BOOST_AUTO_TEST_SUITE_END();


