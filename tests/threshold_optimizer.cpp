/* Author: Christoph Lassner. */
#include <fertilized/global.h>
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <functional>
#include <string>
#include <vector>
#include <type_traits>
#include <random>

#include <fertilized/impurities/shannonentropy.h>
#include <fertilized/impurities/inducedentropy.h>
#include <fertilized/gains/entropygain.h>
#include <fertilized/threshold_optimizers/ithresholdoptimizer.h>
#include <fertilized/threshold_optimizers/classificationthresholdoptimizer.h>
#include <fertilized/threshold_optimizers/twosideclassificationthresholdoptimizer.h>
#include <fertilized/threshold_optimizers/varianceclassificationthresholdoptimizer.h>
#include <fertilized/threshold_optimizers/alternatingthresholdoptimizer.h>
#include <fertilized/threshold_optimizers/randomizedclassificationthresholdoptimizer.h>
#include <fertilized/util/sampling.h>

#include "./setup.h"
#include "./timeit.h"

// Required objects.
using fertilized::EntropyGain;
using fertilized::ShannonEntropy;
using fertilized::InducedEntropy;
using fertilized::EThresholdSelection;
using fertilized::IDataProvider;

// Test objects.
using fertilized::IThresholdOptimizer;
using fertilized::ClassificationThresholdOptimizer;
using fertilized::TwoSideClassificationThresholdOptimizer;
using fertilized::RandomizedClassificationThresholdOptimizer;
using fertilized::VarianceClassificationThresholdOptimizer;
using fertilized::AlternatingThresholdOptimizer;
using fertilized::unique_indices;

BOOST_AUTO_TEST_SUITE(Correctness_ThresholdOptimizers);
//---------------------------------------------------------------------------//
// Best threshold found and threshold optimization results correct.

