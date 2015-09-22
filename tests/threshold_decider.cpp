// Author: Christoph Lassner.
#include <fertilized/fertilized.h>

#include <random>
#include <iostream>

#include "boost/test/unit_test.hpp"

#include "timeit.h"
#include "setup.h"


using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_Deciders);

BOOST_AUTO_TEST_CASE(Correctness_Parallel_Tree_Training) {
  auto soil = Soil<double, double>();
  auto eng = std::mt19937_64();
  auto feat_dist = std::normal_distribution<double>(0., 1.);
  auto class_dist = std::uniform_int_distribution<uint>(0, 1);
  auto dprov_fixture_threaded =
    ClassificationDataProviderFixture<double>(
      100, // n samples
      100, // sample dim
      2, // n classes
      [&feat_dist, &eng](double *val, size_t ind) { for (int i = 0; i < 100; ++i) { val[i] = feat_dist(eng); } }, // data generator
      [&class_dist, &eng](uint *cls, size_t ind) { *cls = class_dist(eng); }, // annotation generator
      [](float *weight, size_t ind) {*weight = 1.f;}, // weight generator
      false,
      1);
  auto forest_unthreaded = soil.StandardClassificationTree(2, 100, 0, 2, 10, 1, 2, 0., true, 1, "induced", 2.f, 1);
  auto forest_threaded = soil.StandardClassificationTree(2, 100, 0, 2, 10, 1, 2, 0., true, 1, "induced", 2.f, 4);
  // std::cout << "Before fitting: " << std::endl;
  BOOST_CHECK((*forest_unthreaded) == (*forest_threaded));
  // std::cout << "Fitting unthreaded..." << std::endl;
  forest_unthreaded -> fit(dprov_fixture_threaded.input_array, dprov_fixture_threaded.annot_array);
  // std::cout << "Fitting threaded..." << std::endl;
  forest_threaded -> fit(dprov_fixture_threaded.input_array, dprov_fixture_threaded.annot_array);
  BOOST_CHECK(*forest_threaded == *forest_unthreaded);
  BOOST_CHECK(*(forest_threaded -> get_decider()) == *(forest_unthreaded -> get_decider()));
}

BOOST_AUTO_TEST_CASE(Correctness_Deciders_threading) {
  auto s = Soil<double, double>();
  auto selprov = s.StandardFeatureSelectionProvider(2, // selections per node
                                                    1, // selection dimension
                                                    100); // selections available
  auto featcalc = s.AlignedSurfaceCalculator();
  auto gainc = s.EntropyGain(s.ShannonEntropy());
  auto threshopt = s.RandomizedClassificationThresholdOptimizer(10, // number of thresholds
                                                                2,  // number of classes
                                                                gainc);
  auto tdec_threaded = s.ThresholdDecider(selprov, featcalc, threshopt,
                                          0, // valid features to use (0 ignores)
                                          4); // number of threads

  auto selprov_unthreaded = s.StandardFeatureSelectionProvider(2, // selections per node
                                                    1, // selection dimension
                                                    100); // selections available
  auto threshopt_unthreaded = s.RandomizedClassificationThresholdOptimizer(10, // number of thresholds
                                                                2,  // number of classes
                                                                gainc);
  auto tdec_unthreaded = s.ThresholdDecider(selprov_unthreaded, featcalc, threshopt_unthreaded, 0, 1);
  auto eng = std::mt19937_64();
  auto feat_dist = std::normal_distribution<double>(0., 1.);
  auto class_dist = std::uniform_int_distribution<uint>(0, 1);
  auto dprov_fixture_threaded =
    ClassificationDataProviderFixture<double>(1000, // n samples
      100, // sample dim
      2, // n classes
      [&feat_dist, &eng](double *val, size_t ind) { for (int i = 0; i < 100; ++i) { val[i] = feat_dist(eng); } }, // data generator
      [&class_dist, &eng](uint *cls, size_t ind) { *cls = class_dist(eng); }, // annotation generator
      [](float *weight, size_t ind) {*weight = 1.f;}, // weight generator
      false,
      1);
  bool make_to_leaf_threaded;
  auto elem_list_left_threaded = std::make_shared<fertilized::elem_id_vec_t>();
  auto elem_list_right_threaded = std::make_shared<fertilized::elem_id_vec_t>();
  tdec_threaded -> optimize_and_set_for_node(0, 0, 1,
    *(dprov_fixture_threaded.dprov -> get_initial_sample_list()),
    *dprov_fixture_threaded.dprov,
    &make_to_leaf_threaded,
    &elem_list_left_threaded,
    &elem_list_right_threaded);
  eng = std::mt19937_64();
  auto dprov_fixture_unthreaded =
    ClassificationDataProviderFixture<double>(1000, // n samples
      100, // sample dim
      2, // n classes
      [&feat_dist, &eng](double *val, size_t ind) { for (int i = 0; i < 100; ++i) { val[i] = feat_dist(eng); } }, // data generator
      [&class_dist, &eng](uint *cls, size_t ind) { *cls = class_dist(eng); }, // annotation generator
      [](float *weight, size_t ind) {*weight = 1.f;}, // weight generator
      false,
      1);
  bool make_to_leaf_unthreaded;
  auto elem_list_left_unthreaded = std::make_shared<fertilized::elem_id_vec_t>();
  auto elem_list_right_unthreaded = std::make_shared<fertilized::elem_id_vec_t>();
  tdec_unthreaded -> optimize_and_set_for_node(0, 0, 1,
    *(dprov_fixture_unthreaded.dprov -> get_initial_sample_list()),
    *dprov_fixture_unthreaded.dprov,
    &make_to_leaf_unthreaded,
    &elem_list_left_unthreaded,
    &elem_list_right_unthreaded);

  BOOST_REQUIRE(make_to_leaf_threaded == make_to_leaf_unthreaded);
  BOOST_REQUIRE((*elem_list_left_threaded) == (*elem_list_left_unthreaded));
  BOOST_REQUIRE((*elem_list_right_threaded) == (*elem_list_right_unthreaded));
};

