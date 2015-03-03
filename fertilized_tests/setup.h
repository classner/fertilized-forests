/* Author: Christoph Lassner */
#ifndef FERTILIZED_TEST_SETUP_H_
#define FERTILIZED_TEST_SETUP_H_

#include <vector>
#include <sstream>
#include <functional>

#ifdef SERIALIZATION_ENABLED
#include <fertilized/serialization/serialization.h>
#endif
#include <fertilized/gains/igaincalculator.h>
#include <fertilized/gains/entropygain.h>
#include <fertilized/data_providers/unchangeddataprovider.h>
#include <fertilized/impurities/shannonentropy.h>
#include <fertilized/impurities/inducedentropy.h>
#include <fertilized/ndarray.h>

#include "timeit.h"

using ndarray::Array;
using ndarray::Vector;
using ndarray::allocate;
using ndarray::makeVector;
using ndarray::external;

// Selectively disable certain tests.
#define DISABLE_FEATURE_CALCULATOR


/**
 * \brief Maximum tolerated floating point difference for checks.
 *
 * The value is a percentage of the absolute smaller number.
 */
static const float FPTOLERANCE = 0.0002f;
/** \brief Maximum tolerated floating point diff (abs) from zero allowed. */
static const float FPMAXDIFFZRO = 0.000001f;

/** \brief Solves a problem with the boost check_small and check_close defines.
 *
 * (A great, but only very nearly correct description of the boost macros:
 *  http://stackoverflow.com/questions/2113634/problem-with-boost-check-close-fraction/2113891#2113891
 *  it must be ... (min(abs(x), abs(y)) * 0.1)))
 *
 * This is a classical problem of floating point closeness testing:
 * For floating point values, giving an absolute tolerated difference does
 * not make sense, since the minimum difference between two numbers changes
 * according to their value. So it makes sense to specify a maximum tolerated
 * difference, calculated from the absolute size of the (abs) smaller of the
 * two numbers.
 *
 * When one of the two numbers is zero, however, this approach does not work
 * anymore. The maximum specified difference from zero is then always zero.
 * This makes it necessary to specify an absolute tolerated threshold.
 *
 * There is no boost check that takes this into account. Here, this macro
 * comes into play:
 */
#define CHECK_CLOSE(val1, val2, percent_tol, absolute_tol_if_zero) {\
  auto v1 = (val1), v2 = (val2), atol = (absolute_tol_if_zero);     \
  if (!(v1 == 0 && v2 == 0)) {                                      \
    if (v1 == 0)                                                    \
      BOOST_CHECK_SMALL(v2, atol);                                  \
    else if (v2 == 0)                                               \
      BOOST_CHECK_SMALL(v1, atol);                                  \
    else                                                            \
      BOOST_CHECK_CLOSE(v1, v2, (percent_tol));                     \
  };}

/** \brief Convenience overload. */
#define CHECK_CLOSE_(val1, val2) \
        CHECK_CLOSE((val1), (val2), FPTOLERANCE, FPMAXDIFFZRO);

/**
 * \brief A fixture to test the impurity measures.
 *
 *  The first two elements are zero,
 * the second two are ones, ...
 */
template <typename T>
struct MemberNumberFixture {
  std::vector<T> memberNumbers;
  std::vector<T> part_1;
  std::vector<T> part_2;

  // Initialize the fixture.
  MemberNumberFixture() {
    // Initialize the first to elements to zero, the rest to arbitrary
    // values for the tests.
    memberNumbers = std::vector<T>(10);
    for (size_t i = 0; i < 10; ++i)
      memberNumbers[i] = static_cast<T>(i / 2);

    part_1 = std::vector<T>(memberNumbers.begin(), memberNumbers.begin() + 1);
    part_2 = std::vector<T>(memberNumbers.begin(), memberNumbers.begin() + 2);
  };
};

/**
 * \brief A fixture to test the gain measures.
 * The first two elements are zero,
 * the second two are ones, ... This twice for both groups.
 */
template <typename T>
struct DualMemberNumberFixture {
  std::vector<T> hist_l;
  std::vector<T> hist_r;

