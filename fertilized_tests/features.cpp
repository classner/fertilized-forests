/* Author: Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

#include <chrono>
#include <string>
#include <vector>
#include <unordered_set>
#include <random>

#include <fertilized/features/ifeatureselectionprovider.h>
#include <fertilized/features/isurfacecalculator.h>
#include <fertilized/features/standardfeatureselectionprovider.h>
#include <fertilized/features/alignedsurfacecalculator.h>
#include <fertilized/features/featcalcparamset.h>
#include <fertilized/types.h>
#include <fertilized/data_providers/idataprovider.h>
#include <fertilized/util/sampling.h>

#include "./setup.h"
#include "./timeit.h"

// Required objects.
using fertilized::proposal_set_t;
using fertilized::Fertilized_Exception;
using fertilized::IFeatureSelectionProvider;
using fertilized::vector_hasher;
using fertilized::ISurfaceCalculator;
using fertilized::FeatCalcParamSet;
using fertilized::IDataProvider;

// Test objects.
using fertilized::StandardFeatureSelectionProvider;
using fertilized::ibinom;
using fertilized::vector_hasher;
using fertilized::AlignedSurfaceCalculator;

BOOST_AUTO_TEST_SUITE(Correctness_Features);

//---------------------------------------------------------------------------//
// ibinom.

BOOST_AUTO_TEST_CASE(Correctness_nChooseK) {
  for (unsigned int i = 0; i < 100; ++i) {
    if (i > 0)
      BOOST_CHECK_EQUAL(ibinom(i, 1), i);
    BOOST_CHECK_EQUAL(ibinom(i, i), 1);
    BOOST_CHECK_EQUAL(ibinom(i, 0), 1);
  }
  BOOST_CHECK_EQUAL(ibinom(5, 3), 10);
  BOOST_CHECK_EQUAL(ibinom(4, 2), 6);
  // Overflow detection.
  BOOST_CHECK_EQUAL(ibinom(1000, 100), -1);
}

//---------------------------------------------------------------------------//
// Vector Hasher.
BOOST_AUTO_TEST_CASE(Correctness_VectorHasher) {
  std::vector<size_t> tvec = std::vector<size_t>(5, 0);
  auto used_hashes = std::unordered_set<size_t>();
  auto hasher = vector_hasher();
  unsigned int collisions = 0;
  for (size_t i = 0; i < 1000; ++i) {
    tvec.push_back(i);
    size_t hash = hasher(tvec);
    if (used_hashes.find(hash) != used_hashes.end()) {
      collisions++;
      used_hashes.insert(hash);
    }
  }
  for (size_t i = 1; i < 1000; ++i) {
    tvec[0] = i;
    size_t hash = hasher(tvec);
    if (used_hashes.find(hash) != used_hashes.end()) {
      collisions++;
      used_hashes.insert(hash);
    }
  }
  BOOST_CHECK_EQUAL(collisions, 0);
};

//---------------------------------------------------------------------------//
// StandardFeatureSelectionProvider.
bool check_indexes_unique(const proposal_set_t &set) {
  auto used = std::unordered_set<size_t>();
  auto used_vecs = std::unordered_set<std::vector<size_t>, vector_hasher>();
  for (const auto &vec : set) {
    // Selection uniqueness.
    if (used_vecs.find(vec) != used_vecs.end())
      return false;
    else
      used_vecs.insert(vec);
    // Vector dimension uniqueness.
    if (vec.size() == 1)
      continue;
    used.clear();
    for (const auto &sel : vec) {
      if (used.find(sel) != used.end()) {
        return false;
      }
      else {
        used.insert(sel);
      }
    }
  }
  return true;
}

BOOST_AUTO_TEST_CASE(Correctness_StandardFeatureSelectionProvider_BasicProps) {
  for (unsigned int size = 0; size < 10; ++size) {
    for (unsigned int dim = 0; dim < 10; ++dim) {
      if (dim == 0 || size == 0) {
        BOOST_CHECK_THROW(StandardFeatureSelectionProvider(size, dim, 100, 100),
                          Fertilized_Exception);
      } else {
        StandardFeatureSelectionProvider sp(size, dim, 100, 100);
        for (int i = 0; i < 100; i++) {
          auto testsel = sp.get_proposals();
          BOOST_CHECK_EQUAL(testsel.size(), size);
          for (const auto &sel : testsel) {
            BOOST_CHECK_EQUAL(sel.size(), dim);
          }
        }
      }
    }
  }
};

BOOST_AUTO_TEST_CASE(Correctness_StandardFeatureSelectionProvider_Uniqueness) {
  StandardFeatureSelectionProvider sp1(10, 1, 100, 100);
  StandardFeatureSelectionProvider sp3(10, 3, 100, 100);
  StandardFeatureSelectionProvider sp1f(100, 1, 100, 100);
  for (int i = 0; i < 1000; i++) {
    auto testsel3 = sp3.get_proposals();
    sp3.register_used(testsel3);
    BOOST_CHECK(check_indexes_unique(testsel3));

    auto testsel1 = sp1.get_proposals();
    sp1.register_used(testsel1);
    BOOST_CHECK(check_indexes_unique(testsel1));

    auto testsel1f = sp1f.get_proposals();
    sp1f.register_used(testsel1f);
    BOOST_CHECK(check_indexes_unique(testsel1f));
  }
};

BOOST_AUTO_TEST_CASE(Correctness_StandardFeatureSelectionProvider_MaxUsage) {
  StandardFeatureSelectionProvider sp1(5, 1, 100, 10);
  auto used1 = std::unordered_set<size_t>();
  StandardFeatureSelectionProvider sp3(10, 3, 100, 10);
  auto used3 = std::unordered_set<size_t>();
  StandardFeatureSelectionProvider sp1f(10, 1, 100, 10);
  auto used1f = std::unordered_set<size_t>();

  for (int i = 0; i < 1000; i++) {
    auto testsel3 = sp3.get_proposals();
    sp3.register_used(testsel3);
    for (const auto &sel : testsel3) {
      for (const auto &dim : sel) {
        used3.insert(dim);
      }
    }
    auto testsel1 = sp1.get_proposals();
    sp1.register_used(testsel1);
    for (const auto &sel : testsel1) {
      for (const auto &dim : sel) {
        used1.insert(dim);
      }
    }
    auto testsel1f = sp1f.get_proposals();
    sp1f.register_used(testsel1f);
    for (const auto &sel : testsel1f) {
      for (const auto &dim : sel) {
        used1f.insert(dim);
      }
    }
  }
  BOOST_CHECK_EQUAL(used3.size(), 10);
  BOOST_CHECK_EQUAL(used1.size(), 10);
  BOOST_CHECK_EQUAL(used1f.size(), 10);
};

//---------------------------------------------------------------------------//
// AlignedSurfaceCalculator.
#ifndef DISABLE_FEATURE_CALCULATOR
BOOST_AUTO_TEST_CASE(Correctness_IdentityFeatureCalc_ColWise) {
  ClassificationDataProviderFixture<int> dta(100, 10, 2,
    [](int *d, size_t ind){
      for (int i = 0; i < 10; ++i) {
        *d = static_cast<int>(i);
        d += 100; }},
    [](unsigned int *a, size_t ind){*a = static_cast<unsigned int>(ind % 2);});


  auto feat_calc = AlignedSurfaceCalculator<int, unsigned int>();
  auto element_ids = std::vector<size_t>(100);
  std::iota(element_ids.begin(), element_ids.end(), 0);
  for (int i = 0; i < 10; ++i) {
    std::vector<size_t> feat_sel = std::vector<size_t>(1, static_cast<size_t>(i));
    auto result = feat_calc.calculate(feat_sel, FeatCalcParamSet(),
                                      *dta.dprov, element_ids);
    for (const int &elem : result) {
      BOOST_CHECK_EQUAL(elem, i);
    }
  }
  for (int i = 0; i < 10; ++i) {
    std::vector<size_t> feat_sel = std::vector<size_t>(1, static_cast<size_t>(i));
    BOOST_CHECK_EQUAL(feat_calc.calculate(feat_sel, FeatCalcParamSet(),
      dta.input_data.get(), 100), i);
  }
  auto empt_res = feat_calc.calculate(std::vector<size_t>(1, 0), FeatCalcParamSet(),
                                      *dta.dprov, std::vector<size_t>());
  BOOST_CHECK_EQUAL(empt_res.size(), 0);
};

BOOST_AUTO_TEST_CASE(Correctness_IdentityFeatureCalc_RowWise) {
  ClassificationDataProviderFixture<int> dta(100, 10, 2,
    [](int *d, size_t ind){for (int i = 0; i < 10; ++i) *(d++) = static_cast<int>(i);},
    [](unsigned int *a, size_t ind){*a = static_cast<unsigned int>(ind % 2);},
    false);

  auto feat_calc = AlignedSurfaceCalculator<int, unsigned int>();
  auto element_ids = std::vector<size_t>(100);
  std::iota(element_ids.begin(), element_ids.end(), 0);
  for (int i = 0; i < 10; ++i) {
    std::vector<size_t> feat_sel = std::vector<size_t>(1, static_cast<size_t>(i));
    auto result = feat_calc.calculate(feat_sel, FeatCalcParamSet(),
                                      *dta.dprov, element_ids);
    for (const int &elem : result) {
      BOOST_CHECK_EQUAL(elem, i);
    }
  }
  for (int i = 0; i < 10; ++i) {
    std::vector<size_t> feat_sel = std::vector<size_t>(1, static_cast<size_t>(i));
    BOOST_CHECK_EQUAL(feat_calc.calculate(feat_sel, FeatCalcParamSet(),
      dta.input_data.get(), 1), i);
  }
  auto empt_res = feat_calc.calculate(std::vector<size_t>(1, 0), FeatCalcParamSet(),
                                      *dta.dprov, std::vector<size_t>());
  BOOST_CHECK_EQUAL(empt_res.size(), 0);
};
#endif

//---------------------------------------------------------------------------//
// Serialization.
#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Serialization_StandardFeatureSelectionProvider) {
  auto sp1 = std::make_shared<StandardFeatureSelectionProvider>(1, 3, 100, 10);
  sp1 -> get_proposals();
  auto restored = serialize_deserialize(sp1);
  auto original = sp1 -> get_proposals();
  auto after_rest = restored -> get_proposals();
  auto original_vec = *original.begin();
  auto restored_vec = *after_rest.begin();
  for (size_t i = 0; i < 3; ++i)
    BOOST_CHECK_EQUAL(original_vec[i], restored_vec[i]);

  auto sp1f = std::make_shared<StandardFeatureSelectionProvider>(10, 1, 100, 10);
  sp1f -> get_proposals();
  auto restored1f = serialize_deserialize(sp1f);
  auto original1f = sp1f -> get_proposals();
  auto after_rest1f = restored1f -> get_proposals();
  auto original_vecit1f = original1f.begin();
  auto restored_vecit1f = after_rest1f.begin();
  while (original_vecit1f != original1f.end()) {
    BOOST_CHECK_EQUAL((*original_vecit1f)[0], (*restored_vecit1f)[0]);
    original_vecit1f++;
    restored_vecit1f++;
  }
};
#ifndef DISABLE_FEATURE_CALCULATOR
BOOST_AUTO_TEST_CASE(Serialization_IdentityFeatCalc) {
  auto f = std::make_shared<AlignedSurfaceCalculator<int, unsigned int>>();
  auto restored = serialize_deserialize(f);
  ClassificationDataProviderFixture<int> dta(100, 10, 2,
  [](int *d, size_t ind){for (int i = 0; i < 10; ++i) *(d++) = static_cast<int>(i);},
  [](unsigned int *a, size_t ind){*a = static_cast<unsigned int>(ind % 2);},
  false);

  auto element_ids = std::vector<size_t>(100);
  std::iota(element_ids.begin(), element_ids.end(), 0);
  for (int i = 0; i < 10; ++i) {
    std::vector<size_t> feat_sel = std::vector<size_t>(1, static_cast<size_t>(i));
    auto result = restored -> calculate(feat_sel, FeatCalcParamSet(),
                                        *dta.dprov, element_ids);
    for (const int &elem : result) {
      BOOST_CHECK_EQUAL(elem, i);
    }
  }
};
#endif
#endif

BOOST_AUTO_TEST_SUITE_END();


//---------------------------------------------------------------------------//
// Speed.
BOOST_AUTO_TEST_SUITE(Speeds_Features);
struct sp_timer : public Utility::ITimefunc {
  sp_timer(IFeatureSelectionProvider *sp) : sp(sp) {}
  int operator()() { return static_cast<int>(sp -> get_proposals().size()); }
 private:
  IFeatureSelectionProvider *sp;
};

void test_IFeatureSelProvSpeed(IFeatureSelectionProvider *sp,
                                      const float &expected,
                                      const std::string &name) {
  // Get the measurement in ms.
  auto timer = sp_timer(sp);
  float ent_time = Utility::timeit<std::chrono::nanoseconds>(
                                      &timer, false, 3, 2);
  BOOST_TEST_MESSAGE(name + ": " + std::to_string(ent_time));
  BOOST_CHECK_LE(ent_time, expected * 1.1f);
}

BOOST_AUTO_TEST_CASE(Speeds_StandardFetSelProvSpeedIsNormal) {
  StandardFeatureSelectionProvider sp1(50, 1, 1000, 100);
  test_IFeatureSelProvSpeed(&sp1, 13700.f,
    "StandardFeatureSelectionProvider(50,1,1000,100)");
  StandardFeatureSelectionProvider sp3(50, 3, 1000, 100);
  test_IFeatureSelProvSpeed(&sp3, 45000.f,
    "StandardFeatureSelectionProvider(50,3,1000,100)");
};
#ifndef DISABLE_FEATURE_CALCULATOR
template <typename I, typename F, typename A>
struct ifc_timer : public Utility::ITimefunc {
  ifc_timer(ISurfaceCalculator<I, F, A> *fc,
            FeatCalcParamSet *pset,
            const IDataProvider<I, A> &dprov,
            const size_t &n_features)
            : fc(fc), pset(pset), dprov(&dprov),
              random_engine(std::mt19937(1)) {
    elem_list = dprov.get_initial_sample_list();
    n_elem_dist = std::uniform_int_distribution<size_t>(0, elem_list -> size()-1);
    feat_dist = std::uniform_int_distribution<size_t>(0, n_features - 1);
  }
  int operator()() {
    std::shuffle(elem_list -> begin(), elem_list -> end(), random_engine);
    size_t n_elems = n_elem_dist(random_engine);
    std::vector<fertilized::element_id_t> elems(elem_list->begin(),
                                                elem_list->begin() + n_elems);
    auto feat_sel = std::vector<size_t>(1, feat_dist(random_engine));
    return static_cast<int>(
      fc -> calculate(feat_sel, *pset, *dprov, elems).size()); }
 private:
  std::shared_ptr<std::vector<fertilized::element_id_t>> elem_list;
  ISurfaceCalculator<I, F, A> *fc;
  FeatCalcParamSet *pset;
  const IDataProvider<I, A> *dprov;
  std::uniform_int_distribution<size_t> n_elem_dist;
  std::uniform_int_distribution<size_t> feat_dist;
  std::mt19937 random_engine;
};

template <typename I, typename F, typename A>
void test_IFeatCalcSpeed(ISurfaceCalculator<I, F, A> *fc,
                         FeatCalcParamSet *pset,
                         const float &expected,
                         const std::string &name) {
  ClassificationDataProviderFixture<int> dta(1000, 100, 2,
    [](int *d, size_t ind){
      for (int i = 0; i < 10; ++i) {
        *d = static_cast<int>(i);
        d += 100; }},
    [](unsigned int *a, size_t ind){*a = static_cast<unsigned int>(ind % 2);});
  auto feat_ids = std::vector<size_t>(1);
  // Get the measurement in ms.
  float time = Utility::timeit<std::chrono::nanoseconds>(
    &ifc_timer<I, F, A>(fc, pset, *dta.dprov, 100), false, 3, 2);
  BOOST_TEST_MESSAGE(name + ": " + std::to_string(time));
  BOOST_CHECK_LE(time, expected * 1.1f);
}

BOOST_AUTO_TEST_CASE(Speeds_IdentityFeatCalcSpeedIsNormal) {
  auto fc = AlignedSurfaceCalculator<int, unsigned int>();
  auto params = FeatCalcParamSet();
  test_IFeatCalcSpeed(&fc, &params, 45000.f, "AlignedSurfaceCalculator");
};
#endif
BOOST_AUTO_TEST_SUITE_END();