template <typename T, typename F>
void test_ClassThresholdOptFindsPerfectSplit(
  IThresholdOptimizer<T, F, unsigned int> *to, float gain2, bool twosided2,
  IThresholdOptimizer<T, F, unsigned int> *to3, float gain3, bool twosided3) {
  // Two classes.
  ClassificationDataProviderFixture<T> dp2(300, 10, 2,
    [](T * val_p, size_t i){}, // Irrelevant for this test.
    [](unsigned int *annot_p, size_t i){
      *annot_p = static_cast<unsigned int>(i < 100 || i >= 200 ? (i % 2) : 0);
  });
  auto elem_ids = dp2.dprov -> get_initial_sample_list();
  std::vector<F> feats(300);
  for (size_t i =0; i < 300; ++i)
    feats[i] = static_cast<F>(i);
  bool valid;
  auto res = to -> optimize(0, 0, 1, 300, dp2.input_data.get(),
                                      10, dp2.annot_data.get(),
                                       1, dp2.weights.get(), &feats[0], &valid);
  BOOST_REQUIRE(valid);
  if (std::is_floating_point<F>())
    BOOST_CHECK(std::get<1>(res) == EThresholdSelection::less_only &&
                (abs(std::get<0>(res).first - 99.5) < 0.5 || abs(std::get<0>(res).first - 200.5) < 0.5) ||
                std::get<1>(res) == EThresholdSelection::greater_only &&
                (abs(std::get<0>(res).second - 99.5) < 0.5 || abs(std::get<0>(res).second - 200.5) < 0.5) ||
                std::get<1>(res) == EThresholdSelection::both &&
                (abs(std::get<0>(res).first - 99.5) < 0.5 && abs(std::get<0>(res).second - 200.5) < 0.5 ||
                 abs(std::get<0>(res).first - 200.5) < 0.5 && abs(std::get<0>(res).second - 99.5) < 0.5));
  else
    BOOST_CHECK(std::get<1>(res) == EThresholdSelection::less_only &&
                (std::get<0>(res).first == 100 || std::get<0>(res).first == 201) ||
                std::get<1>(res) == EThresholdSelection::greater_only &&
                (std::get<0>(res).second == 99 || std::get<0>(res).second == 200) ||
                std::get<1>(res) == EThresholdSelection::both &&
                (std::get<0>(res).first == 100 && std::get<0>(res).second == 200 ||
                 std::get<0>(res).first == 201 && std::get<0>(res).second == 99));
  BOOST_CHECK_EQUAL(std::get<2>(res) + std::get<3>(res), 300);
  CHECK_CLOSE_(std::get<4>(res), gain2);
  // Three classes.
  ClassificationDataProviderFixture<T> dp3(300, 10, 3,
    [](T * val_p, size_t i){}, // Irrelevant for this test.
    [](unsigned int *annot_p, size_t i){
      *annot_p = static_cast<unsigned int>(i / 100);
  });
  auto elem_ids3 = dp3.dprov -> get_initial_sample_list();
  auto res3 = to3 -> optimize(0, 0, 1, 300, dp3.input_data.get(),
                                        10, dp3.annot_data.get(),
                                         1, dp3.weights.get(),
                              &feats[0], &valid);
  BOOST_REQUIRE(valid);
  if (std::is_floating_point<F>())
    BOOST_CHECK(std::get<1>(res) == EThresholdSelection::less_only &&
                (abs(std::get<0>(res).first - 99.5) < 0.5 || abs(std::get<0>(res).first - 200.5) < 0.5) ||
                std::get<1>(res) == EThresholdSelection::greater_only &&
                (abs(std::get<0>(res).second - 99.5) < 0.5 || abs(std::get<0>(res).second - 200.5) < 0.5) ||
                std::get<1>(res) == EThresholdSelection::both &&
                (abs(std::get<0>(res).first - 99.5) < 0.5 && abs(std::get<0>(res).second - 200.5) < 0.5 ||
                 abs(std::get<0>(res).first - 200.5) < 0.5 && abs(std::get<0>(res).second - 99.5) < 0.5));
  else
    BOOST_CHECK(std::get<1>(res) == EThresholdSelection::less_only &&
                (std::get<0>(res).first == 100 || std::get<0>(res).first == 201) ||
                std::get<1>(res) == EThresholdSelection::greater_only &&
                (std::get<0>(res).second == 99 || std::get<0>(res).second == 200) ||
                std::get<1>(res) == EThresholdSelection::both &&
                (std::get<0>(res).first == 100 && std::get<0>(res).second == 200 ||
                 std::get<0>(res).first == 201 && std::get<0>(res).second == 99));
  BOOST_CHECK_EQUAL(std::get<2>(res3) + std::get<3>(res3), 300);
  CHECK_CLOSE_(std::get<4>(res3), gain3);
}