  DualMemberNumberFixture() {
    // Initialize the first to elements to zero, the rest to arbitrary
    // values for the tests.
    hist_l = std::vector<T>(10);
    hist_r = std::vector<T>(10);
    for (size_t i = 0; i < 10; ++i) {
      hist_l[i] = static_cast<T>(i / 2);
      hist_r[i] = hist_l[i];
    }
  };
};

template <typename T>
struct EntropyGainFixture {
  std::shared_ptr<fertilized::IGainCalculator<T>> egain;
  std::shared_ptr<fertilized::IGainCalculator<T>> pent2gain;

  EntropyGainFixture() {
    egain = std::shared_ptr<fertilized::IGainCalculator<T>>(
        new fertilized::EntropyGain<T>(std::make_shared<fertilized::ShannonEntropy<T>>()));
    pent2gain = std::shared_ptr<fertilized::IGainCalculator<T>>(
        new fertilized::EntropyGain<T>(std::make_shared<fertilized::InducedEntropy<T>>(2.f)));
  };
};

template <typename I, typename A=unsigned int>
struct ClassificationDataProviderFixture {
  ClassificationDataProviderFixture(
      const size_t &n_samples,
      const size_t &n_sample_dim,
      const size_t &n_classes,
      std::function<void (I *, size_t)> data_gen,
      std::function<void (A*, size_t)> annot_gen,
      std::function<void (float*, size_t)> weight_gen=[](float*pf, size_t i){*pf=1.f;},
      bool column_wise = true,
      const size_t &annot_factor = 1) {
    input_data = std::shared_ptr<I>(new I[n_samples * n_sample_dim],
                                                [](I *p){ delete[] p;});
    annot_data = std::shared_ptr<A>(new A[n_samples * annot_factor],
      [](A *p){delete[] p;});
    weights = std::shared_ptr<float>(new float[n_samples],
                                     [](float *p) {delete[] p;});
    if (column_wise) {
      for (size_t i = 0; i < n_samples; ++i) {
        data_gen(input_data.get() + i, i);
        annot_gen(annot_data.get() + i * annot_factor, i);
        weight_gen(weights.get() + i, i);
      }
    } else {
      for (size_t i = 0; i < n_samples; ++i) {
        data_gen(input_data.get() + i * n_sample_dim, i);
        annot_gen(annot_data.get() + i * annot_factor, i);
        weight_gen(weights.get() + i, i);
      }
    }
    input_array = external(input_data.get(),
                           makeVector(n_samples,
                                      n_sample_dim));
    annot_array = external(annot_data.get(),
                           makeVector<size_t>(n_samples, 1));
    if (n_samples != 0 && n_sample_dim != 0)
      dprov = std::shared_ptr<fertilized::UnchangedDataProvider<I, A>>(
        new fertilized::UnchangedDataProvider<I, A>(input_array,
                                                    annot_array));
  }

  ClassificationDataProviderFixture(
    const size_t &n_samples,
    const size_t &sample_dim,
    const size_t &n_classes,
    const bool &column_wise = true,
    const size_t &annot_factor = 1) {
    input_data = std::shared_ptr<I>(new I[n_samples * sample_dim],
                                    [](I *p){ delete[] p;});
    annot_data = std::shared_ptr<A>(new A[n_samples * annot_factor],
                                    [](A *p){delete[] p;});
    weights = std::shared_ptr<float>(new float[n_samples],
                                     [](float *p) { delete[] p; });
    auto data_gen = [&](I *d, size_t ind){
      for (size_t i = 0; i < sample_dim; ++i) {
        *d = static_cast<I>(i);
        if (column_wise)
          d += n_samples;
        else
          d++;
      }
    };
    auto annot_gen = [&n_classes, &annot_factor](A *a, size_t ind){
      for (size_t i = 0; i < annot_factor; ++i)
        a[i] = static_cast<A>(ind % n_classes);
    };
    auto weight_gen = [&](float *d, size_t ind){ *d = 1.f; };
    if (column_wise) {
      for (size_t i = 0; i < n_samples; ++i) {
        data_gen(input_data.get() + i, i);
        annot_gen(annot_data.get() + i* annot_factor, i);
        weight_gen(weights.get() + i, i);
      }
    } else {
      for (size_t i = 0; i < n_samples; ++i) {
        data_gen(input_data.get() + i * sample_dim, i);
        annot_gen(annot_data.get() + i* annot_factor, i);
        weight_gen(weights.get() + i, i);
      }
    }
    input_array = external(input_data.get(),
                           makeVector(n_samples,
                                      sample_dim));
    annot_array = external(annot_data.get(),
                           makeVector<size_t>(n_samples, 1));
    if (n_samples != 0 && sample_dim != 0)
      dprov = std::shared_ptr<fertilized::UnchangedDataProvider<I, A>>(
        new fertilized::UnchangedDataProvider<I, A>(input_array,
                                                    annot_array));
  }
  Array<I, 2, 2> input_array;
  Array<A, 2, 2> annot_array;
  std::shared_ptr<I> input_data;
  std::shared_ptr<A> annot_data;
  std::shared_ptr<float> weights;
  std::shared_ptr<fertilized::IDataProvider<I, A>> dprov;
};


