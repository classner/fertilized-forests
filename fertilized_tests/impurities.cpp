/* Author: Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

#include <chrono>
#include <functional>
#include <string>
#include <vector>

#include <Eigen/Dense>

#include <fertilized/impurities/ientropyfunction.h>
#include <fertilized/impurities/classificationerror.h>
#include <fertilized/impurities/inducedentropy.h>
#include <fertilized/impurities/shannonentropy.h>
#include <fertilized/impurities/tsallisentropy.h>
#include <fertilized/impurities/renyientropy.h>

#include "./setup.h"
#include "./timeit.h"

// Test objects.
using fertilized::fpowi;
using fertilized::ipow;

using fertilized::IEntropyFunction;
using fertilized::ClassificationError;
using fertilized::InducedEntropy;
using fertilized::ShannonEntropy;
using fertilized::TsallisEntropy;
using fertilized::RenyiEntropy;

BOOST_AUTO_TEST_SUITE(Correctness_Impurities);

BOOST_AUTO_TEST_CASE(Correctness_fpowiTest) {
  for (float i = 0.f; i < 8.f; i++) {
    for (unsigned int j = 0; j < 10; j++)
      BOOST_CHECK_EQUAL(fpowi(i, j),
                        static_cast<int>(pow(static_cast<double>(i),
                                             static_cast<double>(j))));
  }
};

BOOST_AUTO_TEST_CASE(Correctness_ipowTest) {
  for (int i = 0; i < 8; i++) {
    for (unsigned int j = 0; j < 10; j++)
      BOOST_CHECK_EQUAL(ipow(i, j),
                        static_cast<int>(pow(static_cast<double>(i),
                                             static_cast<double>(j))));
  }
};

//---------------------------------------------------------------------------//
// Entropy of zero values is zero.
template <typename T>
void test_IEntropyOfZeroesIsZero(IEntropyFunction<T> *func) {
  MemberNumberFixture<T> dta;
  BOOST_CHECK_EQUAL((*func)(std::vector<T>()), static_cast<T>(0));
  BOOST_CHECK_EQUAL((*func)(std::vector<T>(), static_cast<T>(0)), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_1), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_1, 0.f), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_2), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_2, 0.f), 0.f);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonEntropyOfZeroesIsZero) {
  ShannonEntropy<float> shannon_entropy;
  test_IEntropyOfZeroesIsZero<float>(&shannon_entropy);
  ShannonEntropy<unsigned int> shannon_entropy_uint;
  test_IEntropyOfZeroesIsZero<unsigned int>((IEntropyFunction<unsigned int>*)&shannon_entropy_uint);
};

BOOST_AUTO_TEST_CASE(Correctness_ClassificationErrorOfZeroesIsZero) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  test_IEntropyOfZeroesIsZero<float>(classification_error.get());
  auto classification_error_uint = std::make_shared<ClassificationError<unsigned int>>();
  test_IEntropyOfZeroesIsZero<unsigned int>(classification_error_uint.get());
};

BOOST_AUTO_TEST_CASE(Correctness_pEntropyOfZeroesIsZero) {
  for (unsigned int p = 1; p < 5; ++p) {
    InducedEntropy<float> induced_p_entropy_f(static_cast<float>(p));
    test_IEntropyOfZeroesIsZero<float>(&induced_p_entropy_f);
    InducedEntropy<unsigned int> induced_p_entropy_ui(static_cast<float>(p));
    test_IEntropyOfZeroesIsZero<unsigned int>(&induced_p_entropy_ui);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisEntropyOfZeroesIsZero) {
  for (float q = 1.f; q < 5.f; ++q) {
    auto tsallis = std::make_shared<TsallisEntropy<float>>(q);
    test_IEntropyOfZeroesIsZero<float>(tsallis.get());
    auto tsallis_uint = std::make_shared<TsallisEntropy<unsigned int>>(q);
    test_IEntropyOfZeroesIsZero<unsigned int>(tsallis_uint.get());
  }
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiEntropyOfZeroesIsZero) {
  for (float q = 1.f; q < 5.f; ++q) {
    auto renyi = std::make_shared<RenyiEntropy<float>>(q);
    test_IEntropyOfZeroesIsZero<float>(renyi.get());
    auto renyi_uint = std::make_shared<RenyiEntropy<unsigned int>>(q);
    test_IEntropyOfZeroesIsZero<unsigned int>(renyi_uint.get());
  }
};

BOOST_AUTO_TEST_CASE(Correctness_ClassDiffNormOfZerosIsMINF) {
  auto class_err = std::make_shared<ClassificationError<float>>();
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 0.f, 0.f, 0.f, 0.f;
  BOOST_CHECK_EQUAL(class_err -> differential_normal(mat),
                    -std::numeric_limits<float>::infinity());
}

BOOST_AUTO_TEST_CASE(Correctness_ShannonDiffNormOfZerosIsMINF) {
  ShannonEntropy<float> shannon_entropy;
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 0.f, 0.f, 0.f, 0.f;
  BOOST_CHECK_EQUAL(shannon_entropy.differential_normal(mat),
                    -std::numeric_limits<float>::infinity());
}

BOOST_AUTO_TEST_CASE(Correctness_PEntDiffNormOfZerosIsMINF) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 0.f, 0.f, 0.f, 0.f;
  for (unsigned int p = 2; p < 5; ++p) {
    InducedEntropy<float> induced_p_entropy_f(1.50001f - 1.f/static_cast<float>(p));
    BOOST_CHECK_EQUAL(induced_p_entropy_f.differential_normal(mat),
                      -std::numeric_limits<float>::infinity());
  }
}

BOOST_AUTO_TEST_CASE(Correctness_TsallisDiffNormOfZerosIsMINF) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 0.f, 0.f, 0.f, 0.f;
  for (unsigned int p = 2; p < 5; ++p) {
    TsallisEntropy<float> tsallis_entropy_f(static_cast<float>(p));
    BOOST_CHECK_EQUAL(tsallis_entropy_f.differential_normal(mat),
                      -std::numeric_limits<float>::infinity());
  }
}

BOOST_AUTO_TEST_CASE(Correctness_RenyiDiffNormOfZerosIsMINF) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 0.f, 0.f, 0.f, 0.f;
  for (unsigned int p = 2; p < 5; ++p) {
    RenyiEntropy<float> renyi_entropy_f(static_cast<float>(p));
    BOOST_CHECK_EQUAL(renyi_entropy_f.differential_normal(mat),
                      -std::numeric_limits<float>::infinity());
  }
}

//---------------------------------------------------------------------------//
// Extreme cases (Histogram with 0 elements, only 1 element).

template <typename T>
void test_IEntropyExtremeCases(IEntropyFunction<T> *func) {
  MemberNumberFixture<T> dta;
  // Check for zero classes.
  BOOST_CHECK_EQUAL((*func)(std::vector<T>()), 0.f);
  BOOST_CHECK_EQUAL((*func)(std::vector<T>(), 0.f), 0.f);
  // Check for only one class.
  BOOST_CHECK_EQUAL((*func)(dta.part_1), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_1, 0.f), 0.f);
  dta.part_1[0] = static_cast<T>(1);
  BOOST_CHECK_EQUAL((*func)(dta.part_1), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_1, 1.f), 0.f);
  dta.part_1[0] = static_cast<T>(2);
  BOOST_CHECK_EQUAL((*func)(dta.part_1), 0.f);
  BOOST_CHECK_EQUAL((*func)(dta.part_1, 2.f), 0.f);
}

BOOST_AUTO_TEST_CASE(Correctness_ClassErrExtremeCases) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  test_IEntropyExtremeCases<float>(classification_error.get());
  auto classification_error_uint = std::make_shared<ClassificationError<unsigned int>>();
  test_IEntropyExtremeCases<unsigned int>(classification_error_uint.get());
};

BOOST_AUTO_TEST_CASE(Correctness_ClassErrDiffNormExtremeCases) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  auto mat = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>();
  mat << 4.f;
  // Verified with numpy.
  CHECK_CLOSE_(classification_error -> differential_normal(mat), 0.80052885979928368f);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonEntropyExtremeCases) {
  ShannonEntropy<float> shannon_entropy_f;
  test_IEntropyExtremeCases<float>((IEntropyFunction<float>*)&shannon_entropy_f);
  ShannonEntropy<unsigned int> shannon_entropy_ui;
  test_IEntropyExtremeCases<unsigned int>((IEntropyFunction<unsigned int>*)&shannon_entropy_ui);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonEntropyDiffNormExtremeCases) {
  ShannonEntropy<float> shannon_entropy_f;
  auto mat = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>();
  mat << 4.f;
  CHECK_CLOSE_(shannon_entropy_f.differential_normal(mat), 2.1120857137646181f);
};

BOOST_AUTO_TEST_CASE(Correctness_pEntropyExtremeCases) {
  // Check for zero classes.
  for (unsigned int p = 1; p < 5; p++) {
    InducedEntropy<float> induced_p_entropy_f(static_cast<float>(p));
    test_IEntropyExtremeCases<float>(&induced_p_entropy_f);
    InducedEntropy<unsigned int> induced_p_entropy_ui(static_cast<float>(p));
    test_IEntropyExtremeCases<unsigned int>(&induced_p_entropy_ui);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_InducedEntropyDiffNormExtremeCases) {
  InducedEntropy<float> induced_p(2.f);
  auto mat = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>();
  mat << 4.f;
  CHECK_CLOSE_(induced_p.differential_normal(mat), 0.85895260411306096f);
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisEntropyExtremeCases) {
  // Check for zero classes.
  for (unsigned int p = 1; p < 5; p++) {
    TsallisEntropy<float> entropy_f(static_cast<float>(p));
    test_IEntropyExtremeCases<float>(&entropy_f);
    TsallisEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyExtremeCases<unsigned int>(&entropy_ui);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisEntropyDiffNormExtremeCases) {
  TsallisEntropy<float> tsallis(2.f);
  auto mat = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>();
  mat << 4.f;
  CHECK_CLOSE_(tsallis.differential_normal(mat), 0.85895260411306096f);
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiEntropyExtremeCases) {
  // Check for zero classes.
  for (unsigned int p = 1; p < 5; p++) {
    RenyiEntropy<float> entropy_f(static_cast<float>(p));
    test_IEntropyExtremeCases<float>(&entropy_f);
    RenyiEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyExtremeCases<unsigned int>(&entropy_ui);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiEntropyDiffNormExtremeCases) {
  RenyiEntropy<float> renyi(2.f);
  auto mat = Eigen::Matrix<float, 1, 1, Eigen::RowMajor>();
  mat << 4.f;
  // Verified by numpy.
  CHECK_CLOSE_(renyi.differential_normal(mat), 1.958659304044591f);
  RenyiEntropy<float> renyiinf(std::numeric_limits<float>::infinity());
  // Verified by numpy.
  CHECK_CLOSE_(renyiinf.differential_normal(mat), 1.6120857137646181f);
};

//---------------------------------------------------------------------------//
// Maximum value reached for equal class distributions.

template <typename T>
void test_IEntropyReachMax(IEntropyFunction<T> *func,
                           std::function<float (unsigned int)> *obj_val_calc) {
  std::vector<T> memberNumbers(10, static_cast<T>(1));
  for (unsigned int members = 2; members < 10; ++members) {
    float objective_value = (*obj_val_calc)(members);
    CHECK_CLOSE_(
      (*func)(std::vector<T>(memberNumbers.begin(),
                             memberNumbers.begin() + members)),
              objective_value);
    CHECK_CLOSE_(
      (*func)(std::vector<T>(memberNumbers.begin(),
                             memberNumbers.begin() + members),
              static_cast<float>(members)),
      objective_value);
  }
  memberNumbers = std::vector<T>(10, static_cast<T>(2));
  for (unsigned int members = 2; members < 10; ++members) {
    float objective_value = (*obj_val_calc)(members);
    CHECK_CLOSE_(
      (*func)(std::vector<T>(memberNumbers.begin(),
                             memberNumbers.begin() + members)),
      objective_value);
    CHECK_CLOSE_(
      (*func)(std::vector<T>(memberNumbers.begin(),
                             memberNumbers.begin() + members),
              static_cast<float>(2 * members)),
      objective_value);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_ClassErrOfEqualsIsMax) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  std::function<float (unsigned int)> obj_val = [](unsigned int n_classes) {
    return 1.f - 1.f / static_cast<float>(n_classes);
  };
  test_IEntropyReachMax<float>(classification_error.get(), &obj_val);
  auto class_err_ui = std::make_shared<ClassificationError<unsigned int>>();
  test_IEntropyReachMax<unsigned int>(class_err_ui.get(), &obj_val);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonEntropyOfEqualsIsMax) {
  ShannonEntropy<float> shannon_entropy_f;
  // The maximum of the Shannon entropy is at log2(n_classes).
  std::function<float (unsigned int)> obj_val = [](unsigned int n_classes) {
    return logf(static_cast<float>(n_classes)) / logf(2.f);
  };
  test_IEntropyReachMax<float>((IEntropyFunction<float>*)&shannon_entropy_f, &obj_val);
  ShannonEntropy<unsigned int> shannon_entropy_ui;
  test_IEntropyReachMax<unsigned int>((IEntropyFunction<unsigned int>*)&shannon_entropy_ui, &obj_val);
};

BOOST_AUTO_TEST_CASE(Correctness_pEntropyOfEqualsIsMax) {
  for (unsigned int p = 2; p < 5; ++p) {
    InducedEntropy<float> induced_p_entropy_f(static_cast<float>(p));
    // The maximum of the p-entropy is at (1-1/|C|)^p+(|C|-1)*(1/|C|)^p
    std::function<float (unsigned int)> obj_val = [p](unsigned int n_classes) {
      float n_classes_f = static_cast<float>(n_classes);
      return fpowi(1.f-1.f/n_classes_f, p) + (n_classes_f-1.f)*fpowi(1.f/n_classes_f, p);
    };
    test_IEntropyReachMax<float>(&induced_p_entropy_f, &obj_val);
    InducedEntropy<unsigned int> induced_p_entropy_ui(static_cast<float>(p));
    test_IEntropyReachMax<unsigned int>(&induced_p_entropy_ui, &obj_val);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisEntropyOfEqualsIsMax) {
  for (unsigned int p = 2; p < 5; ++p) {
    TsallisEntropy<float> entropy_f(static_cast<float>(p));
    std::function<float (unsigned int)> obj_val = [p](unsigned int n_classes) {
      float n_classes_f = static_cast<float>(n_classes);
      return (1.f - n_classes_f * fpowi(1.f/n_classes_f, p)) / (static_cast<float>(p)-1.f);
    };
    test_IEntropyReachMax<float>(&entropy_f, &obj_val);
    TsallisEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyReachMax<unsigned int>(&entropy_ui, &obj_val);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiEntropyOfEqualsIsMax) {
  for (unsigned int p = 2; p < 5; ++p) {
    RenyiEntropy<float> entropy_f(static_cast<float>(p));
    std::function<float (unsigned int)> obj_val = [p](unsigned int n_classes) {
      float n_classes_f = static_cast<float>(n_classes);
      return logf(n_classes_f * fpowi(1.f/n_classes_f, p)) / (1.f - static_cast<float>(p));
    };
    test_IEntropyReachMax<float>(&entropy_f, &obj_val);
    RenyiEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyReachMax<unsigned int>(&entropy_ui, &obj_val);
  }
};

//---------------------------------------------------------------------------//
// Randomly picked point correct.

template <typename T>
void test_IEntropyRandomPoint(IEntropyFunction<T> *func, float point_val) {
  MemberNumberFixture<T> dta;
  CHECK_CLOSE_((*func)(dta.memberNumbers), point_val);
  CHECK_CLOSE_(
    (*func)(dta.memberNumbers,
            static_cast<float>(
              std::accumulate(dta.memberNumbers.begin(),
                              dta.memberNumbers.end(), static_cast<T>(0)))),
    point_val);
}

BOOST_AUTO_TEST_CASE(Correctness_ClassErrRandomPoint) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  // Verified by numpy
  float result = 0.8f;
  test_IEntropyRandomPoint<float>(classification_error.get(), result);
  auto classification_error_ui = std::make_shared<ClassificationError<unsigned int>>();
  test_IEntropyRandomPoint<unsigned int>(classification_error_ui.get(), result);
};

BOOST_AUTO_TEST_CASE(Correctness_DiffClassErrRandomPoint) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  // Verified by numpy
  // cppcheck-suppress variableScope
  float result = 0.94373023024018088f;
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 2.f, 0.f, 0.f, 4.f;
  CHECK_CLOSE_(classification_error -> differential_normal(mat), result);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonEntropyRandomPoint) {
  ShannonEntropy<float> shannon_entropy_f;
  // Verified by MATLAB
  float result = 2.84643936f;
  test_IEntropyRandomPoint<float>((IEntropyFunction<float>*)&shannon_entropy_f, result);
  ShannonEntropy<unsigned int> shannon_entropy_ui;
  test_IEntropyRandomPoint<unsigned int>((IEntropyFunction<unsigned int>*)&shannon_entropy_ui, result);
};

BOOST_AUTO_TEST_CASE(Correctness_ShannonDiffNormEntropyRandomPoint) {
  ShannonEntropy<float> shannon_entropy_f;
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 2.f, 0.f, 0.f, 4.f;
  // Verified by numpy
  // cppcheck-suppress variableScope
  float result = 3.8775978372492634f;
  CHECK_CLOSE_(shannon_entropy_f.differential_normal(mat), result);
};

BOOST_AUTO_TEST_CASE(Correctness_pEntropyRandomPoint) {
  InducedEntropy<unsigned int> induced_p_entropy(1.f);
  // Verified by MATLAB
  float obj_vals[] = { 1.2f, 0.85f, 0.7335f };
  for (unsigned int p = 1; p < 4; ++p) {
    InducedEntropy<float> induced_p_entropy_f(static_cast<float>(p));
    test_IEntropyRandomPoint(&induced_p_entropy_f, obj_vals[p-1]);
    InducedEntropy<unsigned int> induced_p_entropy_ui(static_cast<float>(p));
    test_IEntropyRandomPoint(&induced_p_entropy_ui, obj_vals[p-1]);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_pEntropyDiffNormRandomPoint) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 2.f, 0.f, 0.f, 4.f;
  // Verified by numpy
  float obj_vals[] = {0.610378616659f, 0.71261078526189969f, 0.752807774668f };
  for (unsigned int p = 2; p < 5; ++p) {
    float fp = 1.50001f - 0.5f / static_cast<float>(p);
    InducedEntropy<float> induced_p_entropy_f(fp);
    CHECK_CLOSE_(induced_p_entropy_f.differential_normal(mat), obj_vals[p-2]);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisEntropyRandomPoint) {
  // Verified by MATLAB
  float obj_vals[] = { 2.846439f, 0.850000f, 0.487500f };
  for (unsigned int p = 1; p < 4; ++p) {
    TsallisEntropy<float> entropy_f(static_cast<float>(p));
    test_IEntropyRandomPoint(&entropy_f, obj_vals[p-1]);
    TsallisEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyRandomPoint(&entropy_ui, obj_vals[p-1]);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_TsallisDiffNormRandomPoint) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 2.f, 0.f, 0.f, 4.f;
  // Verified by numpy
  float obj_vals[] = {0.97186511512009044f, 0.49947228550186284f, 0.33331848614667875f };
  for (unsigned int p = 2; p < 5; ++p) {
    float fp = static_cast<float>(p);
    TsallisEntropy<float> entropy_f(fp);
    CHECK_CLOSE_(entropy_f.differential_normal(mat), obj_vals[p-2]);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiEntropyRandomPoint) {
  // Verified by MATLAB
  float obj_vals[] = { 2.846439f, 1.897120f, 1.844440f };
  for (unsigned int p = 1; p < 4; ++p) {
    RenyiEntropy<float> entropy_f(static_cast<float>(p));
    test_IEntropyRandomPoint(&entropy_f, obj_vals[p-1]);
    RenyiEntropy<unsigned int> entropy_ui(static_cast<float>(p));
    test_IEntropyRandomPoint(&entropy_ui, obj_vals[p-1]);
  }
};

BOOST_AUTO_TEST_CASE(Correctness_RenyiDiffNormRandomPoint) {
  auto mat = Eigen::Matrix<float, 2, 2, Eigen::RowMajor>();
  mat << 2.f, 0.f, 0.f, 4.f;
  // Verified by numpy
  float obj_vals[] = {3.5707450178092088f, 3.4269039815833184f, 3.33982253f };
  for (unsigned int p = 2; p < 5; ++p) {
    float fp = static_cast<float>(p);
    RenyiEntropy<float> entropy_f(fp);
    CHECK_CLOSE_(entropy_f.differential_normal(mat), obj_vals[p-2]);
  }
};

//---------------------------------------------------------------------------//
// Serialization.
#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Serialization_ClassificationError) {
  auto classification_error = std::make_shared<ClassificationError<float>>();
  auto restored_f = serialize_deserialize(classification_error);
  float result = 0.8f;
  test_IEntropyRandomPoint(restored_f.get(), result);
};

BOOST_AUTO_TEST_CASE(Serialization_ShannonEntropy) {
  auto shannon_entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                new ShannonEntropy<float>());
  auto restored_f = serialize_deserialize(shannon_entropy_f);
  float result = 2.84643936f;
  test_IEntropyRandomPoint(restored_f.get(), result);
  auto shannon_entropy_ui = std::shared_ptr<IEntropyFunction<unsigned int>>(
                                new ShannonEntropy<unsigned int>());
  auto restored_ui = serialize_deserialize(shannon_entropy_ui);
  test_IEntropyRandomPoint(restored_ui.get(), result);
};

BOOST_AUTO_TEST_CASE(Serialization_PEntropy) {
  auto p_entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                new InducedEntropy<float>(3.f));
  auto restored_f = serialize_deserialize(p_entropy_f);
  float result = 0.7335f;
  test_IEntropyRandomPoint(restored_f.get(), result);
  auto p_entropy_ui = std::shared_ptr<IEntropyFunction<unsigned int>>(
                                new InducedEntropy<unsigned int>(3.f));
  auto restored_ui = serialize_deserialize(p_entropy_ui);
  test_IEntropyRandomPoint(restored_ui.get(), result);
};

BOOST_AUTO_TEST_CASE(Serialization_TsallisEntropy) {
  auto entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                new TsallisEntropy<float>(2.f));
  auto restored_f = serialize_deserialize(entropy_f);
  float result = 0.850000f;
  test_IEntropyRandomPoint(restored_f.get(), result);
};

BOOST_AUTO_TEST_CASE(Serialization_RenyiEntropy) {
  auto entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                new RenyiEntropy<float>(2.f));
  auto restored_f = serialize_deserialize(entropy_f);
  float result = 1.897120f;
  test_IEntropyRandomPoint(restored_f.get(), result);
};
#endif
BOOST_AUTO_TEST_SUITE_END();
//---------------------------------------------------------------------------//
// Speed.

BOOST_AUTO_TEST_SUITE(Speeds_Impurities);

template <typename T>
void test_IEntropySpeed(std::shared_ptr<IEntropyFunction<T>> *func,
                        const float &expected,
                        const std::string &name) {
  MemberNumberFixture<T> dta;
  // Define the functor to measure.
  struct entropy_timer : public Utility::ITimefunc {
    entropy_timer(const std::vector<T> &numbers,
                  std::shared_ptr<IEntropyFunction<T>> *ef)
    : numbers(numbers), ef(*ef) {}
    int operator()() { return static_cast<int>((*ef)(numbers)); }
   private:
    std::vector<T> numbers;
    std::shared_ptr<IEntropyFunction<T>> ef;
  };
  // Get the measurement in ms.
  auto timer = entropy_timer(dta.memberNumbers, func);
  float ent_time = Utility::timeit<std::chrono::nanoseconds>(
    &timer, false, 3, 2);
  BOOST_TEST_MESSAGE(name + ": " + std::to_string(ent_time));
  BOOST_CHECK_LE(ent_time, expected * 1.1f);
}

BOOST_AUTO_TEST_CASE(Speeds_ShannonEntropySpeedIsNormal) {
  auto shannon_entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                  new ShannonEntropy<float>());
  test_IEntropySpeed(&shannon_entropy_f, 94.f, "ShannonEntropy<float>");
  auto shannon_entropy_ui = std::shared_ptr<IEntropyFunction<unsigned int>>(
                                  new ShannonEntropy<unsigned int>());
  test_IEntropySpeed(&shannon_entropy_ui, 103.f, "ShannonEntropy<uint>");
};

BOOST_AUTO_TEST_CASE(Speeds_pEntropySpeedIsNormal) {
  auto p_entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                  new InducedEntropy<float>(3.f));
  test_IEntropySpeed(&p_entropy_f, 54.f, "InducedEntropy<float>");
  auto p_entropy_ui = std::shared_ptr<IEntropyFunction<unsigned int>>(
                                  new InducedEntropy<unsigned int>(3.f));
  test_IEntropySpeed(&p_entropy_ui, 57.f, "InducedEntropy<uint>");
};

BOOST_AUTO_TEST_CASE(Speeds_TsallisEntropySpeedIsNormal) {
  auto entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                   new TsallisEntropy<float>(2));
  test_IEntropySpeed(&entropy_f, 44.f, "TsallisEntropy<float>");
};

BOOST_AUTO_TEST_CASE(Speeds_RenyiEntropySpeedIsNormal) {
  auto entropy_f = std::shared_ptr<IEntropyFunction<float>>(
                                   new RenyiEntropy<float>(2));
  test_IEntropySpeed(&entropy_f, 51.f, "RenyiEntropy<float>");
};
BOOST_AUTO_TEST_SUITE_END();