BOOST_AUTO_TEST_CASE(Correctness_ThresholdFindsPerfectSplit) {
  auto ef = EntropyGainFixture<float>();
  ClassificationThresholdOptimizer<float, float, unsigned int> to2(true, 2, ef.egain);
  to2.prepare_for_optimizing(0, 1);
  ClassificationThresholdOptimizer<float, float, unsigned int> to3(true, 3, ef.egain);
  to3.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to2, 0.0460885167f, false,
                                          &to3, 0.918295920f, false);
  TwoSideClassificationThresholdOptimizer<float, float, unsigned int> to22(true, 2, ef.egain);
  to22.prepare_for_optimizing(0, 1);
  TwoSideClassificationThresholdOptimizer<float, float, unsigned int> to32(true, 3, ef.egain);
  to32.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to22, 0.254974544f, true,
                                          &to32, 0.918295920f, true);
  TwoSideClassificationThresholdOptimizer<float, unsigned int, unsigned int> to2fui2(true, 2, ef.egain);
  to2fui2.prepare_for_optimizing(0, 1);
  TwoSideClassificationThresholdOptimizer<float, unsigned int, unsigned int> to3fui2(true, 3, ef.egain);
  to3fui2.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to2fui2, 0.254974544f, true,
                                          &to3fui2, 0.918295920f, true);
  ClassificationThresholdOptimizer<float, unsigned int, unsigned int> to2fui(true, 2, ef.egain);
  to2fui.prepare_for_optimizing(0, 1);
  ClassificationThresholdOptimizer<float, unsigned int, unsigned int> to3fui(true, 3, ef.egain);
  to3fui.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to2fui, 0.0460885167f, false,
                                          &to3fui, 0.918295920f, false);
  ClassificationThresholdOptimizer<unsigned int, float, unsigned int> to2uif(true, 2, ef.egain);
  to2uif.prepare_for_optimizing(0, 1);
  ClassificationThresholdOptimizer<unsigned int, float, unsigned int> to3uif(true, 3, ef.egain);
  to3uif.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to2uif, 0.0460885167f, false,
    &to3uif, 0.918295920f, false);
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> to2uiui(true, 2, ef.egain);
  to2uiui.prepare_for_optimizing(0, 1);
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> to3uiui(true, 3, ef.egain);
  to3uiui.prepare_for_optimizing(0, 1);
  test_ClassThresholdOptFindsPerfectSplit(&to2uiui, 0.0460885167f, false,
    &to3uiui, 0.918295920f, false);

  auto indpent = std::shared_ptr<fertilized::IEntropyFunction<float>>(
    new InducedEntropy<float>(1.50001f - 0.25f));
  VarianceClassificationThresholdOptimizer<float, float, unsigned int> vct2(
    300, 2, 2, 1.f, 1);
  vct2.prepare_for_optimizing(0, 1);
  VarianceClassificationThresholdOptimizer<float, float, unsigned int> vct3(
    300, 2, 2, indpent, 1.f, 1);
  vct3.prepare_for_optimizing(0, 1);
  ClassificationDataProviderFixture<float> dp2(300, 10, 3,
    [](float * val_p, size_t i){}, // Irrelevant for this test.
    [](unsigned int *annot_p, size_t i){
      *annot_p = static_cast<unsigned int>(i % 2);
      annot_p[1] = static_cast<unsigned int>(i);
      annot_p[2] = static_cast<unsigned int>(299-i);
    },
    [](float *w_p, size_t i){ *w_p = 1.f; },
    true,
    3
  );
  bool valid;
  std::vector<float> feats(300);
  for (size_t i = 0; i < 300; ++i)
    feats[i] = static_cast<float>(i);
  auto res = vct2.optimize(0, 0, 1, 300, dp2.input_data.get(),
                                     10, dp2.annot_data.get(),
                                      3, dp2.weights.get(), &feats[0], &valid);
  BOOST_CHECK_EQUAL(std::get<2>(res), 150);
  BOOST_CHECK_EQUAL(std::get<3>(res), 150);
  BOOST_CHECK_EQUAL(std::get<4>(res), 11250.f);
  res = vct3.optimize(0, 0, 1, 300, dp2.input_data.get(),
                                10, dp2.annot_data.get(),
                                 3, dp2.weights.get(), &feats[0], &valid);
  BOOST_CHECK_EQUAL(std::get<2>(res), 150);
  BOOST_CHECK_EQUAL(std::get<3>(res), 150);

  auto to2fuip = std::make_shared<ClassificationThresholdOptimizer<int, float, unsigned int>>(
    true, 2, ef.egain, 1E-7f, 3);
  auto vct2p = std::make_shared<VarianceClassificationThresholdOptimizer<int, float, unsigned int>>(
    300, 2, 2);
  AlternatingThresholdOptimizer<int, float, unsigned int> atp2(to2fuip, vct2p);
};