template <typename regression_dt>
struct RegressionDataProviderFixture {
  RegressionDataProviderFixture(
    const size_t &n_samples,
    const size_t &sample_input_dim,
    const size_t &sample_annot_dim,
    std::function<void (regression_dt *, size_t, size_t)> data_gen,
    std::function<void (regression_dt *, size_t, size_t)> annot_gen,
    bool column_wise = true) {
    input_data = std::shared_ptr<regression_dt>(new regression_dt[n_samples * sample_input_dim],
                                    [](regression_dt *p){ delete[] p;});
    annot_data = std::shared_ptr<regression_dt>(new regression_dt[n_samples * sample_annot_dim],
                                               [](regression_dt *p){delete[] p;});
    if (column_wise) {
      for (size_t i = 0; i < n_samples; ++i) {
        for (size_t j = 0; j < sample_input_dim; j++) {
          data_gen(input_data.get() + i + j*sample_input_dim, i, j);
        }
        for (size_t j = 0; j < sample_annot_dim; j++) {
          annot_gen(annot_data.get() + i + j*sample_annot_dim, i, j);
        }

      }
    } else {
      for (size_t i = 0; i < n_samples; ++i) {
        for (size_t j = 0; j < sample_input_dim; j++) {
          data_gen(input_data.get() + i*sample_input_dim + j, i, j);
        }
        for (size_t j = 0; j < sample_annot_dim; j++) {
          annot_gen(annot_data.get() + i*sample_annot_dim + j, i, j);
        }
      }
    }
    dprov = std::shared_ptr<fertilized::UnchangedDataProvider<regression_dt, regression_dt>>(
      new fertilized::UnchangedDataProvider<regression_dt, regression_dt>(
                            input_data, annot_data, sample_input_dim, sample_annot_dim, n_samples,
                            column_wise));

  }

  std::shared_ptr<regression_dt> input_data;
  std::shared_ptr<regression_dt> annot_data;
  std::shared_ptr<fertilized::IDataProvider<regression_dt, regression_dt>> dprov;
};

