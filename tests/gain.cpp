/* Author: Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

#include <chrono>
#include <functional>
#include <string>
#include <vector>

#include <fertilized/impurities/shannonentropy.h>
#include <fertilized/impurities/inducedentropy.h>
#include <fertilized/gains/igaincalculator.h>
#include <fertilized/gains/entropygain.h>

#include "./setup.h"
#include "./timeit.h"

// Utility objects.
using fertilized::ShannonEntropy;
using fertilized::InducedEntropy;

// Test objects.
using fertilized::IGainCalculator;
using fertilized::EntropyGain;

// TODO(Christoph): With the change to STL containers instead of raw memory
// access for gain and entropy calculation, the functions became about
// factor two slower. Where did that time go exactly? Could it be the other
// summation functions? The range calculation of the containers? Might be
// a place to start looking for performance improvement later.


BOOST_AUTO_TEST_SUITE(Correctness_Gains);

//---------------------------------------------------------------------------//
// Gains of zero values is zero.

template <typename T>
void test_IGainCalcOfZeroesIsZero(IGainCalculator<T> *calc) {
  DualMemberNumberFixture<T> dta;
  for (size_t i = 0; i < 10; ++i) {
    std::vector<T> hist_l(i, static_cast<T>(0));
    std::vector<T> hist_r(i, static_cast<T>(0));
    BOOST_CHECK_EQUAL((*calc)(hist_l, hist_r), 0.f);
    BOOST_CHECK_EQUAL((*calc)(0.f, hist_l, hist_r), 0.f);
    BOOST_CHECK_EQUAL((*calc).approx(hist_l, hist_r), 0.f);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_EntropyGainOfEmptyIsZero) {
  EntropyGainFixture<float> obj;
  test_IGainCalcOfZeroesIsZero<float>(obj.egain.get());
  EntropyGainFixture<unsigned int> obj_ui;
  test_IGainCalcOfZeroesIsZero<unsigned int>(obj_ui.egain.get());
};

//---------------------------------------------------------------------------//
// Extreme cases (Histogram with 0 elements, only 1 element).

template <typename T>
void test_IGainCalcExtremeCases(IGainCalculator<T> *calc) {
  DualMemberNumberFixture<T> dta;
  std::vector<T> hist_l(0);
  std::vector<T> hist_r(0);
  BOOST_CHECK_EQUAL((*calc)(hist_l, hist_r), 0.f);
  BOOST_CHECK_EQUAL((*calc)(0.f, hist_l, hist_r), 0.f);
  BOOST_CHECK_EQUAL((*calc).approx(hist_l, hist_r), 0.f);
  hist_l = std::vector<T>(1);
  hist_r = std::vector<T>(1);
  BOOST_CHECK_EQUAL((*calc)(hist_l, hist_r), 0.f);
  BOOST_CHECK_EQUAL((*calc)(0.f, hist_l, hist_r), 0.f);
  BOOST_CHECK_EQUAL((*calc).approx(hist_l, hist_r), 0.f);
};

BOOST_AUTO_TEST_CASE(Correctness_EntropyGainExtremeCases) {
  EntropyGainFixture<float> obj;
  test_IGainCalcExtremeCases<float>(obj.egain.get());
  EntropyGainFixture<unsigned int> obj_ui;
  test_IGainCalcExtremeCases<unsigned int>(obj_ui.egain.get());
};

//---------------------------------------------------------------------------//
// Minimum value reached for equal sets.

template <typename T>
void test_IGainCalcMin(IGainCalculator<T> *calc,
                       const std::function<float (unsigned int)> &objective,
                       const std::function<float (unsigned int)> &approx_obj) {
  for (unsigned int hist_size = 2; hist_size < 10; ++hist_size) {
    for (unsigned int hist_value = 1; hist_value < 5; ++hist_value) {
      float objective_value = objective(hist_size);
      std::vector<T> hist_l(hist_size, static_cast<T>(hist_value));
      std::vector<T> hist_r(hist_size, static_cast<T>(hist_value));
      CHECK_CLOSE_((*calc)(logf(static_cast<float>(hist_size)) / logf(2.f),
                                 hist_l, hist_r),
                   objective_value);
      CHECK_CLOSE_((*calc)(hist_l, hist_r),
                   objective_value);
      CHECK_CLOSE_((*calc).approx(hist_l, hist_r),
                   approx_obj(hist_size));
    }
  }
};

BOOST_AUTO_TEST_CASE(Correctness_EntropyGainCalcMin) {
  EntropyGainFixture<float> obj_f;
  test_IGainCalcMin<float>(obj_f.egain.get(),
    [](unsigned int hist_size){ return 0.f; },
    [](unsigned int hist_size){ return -logf(static_cast<float>(hist_size)) /
                                                    logf(2.f); });
  EntropyGainFixture<unsigned int> obj_ui;
  test_IGainCalcMin<unsigned int>(obj_ui.egain.get(),
    [](unsigned int hist_size){ return 0.f; },
    [](unsigned int hist_size){ return -logf(static_cast<float>(hist_size)) /
                                                    logf(2.f); });
};

//---------------------------------------------------------------------------//
// Maximum value reached for a perfect split.

template <typename T>
void test_IGainCalcMax(IGainCalculator<T> *calc,
                       const std::function<float (unsigned int)> &objective,
                       const std::function<float (unsigned int)> &approx_obj) {
  for (unsigned int hist_size = 2; hist_size < 11; ++++hist_size) {
    for (unsigned int hist_value = 1; hist_value < 5; ++hist_value) {
      float objective_value = objective(hist_size);
      std::vector<T> hist_l(hist_size, static_cast<T>(hist_value));
      std::vector<T> hist_r(hist_size, static_cast<T>(hist_value));
      for (size_t i = 0; i < hist_size; ++i) {
        if (i < hist_size / 2) hist_l[i] = 0;
        else                   hist_r[i] = 0;
      }
      CHECK_CLOSE_((*calc)(logf(static_cast<float>(hist_size)) / logf(2.f),
                                 hist_l, hist_r),
                   objective_value);
      CHECK_CLOSE_((*calc)(hist_l, hist_r),
                   objective_value);
      CHECK_CLOSE_((*calc).approx(hist_l, hist_r),
                   approx_obj(hist_size));
    }
  }
};

BOOST_AUTO_TEST_CASE(Correctness_EntropyGainCalcMax) {
  EntropyGainFixture<float> obj_f;
  test_IGainCalcMax<float>(obj_f.egain.get(),
    [](unsigned int hist_size){ return 1.f; },
    [](unsigned int hist_size){ return -logf(static_cast<float>(hist_size/2)) /
                                                    logf(2.f); });
  EntropyGainFixture<unsigned int> obj_ui;
  test_IGainCalcMax<unsigned int>(obj_ui.egain.get(),
    [](unsigned int hist_size){ return 1.f; },
    [](unsigned int hist_size){ return -logf(static_cast<float>(hist_size/2)) /
                                                    logf(2.f); });
};


//---------------------------------------------------------------------------//
// Randomly picked point correct.

template <typename T>
void test_EGainRandomPoint(IGainCalculator<T> *calc, const float &curr_e,
                           const float &point_val, const float &approx_val) {
  DualMemberNumberFixture<T> dta;
  auto hist_r = std::vector<T>(10, static_cast<T>(1));
  CHECK_CLOSE_((*calc)(dta.hist_l, hist_r), point_val);
  CHECK_CLOSE_((*calc)(curr_e, dta.hist_l, hist_r), point_val);
  CHECK_CLOSE_((*calc).approx(dta.hist_l, hist_r), approx_val);
}

BOOST_AUTO_TEST_CASE(Correctness_EntropyGainShannonRandomPoint) {
  EntropyGainFixture<float> obj_f;
  // Verified by MATLAB
  float result = 0.144319802425370f;
  float curr = 3.149255397168500f;
  float approx = -3.004935594743131f;
  test_EGainRandomPoint<float>(obj_f.egain.get(), curr, result, approx);
  auto egain_ui = std::shared_ptr<IGainCalculator<unsigned int>>(
                                new EntropyGain<unsigned int>(
                                std::make_shared<ShannonEntropy<unsigned int>>()));
  EntropyGainFixture<unsigned int> obj_ui;
  test_EGainRandomPoint<unsigned int>(obj_ui.egain.get(), curr, result, approx);
};

//---------------------------------------------------------------------------//
// Serialization.
#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Serialization_EntropyGain) {
  auto entropy_gain_f = std::shared_ptr<IGainCalculator<float>>(
                                new EntropyGain<float>(
                                std::make_shared<ShannonEntropy<float>>()));
  auto restored_f = serialize_deserialize(entropy_gain_f);
  // Verified by MATLAB
  float result = 0.144319802425370f;
  float curr = 3.149255397168500f;
  float approx = -3.004935594743131f;
  test_EGainRandomPoint<float>(restored_f.get(), curr, result, approx);
  auto egain_ui = std::shared_ptr<IGainCalculator<unsigned int>>(
                                new EntropyGain<unsigned int>(
                                std::make_shared<ShannonEntropy<unsigned int>>()));
  auto restored_ui = serialize_deserialize(egain_ui);
  test_EGainRandomPoint<unsigned int>(restored_ui.get(), curr, result, approx);
};
#endif
BOOST_AUTO_TEST_SUITE_END();

//---------------------------------------------------------------------------//
// Speed.

BOOST_AUTO_TEST_SUITE(Speed_Gain);

template <typename T>
void test_IGainCalcSpeed(std::shared_ptr<IGainCalculator<T>> *calc,
                         const float &expected,
                         const std::string &name) {
  DualMemberNumberFixture<T> dta;
  // Define the functor to measure.
  struct gain_timer : public Utility::ITimefunc {
    gain_timer(const std::vector<T> &hist_l, const std::vector<T> &hist_r,
               std::shared_ptr<IGainCalculator<T>> *ef)
    : hist_l(hist_l), hist_r(hist_r), ef(*ef) {}
    int operator()() { return static_cast<int>((*ef).approx(hist_l, hist_r)); }
   private:
    std::vector<T> hist_l;
    std::vector<T> hist_r;
    std::shared_ptr<IGainCalculator<T>> ef;
  };
  // Get the measurement in ms.
  auto timer = gain_timer(dta.hist_l, dta.hist_r, calc);
  float ent_time = Utility::timeit<std::chrono::nanoseconds>(
    &timer, false, 3, 2);
  BOOST_TEST_MESSAGE(name + ": " + std::to_string(ent_time));
  BOOST_CHECK_LE(ent_time, expected * 1.1f);
}

BOOST_AUTO_TEST_CASE(Speeds_EntropyGainSpeedIsNormal) {
  EntropyGainFixture<float> efs;
  test_IGainCalcSpeed<float>(&efs.egain, 210.f,
                             "EntropyGain<float>(ShannonEntropy)");

  EntropyGainFixture<unsigned int> euis;
  test_IGainCalcSpeed<unsigned int>(&euis.egain, 220.f,
      "EntropyGain<unsigned int>(ShannonEntropy)");

  auto egfip =     std::shared_ptr<IGainCalculator<float>>(
        new EntropyGain<float>(std::make_shared<InducedEntropy<float>>(2.f)));
  test_IGainCalcSpeed<float>(&egfip, 100.f,
    "EntropyGain<float>(InducedPEntropy(2))");

  auto eguiip =     std::shared_ptr<IGainCalculator<unsigned int>>(
        new EntropyGain<unsigned int>(
          std::make_shared<InducedEntropy<unsigned int>>(2.f)));
  test_IGainCalcSpeed<unsigned int>(&eguiip, 105.f,
    "EntropyGain<unsigned int>(InducedPEntropy(2))");
};
BOOST_AUTO_TEST_SUITE_END();