//---------------------------------------------------------------------------//
// Serialization.
#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Serialization_TwoSideClassificationThresholdOptimizer) {
  auto ef = EntropyGainFixture<float>();
  auto to22 = std::make_shared<TwoSideClassificationThresholdOptimizer<float, float, unsigned int>>(
                      true, 2, ef.egain);
  auto to32 = std::make_shared<TwoSideClassificationThresholdOptimizer<float, float, unsigned int>>(
                      true, 3, ef.egain);
  auto restored_to = serialize_deserialize(to22);
  auto restored_to3 = serialize_deserialize(to32);
  test_ClassThresholdOptFindsPerfectSplit(to22.get(), 0.254974544f, true,
                                          to32.get(), 0.918295920f, true);
};
BOOST_AUTO_TEST_CASE(Serialization_ClassificationThresholdOptimizer) {
  auto ef = EntropyGainFixture<float>();
  auto to2 = std::make_shared<ClassificationThresholdOptimizer<float, float, unsigned int>>(
                      true, 2, ef.egain);
  auto to3 = std::make_shared<ClassificationThresholdOptimizer<float, float, unsigned int>>(
                      true, 3, ef.egain);
  auto restored_to2 = serialize_deserialize(to2);
  auto restored_to3 = serialize_deserialize(to3);
  test_ClassThresholdOptFindsPerfectSplit(to2.get(), 0.0460885167f, true,
                                          to3.get(), 0.918295920f, true);
};
BOOST_AUTO_TEST_CASE(Serialization_RandomizedClassificationThresholdOptimizer) {
  auto ef = EntropyGainFixture<float>();
  // Two classes.
  ClassificationDataProviderFixture<float> dp2(300, 10, 2,
    [](float * val_p, size_t i){}, // Irrelevant for this test.
    [](unsigned int *annot_p, size_t i){
      *annot_p = static_cast<unsigned int>(i < 100 || i >= 200 ? (i % 2) : 0);
    },
    [](float *w_p, size_t i){ *w_p = 1.f; }
  );
  bool valid;
  std::vector<float> feats(300);
  for (size_t i = 0; i < 300; ++i)
    feats[i] = static_cast<float>(i);

  auto rto2 = std::make_shared<RandomizedClassificationThresholdOptimizer<float, float, unsigned int>>(
                      10, 2, ef.egain);
  rto2 -> prepare_for_optimizing(0, 1);
  rto2 -> optimize(0, 0, 1, 10, dp2.input_data.get(),
                            10, dp2.annot_data.get(),
                             1, dp2.weights.get(), &feats[0], &valid);
  auto restored_rto2 = serialize_deserialize(rto2);
  rto2 -> prepare_for_optimizing(0, 1);
  auto res = rto2 -> optimize(0, 0, 1, 10, dp2.input_data.get(),
                                       10, dp2.annot_data.get(),
                                        1, dp2.weights.get(), &feats[0], &valid);
  BOOST_REQUIRE(valid);
  restored_rto2 -> prepare_for_optimizing(0, 1);
  auto res_restored = restored_rto2 -> optimize(0, 0, 1, 10, dp2.input_data.get(),
                                                         10, dp2.annot_data.get(),
                                                          1, dp2.weights.get(),
                                                &feats[0], &valid);
  BOOST_REQUIRE(valid);
  BOOST_CHECK_EQUAL(std::get<0>(res).first, std::get<0>(res_restored).first);
  BOOST_CHECK_EQUAL(std::get<0>(res).second, std::get<0>(res_restored).second);
  BOOST_CHECK(std::get<1>(res) == std::get<1>(res_restored));
  BOOST_CHECK_EQUAL(std::get<2>(res), std::get<2>(res_restored));
  BOOST_CHECK_EQUAL(std::get<3>(res), std::get<3>(res_restored));
  BOOST_CHECK_EQUAL(std::get<4>(res), std::get<4>(res_restored));
};
#endif

BOOST_AUTO_TEST_SUITE_END();

//---------------------------------------------------------------------------//
// Speed.

BOOST_AUTO_TEST_SUITE(Speeds_ThresholdOptimizers);