template <typename i_dt, typename a_dt>
struct ImageDataFixture {
  static void extraction_helper(size_t pos_x,
                                size_t pos_y,
                                i_dt *dta,
                                size_t dta_shape_y,
                                size_t dta_shape_x,
                                i_dt *target) {
    for (int z = 0; z < 3; ++z) {
      for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
          target[ z * 100 + y * 10 + x] = dta[ z * dta_shape_y * dta_shape_x +
                                               (y+pos_y-5) * dta_shape_x +
                                               (x+pos_x-5) ];
        }
      }
    }
  }

  ImageDataFixture() {
    image_ptrs_vec = std::make_shared<std::vector<i_dt*>>();
    const_im_ptrs_vec = std::make_shared<std::vector<const i_dt*>>();
    i_dt *im_1 = static_cast<i_dt*>(malloc(40 * 40 * 3 * sizeof(i_dt)));
    Array<i_dt, 3, 3> im_arr_1 = external(im_1, makeVector<size_t>(3, 40, 40));
    std::iota(im_1, im_1 + 40*40*3, 0);
    image_ptrs_vec -> push_back(im_1);
    const_im_ptrs_vec -> push_back(im_1);
    i_dt *im_2 = static_cast<i_dt*>(malloc(50 * 50 * 3 * sizeof(i_dt)));
    Array<i_dt, 3, 3> im_arr_2 = external(im_2, makeVector<size_t>(3, 50, 50));
    std::iota(im_2, im_2 + 50*50*3, 0);
    image_ptrs_vec -> push_back(im_2);
    const_im_ptrs_vec -> push_back(im_2);
    images.push_back(im_arr_1);
    images.push_back(im_arr_2);
    shapes = std::shared_ptr<a_dt>(new a_dt[4],
                                   [](a_dt *p){ delete[] p; });
    shapes.get()[0] = 40;
    shapes.get()[1] = 40;
    shapes.get()[2] = 50;
    shapes.get()[3] = 50;
    patch_descs = std::shared_ptr<a_dt>(new a_dt[4 * 5],
                                        [](a_dt *p) { delete[] p;});
    patch_vec = std::make_shared<std::vector<i_dt*>>();
    i_dt *tmp;
    //
    patch_descs.get()[0] = 0;
    patch_descs.get()[1] = 15;
    patch_descs.get()[2] = 15;
    patch_descs.get()[3] = 2;
    patch_descs.get()[4] = 2;
    tmp = static_cast<i_dt*>(malloc(10 * 10 * 3 * sizeof(i_dt)));
    extraction_helper(15, 15, im_1, 40, 40, tmp);
    patch_vec -> push_back(tmp);
    //
    patch_descs.get()[5] = 1;
    patch_descs.get()[6] = 35;
    patch_descs.get()[7] = 35;
    patch_descs.get()[8] = -1;
    patch_descs.get()[9] = -1;
    tmp = static_cast<i_dt*>(malloc(10 * 10 * 3 * sizeof(i_dt)));
    extraction_helper(35, 35, im_2, 50, 50, tmp);
    patch_vec -> push_back(tmp);
    //
    patch_descs.get()[10] = 0;
    patch_descs.get()[11] = 25;
    patch_descs.get()[12] = 25;
    patch_descs.get()[13] = 0;
    patch_descs.get()[14] = 0;
    tmp = static_cast<i_dt*>(malloc(10 * 10 * 3 * sizeof(i_dt)));
    extraction_helper(25, 25, im_1, 40, 40, tmp);
    patch_vec -> push_back(tmp);
    //
    patch_descs.get()[15] = 1;
    patch_descs.get()[16] = 15;
    patch_descs.get()[17] = 15;
    patch_descs.get()[18] = 0;
    patch_descs.get()[19] = 0;
    tmp = static_cast<i_dt*>(malloc(10 * 10 * 3 * sizeof(i_dt)));
    extraction_helper(15, 15, im_2, 50, 50, tmp);
    patch_vec -> push_back(tmp);
    patch_desc_arr = external(patch_descs.get(), makeVector<size_t>(4, 5));
  }

  ~ImageDataFixture() {
    for (int i = 0; i < image_ptrs_vec -> size(); ++i)
      free(image_ptrs_vec -> operator[](i));
    for (int i = 0; i < patch_vec -> size(); ++i)
      free(patch_vec -> operator[](i));
  }

  std::shared_ptr<std::vector<i_dt*>> image_ptrs_vec;
  std::shared_ptr<std::vector<const i_dt*>> const_im_ptrs_vec;
  std::vector<Array<const i_dt, 3, 3>> images;
  Array<const a_dt, 2, 2> patch_desc_arr;
  std::shared_ptr<a_dt> shapes;
  std::shared_ptr<a_dt> patch_descs;
  std::shared_ptr<std::vector<i_dt*>> patch_vec;
};

template <typename TT, typename IT>
struct PredictTimer : public Utility::ITimefunc {
  PredictTimer(const TT *t, const IT *d) : tree(t), data(d) {}

  int operator()() { return static_cast<int>(tree -> predict(*data)[0][0]);};

  const TT *tree;
  const IT *data;
};

#ifdef SERIALIZATION_ENABLED
template <typename T>
std::shared_ptr<T> serialize_deserialize(const std::shared_ptr<T> &obj) {
  // Serialize
  std::string ser = fertilized::serialize(obj.get());
  std::stringstream ss;
  ss.str(ser);
  auto restored = std::shared_ptr<T>(fertilized::deserialize<T>(ss));
  return restored;
};

template <typename i_dt, typename a_dt>
struct TreeFixture {

  TreeFixture() {

  }
};
#endif
#endif  // FERTILIZED_TEST_SETUP_H_