BOOST_AUTO_TEST_CASE(Correctness_Deciders_early_stop) {
  auto s = Soil<double, double>();
  auto selprov = s.StandardFeatureSelectionProvider(1, // selections per node
                                                    1, // selection dimension
                                                    1); // selections available
  auto featcalc = s.AlignedSurfaceCalculator();
  auto gainc = s.EntropyGain(s.ShannonEntropy());
  auto threshopt = s.RandomizedClassificationThresholdOptimizer(10, // number of thresholds
                                                                2,  // number of classes
                                                                gainc,
                                                                1E-11f); // gain threshold
  auto tdec_early = s.ThresholdDecider(selprov, featcalc, threshopt,
                                          10, // valid features to use (0 ignores)
                                          1, // number of threads
                                          false, 0.05f, 0, // hough heuristic
                                          true); // early stopping
  auto lm_early = s.ClassificationLeafManager(2);
  auto tree_early = s.Tree(10000, 1, 2, tdec_early, lm_early);

  auto selprov_nonearly = s.StandardFeatureSelectionProvider(1, // selections per node
                                                    1, // selection dimension
                                                    1); // selections available
  auto threshopt_nonearly = s.RandomizedClassificationThresholdOptimizer(10, // number of thresholds
                                                                2,  // number of classes
                                                                gainc,
                                                                1E-11f); // gain threshold
  auto featcalc_nonearly = s.AlignedSurfaceCalculator();
  auto tdec_nonearly = s.ThresholdDecider(selprov_nonearly, featcalc_nonearly, threshopt_nonearly,
                                          10, // valid features to use (0 ignores)
                                          1, // number of threads
                                          false, 0.05f, 0, // hough heuristic
                                          false); // early stopping
  auto lm_nonearly = s.ClassificationLeafManager(2);
  auto tree_nonearly = s.Tree(10000, 1, 2, tdec_nonearly, lm_nonearly);

  auto eng = std::mt19937_64();
  auto feat_dist = std::normal_distribution<double>(0., 1.);
  auto class_dist = std::uniform_int_distribution<uint>(0, 1);
  auto dprov_fixture_threaded =
    ClassificationDataProviderFixture<double>(100, // n samples
      1, // sample dim
      2, // n classes
      [&feat_dist, &eng](double *val, size_t ind) { *val = feat_dist(eng); }, // data generator
      [&class_dist, &eng](uint *cls, size_t ind) { *cls = class_dist(eng); }, // annotation generator
      [](float *weight, size_t ind) {*weight = 1.f;}, // weight generator
      false,
      1);
  auto eng_nonearly = std::mt19937_64();
  auto feat_dist_nonearly = std::normal_distribution<double>(0., 1.);
  auto class_dist_nonearly = std::uniform_int_distribution<uint>(0, 1);
  auto dprov_fixture_nonearly =
    ClassificationDataProviderFixture<double>(100, // n samples
      1, // sample dim
      2, // n classes
      [&feat_dist_nonearly, &eng_nonearly](double *val, size_t ind) { *val = feat_dist_nonearly(eng_nonearly); }, // data generator
      [&class_dist_nonearly, &eng_nonearly](uint *cls, size_t ind) { *cls = class_dist_nonearly(eng_nonearly); }, // annotation generator
      [](float *weight, size_t ind) {*weight = 1.f;}, // weight generator
      false,
      1);

  //BOOST_REQUIRE(*tree_early == *tree_nonearly);
  tree_early -> fit(dprov_fixture_threaded.input_array, dprov_fixture_threaded.annot_array, false);
  //std::cout << dprov_fixture_threaded.input_array << std::endl;
  tree_nonearly -> fit(dprov_fixture_nonearly.input_array, dprov_fixture_nonearly.annot_array, false);
  //std::cout << dprov_fixture_threaded.annot_array << std::endl;
  while (tree_early -> get_marks().size() > 0) {
    tree_early -> make_node(dprov_fixture_threaded.dprov.get(), false);
    tree_nonearly -> make_node(dprov_fixture_nonearly.dprov.get(), false);
    const std::deque<node_todo_tuple_t> &marks_early = tree_early -> get_marks();
    const std::deque<node_todo_tuple_t> &marks_nonearly = tree_nonearly -> get_marks();
    BOOST_REQUIRE(marks_early.size() == marks_nonearly.size());
    for (size_t i = 0; i < marks_early.size(); ++i) {
      BOOST_CHECK(*std::get<0>(marks_early.at(i)) == *(std::get<0>(marks_early.at(i))));
      BOOST_CHECK(std::get<1>(marks_early.at(i)) == std::get<1>(marks_early.at(i)));
      BOOST_CHECK(std::get<2>(marks_early.at(i)) == std::get<2>(marks_early.at(i)));
    }
  }
  BOOST_REQUIRE((*tree_early) == (*tree_nonearly));
};

BOOST_AUTO_TEST_SUITE_END();