template <typename T, typename F>
void test_ClassifThresholdOptimizerSpeed(IThresholdOptimizer<T, F, unsigned int> *func,
                                   const float &expected,
                                   const std::string &name) {
  // Define the functor to measure.
  struct classif_opt_timer : public Utility::ITimefunc {
    classif_opt_timer(const std::vector<F> &feats,
                      ClassificationDataProviderFixture<T> *pfix,
                      const std::shared_ptr<const std::vector<size_t>> &elem_ids,
                      IThresholdOptimizer<T, F, unsigned int> *to)
    : features(feats), feat_ids(elem_ids), pfix(pfix), to(to) {
      to -> prepare_for_optimizing(0, 1);
    }
    int operator()() { return static_cast<int>(std::get<2>(to -> optimize(
      0, 0, 1, 10, pfix -> input_data.get(),
               10, pfix -> annot_data.get(),
                1, pfix -> weights.get(), &features[0], &valid))); }
   private:
    std::vector<F> features;
    std::shared_ptr<const std::vector<size_t>> feat_ids;
    ClassificationDataProviderFixture<T> *pfix;
    IThresholdOptimizer<T, F, unsigned int> *to;
    bool valid;
  };
  std::mt19937 re(1);
  std::uniform_int_distribution<unsigned int> dis(0, 1);
  ClassificationDataProviderFixture<T> dp2(300, 10, 2,
    [](T * val_p, size_t i){}, // Irrelevant for this test.
    [&re, &dis](unsigned int *annot_p, size_t i){
      *annot_p = dis(re);
  });
  auto elem_ids = dp2.dprov -> get_initial_sample_list();
  std::vector<F> feats(300);
  for (size_t i =0; i < 300; ++i)
    feats[i] = static_cast<F>(i);
  classif_opt_timer timer(feats, &dp2, elem_ids, func);
  // Get the measurement in ms.
  float ent_time = Utility::timeit<std::chrono::nanoseconds>(
    &timer, false, 3, 2);
  BOOST_TEST_MESSAGE(name + ": " + std::to_string(ent_time));
  BOOST_CHECK_LE(ent_time, expected * 1.1f);
}

BOOST_AUTO_TEST_CASE(Speeds_SingleThreshOptSpeedIsNormal) {
  auto ef = EntropyGainFixture<float>();
  ClassificationThresholdOptimizer<float, float, unsigned int> to(true, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&to, 14000.f,
"ClassificationThresholdOptimizer<float,float>(Approx,EntropyGain(SE))");
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> toui(true, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&toui, 14000.f,
  "ClassificationThresholdOptimizer<uint,uint>(Approx,EntropyGain(SE))");
  //
  ClassificationThresholdOptimizer<float, float, unsigned int> topent(true, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&topent, 10000.f,
"ClassificationThresholdOptimizer<float,float>(Approx,EntropyGain(IPE(2)))");
  //
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> topentui(true, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&topentui, 10000.f,
"ClassificationThresholdOptimizer<uint,uint>(Approx,EntropyGain(IPE(2)))");
  //
  ClassificationThresholdOptimizer<float, float, unsigned int> tona(false, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&tona, 23000.f,
"ClassificationThresholdOptimizer<float,float>(NoApprox,EntropyGain(SE))");
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> touina(false, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&touina, 23000.f,
"ClassificationThresholdOptimizer<uint,uint>(NoApprox,EntropyGain(SE))");
  ClassificationThresholdOptimizer<float, float, unsigned int> topentna(false, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&topentna, 13000.f,
"ClassificationThresholdOptimizer<float,float>(NoApprox,EntropyGain(IPE(2)))");
  ClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> topentuina(false, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&topentuina, 13000.f,
"ClassificationThresholdOptimizer<uint,uint>(NoApprox,EntropyGain(IPE(2)))");
};

BOOST_AUTO_TEST_CASE(Speeds_TwoSideThreshOptSpeedIsNormal) {
  auto ef = EntropyGainFixture<float>();
  TwoSideClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> toui2(true, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&toui2, 62000.f,
  "TwoSideClassificationThresholdOptimizer<uint,uint>(Approx,EntropyGain(SE))");
  TwoSideClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> topentui2(true, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&topentui2, 55000.f,
  "TwoSideClassificationThresholdOptimizer<uint,uint>(Approx,EntropyGain(IPE(2)))");
};

BOOST_AUTO_TEST_CASE(Speeds_RandomizedThreshOptSpeedIsNormal) {
  auto ef = EntropyGainFixture<float>();
  RandomizedClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> rtoui2(10, 2, ef.egain);
  test_ClassifThresholdOptimizerSpeed(&rtoui2, 7000.f,
  "RandomizedClassificationThresholdOptimizer<uint,uint>(EntropyGain(SE))");
  RandomizedClassificationThresholdOptimizer<unsigned int, unsigned int, unsigned int> rtopentui2(10, 2, ef.pent2gain);
  test_ClassifThresholdOptimizerSpeed(&rtopentui2, 7000.f,
  "RandomizedClassificationThresholdOptimizer<uint,uint>(EntropyGain(IPE(2)))");
};
BOOST_AUTO_TEST_SUITE_END();
