/* Author: Christoph Lassner. */
#include <fertilized/global.h>

#include <boost/test/unit_test.hpp>

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <random>

#include <fertilized/data_providers/idataprovider.h>
#include <fertilized/data_providers/sample.h>
#include <fertilized/data_providers/unchangeddataprovider.h>
#include <fertilized/data_providers/unchangedfdataprovider.h>
#include <fertilized/data_providers/patchtoimagecoordinatetransformer.h>
#include <fertilized/data_providers/patchsamplemanager.h>
#include <fertilized/data_providers/nocopypatchsamplemanager.h>
#include <fertilized/data_providers/subsamplingdataprovider.h>
#include <fertilized/tree.h>
#include <fertilized/threshold_optimizers/classificationthresholdoptimizer.h>
#include <fertilized/features/differencesurfacecalculator.h>
#include <fertilized/features/volumefeatureselectionprovider.h>
#include <fertilized/deciders/thresholddecider.h>
#include <fertilized/gains/entropygain.h>
#include <fertilized/leafs/houghleafmanager.h>
#include <fertilized/types.h>
#include <fertilized/bagging/equaldistbagging.h>
#include <fertilized/ndarray.h>
#include <fertilized/types.h>

#include "./setup.h"
#include "./timeit.h"

// Required objects.
using ndarray::Array;
using ndarray::allocate;
using ndarray::Vector;
using ndarray::makeVector;
using fertilized::IDataProvider;
using fertilized::Fertilized_Exception;
using fertilized::Sample;
using fertilized::tree_id_t;
using fertilized::element_id_t;
using fertilized::usage_map_t;
using fertilized::EqualDistBagging;
using fertilized::FeatCalcParamSet;
using fertilized::EThresholdSelection;

// Test objects.
using fertilized::UnchangedDataProvider;
using fertilized::UnchangedFDataProvider;
using fertilized::PatchToImageCoordinateTransformer;
using fertilized::PatchSampleManager;
using fertilized::NoCopyPatchSampleManager;
using fertilized::SubsamplingDataProvider;
using fertilized::Tree;
using fertilized::ClassificationThresholdOptimizer;
using fertilized::DifferenceSurfaceCalculator;
using fertilized::VolumeFeatureSelectionProvider;
using fertilized::ThresholdDecider;
using fertilized::EntropyGain;
using fertilized::HoughLeafManager;


BOOST_AUTO_TEST_SUITE(Correctness_DataProviders);

//---------------------------------------------------------------------------//
// Unchanged data provider.
BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvProps) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2);
  UnchangedDataProvider<float, unsigned int> tprov(dta.input_array,
                                                   dta.annot_array);
  ClassificationDataProviderFixture<float> emptydta(100, 0, 2);
  BOOST_CHECK_THROW((UnchangedDataProvider<float, unsigned int>(emptydta.input_array,
                                                                emptydta.annot_array)),
                    Fertilized_Exception);
  BOOST_CHECK_EQUAL(tprov.feat_vec_dim, 10);
  BOOST_CHECK_EQUAL(tprov.get_n_samples(), 100);
  BOOST_CHECK_EQUAL(tprov.get_column_wise(), false);
  BOOST_CHECK_EQUAL(tprov.get_samples() -> size(), 100);
};

BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvInitSampleList) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2);
  UnchangedDataProvider<float, unsigned int> tprov(dta.input_array,
                                                   dta.annot_array);
  auto slist = tprov.get_initial_sample_list();
  for (size_t i = 0; i < 100; ++i) {
    BOOST_CHECK_EQUAL((*slist)[i], i);
  }
}

BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvAnnotations) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2);
  UnchangedDataProvider<float, unsigned int> tprov(dta.input_array,
                                                   dta.annot_array);
  // Check that all annotations are available properly.
  auto &anno_pointers = *(tprov.get_samples());
  for (size_t i = 0; i < 100; ++i) {
    BOOST_CHECK_EQUAL(*(anno_pointers[i].annotation),
                      static_cast<unsigned int>(i % 2));
  };
}

BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvData) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2, false);
  // For row-wise data.
  UnchangedDataProvider<float, unsigned int> rowtprov(dta.input_array,
                                                      dta.annot_array);
  auto &row_data_pointers = *(rowtprov.get_samples());
  for (size_t i = 0; i < 100; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      BOOST_CHECK_EQUAL(*(row_data_pointers[i].data +
                          row_data_pointers[i].data_step * j),
                        static_cast<unsigned int>(j));
      BOOST_CHECK_EQUAL(row_data_pointers[i].data_step, 1);
    }
  }
};

BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvWeights) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2, false);
  UnchangedDataProvider<float, unsigned int> tprov(dta.input_array,
                                                   dta.annot_array);
  // Check that the weights are available.
  auto &weights = *(tprov.get_samples());
  for (int i = 0; i < 100; ++i)
    BOOST_CHECK_EQUAL(weights[i].weight, 1.f);
}

BOOST_AUTO_TEST_CASE(Correctness_UnchangedDProvModFuncs) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2, false);
  UnchangedDataProvider<float, unsigned int> tprov(dta.input_array,
                                                   dta.annot_array);
  BOOST_CHECK_THROW(tprov.add_to_training_set(
                       std::vector<Sample<float, unsigned int>>()),
                    Fertilized_Exception);
  BOOST_CHECK_THROW(tprov.add_to_validation_set(
                        std::vector<Sample<float, unsigned int>>()),
                    Fertilized_Exception);
  BOOST_CHECK_THROW(tprov.remove_from_training_set(
                        std::vector<size_t>()),
                    Fertilized_Exception);
  BOOST_CHECK_THROW(tprov.remove_from_validation_set(
                        std::vector<size_t>()),
                    Fertilized_Exception);
}

//---------------------------------------------------------------------------//
// Unchanged forest data provider.
BOOST_AUTO_TEST_CASE(Correctness_UnchangedFDProvProps) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2);
  UnchangedFDataProvider<float, unsigned int> tprov(dta.input_array,
                                                    dta.annot_array);
  ClassificationDataProviderFixture<float> emptydta(100, 0, 2);
  BOOST_CHECK_THROW(
    (UnchangedFDataProvider<float, unsigned int>(emptydta.input_array,emptydta.annot_array)),
                    Fertilized_Exception);
  BOOST_CHECK_EQUAL(tprov.get_samples() -> size(), 100);
};

BOOST_AUTO_TEST_CASE(Correctness_UnchangedFDProvTreeConstruct) {
  ClassificationDataProviderFixture<float> dta(100, 10, 2);
  auto tsplit = EqualDistBagging<float, unsigned int,
                                 unsigned int, float, float>();
  for (size_t n_trees = 2; n_trees < 10; ++n_trees) {
    UnchangedFDataProvider<float, unsigned int> tprov(dta.input_array,
                                                      dta.annot_array);
    auto umap = tsplit.get_initial_split(n_trees, &tprov);
    tprov.create_tree_providers(n_trees, umap);
    for (size_t tree_id = 0; tree_id < n_trees; ++tree_id) {
      auto slist = tprov.dproviders[tree_id] -> get_initial_sample_list();
      auto vallist = tprov.dproviders[tree_id] -> get_validation_sample_list();
      BOOST_CHECK_EQUAL(slist -> size(), umap[tree_id].first -> size());
      for (size_t ind = 0; ind < umap[tree_id].first -> size(); ++ind) {
        BOOST_CHECK_EQUAL((*slist)[ind], (*umap[tree_id].first)[ind]);
      }
      BOOST_CHECK_EQUAL(vallist -> size(), umap[tree_id].second -> size());
      for (size_t ind = 0; ind < umap[tree_id].second -> size(); ++ind) {
        BOOST_CHECK_EQUAL((*vallist)[ind], (*umap[tree_id].second)[ind]);
      }
    }
  }
}

//---------------------------------------------------------------------------//
// PatchToImageCoordinateTransformer
BOOST_AUTO_TEST_CASE(Correctness_CoordTransformer_ravel) {
  for (size_t z = 0; z < 2; ++z) {
    for (size_t y = 0; y < 10; ++y) {
      for (size_t x = 0; x < 10; ++x) {
        BOOST_CHECK_EQUAL(PatchToImageCoordinateTransformer::ravel_indices(x,
                               y, z, 20, 10),
                          z * 20 * 10 + y * 10 + x);
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(Correctness_CoordTransformer_unravel) {
  size_t rx, ry, rz;
  for (size_t z = 0; z < 2; ++z) {
    for (size_t y = 0; y < 10; ++y) {
      for (size_t x = 0; x < 10; ++x) {
        PatchToImageCoordinateTransformer::unravel_index(z * 20 * 10 +
                                                         y * 10 + x,
                                                         20, 10,
                                                         &rx, &ry, &rz);
        BOOST_CHECK_EQUAL(rx, x);
        BOOST_CHECK_EQUAL(ry, y);
        BOOST_CHECK_EQUAL(rz, z);
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(Correctness_CoordTransformer_patch_to_image) {
  auto pttit = PatchToImageCoordinateTransformer(30, 30, 2, 40, 40, true);
  BOOST_CHECK_EQUAL(pttit.patch_to_image(0, 40, 40, 0, 0, true), 0);
  BOOST_CHECK_EQUAL(pttit.patch_to_image(1799, 40, 40, 10, 10, true), 3199);
  auto pttitf = PatchToImageCoordinateTransformer(30, 30, 2, 40, 40, false);
  BOOST_CHECK_EQUAL(pttitf.patch_to_image(0, 40, 40, 15, 15, false), 0);
  BOOST_CHECK_EQUAL(pttitf.patch_to_image(1799, 40, 40, 25, 25, false), 3199);
}

BOOST_AUTO_TEST_CASE(Correctness_CoordTransformer_LUC) {
  auto pttit = PatchToImageCoordinateTransformer(30, 30, 2, 40, 40, true);
  BOOST_CHECK_EQUAL(pttit.patch_to_image(0, 40, 40, 0, 0, true),
                    pttit.patch_to_image(0, 40, 40, 15, 15, false));
}

BOOST_AUTO_TEST_CASE(Correctness_CoordTransformer_operator__) {
    typedef std::tuple<std::vector<size_t>, FeatCalcParamSet,
      EThresholdSelection, std::pair<int16_t, int16_t>>
      decision_tuple_t;
    auto posvec = std::vector<size_t>();
    posvec.push_back(0);
    posvec.push_back(1799);
    auto dec_tpl = std::make_tuple(posvec, FeatCalcParamSet(),
      EThresholdSelection::both, std::make_pair(0, 0));
    auto pttit = PatchToImageCoordinateTransformer(30, 30, 2, 40, 40, true,
                                                   10, 10);
    pttit(static_cast<void*>(&dec_tpl));
    BOOST_CHECK_EQUAL(std::get<0>(dec_tpl)[0], 410);
    BOOST_CHECK_EQUAL(std::get<0>(dec_tpl)[1], 3199);
}

#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Serialization_CoordTransformer) {
  auto pttitp = std::shared_ptr<PatchToImageCoordinateTransformer>(
    new PatchToImageCoordinateTransformer(30, 30, 2, 40, 40, true));
  auto sres = serialize_deserialize(pttitp);
  BOOST_CHECK(*pttitp == *sres);
}
#endif

//---------------------------------------------------------------------------//
// PatchSampleManager & ISampleManager

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_registration) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(1, hsm, 1);
  BOOST_CHECK_EXCEPTION(
    (SubsamplingDataProvider<uint16_t, int16_t>(1, hsm, 1)),
    Fertilized_Exception, [](Fertilized_Exception const &e){return true;});
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_ensure_available) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(2, hsm, 1);
  // Check the samples are empty.
  auto &samples = *sdp.get_samples();
  for (int i = 0; i < 4; ++i) {
    BOOST_CHECK(samples[i].data == nullptr);
    BOOST_CHECK(samples[i].annotation == nullptr);
  }
  // Load the first two elements.
  auto el_vec = std::vector<size_t>();
  el_vec.push_back(0);
  el_vec.push_back(1);
  hsm -> ensure_available(el_vec);
  // Check these elements for availability.
  bool all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= samples[0].data[i] == im_dta.patch_vec->operator[](0)[i];
    all_elems_correct &= samples[1].data[i] == im_dta.patch_vec->operator[](1)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(samples[0].annotation[0] == 1);
  BOOST_CHECK(samples[0].annotation[1] == 2);
  BOOST_CHECK(samples[0].annotation[2] == 2);
  BOOST_CHECK(samples[1].annotation[0] == 1);
  BOOST_CHECK(samples[1].annotation[1] == -1);
  BOOST_CHECK(samples[1].annotation[2] == -1);
  // Rest empty.
  for (int i = 2; i < 4; ++i) {
    BOOST_CHECK(samples[i].data == nullptr);
    BOOST_CHECK(samples[i].annotation == nullptr);
  }
  // Load the second two elements.
  el_vec.clear();
  el_vec.push_back(2);
  el_vec.push_back(3);
  hsm -> ensure_available(el_vec);
  // Check these elements for availability.
  all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= samples[2].data[i] == im_dta.patch_vec->operator[](2)[i];
    all_elems_correct &= samples[3].data[i] == im_dta.patch_vec->operator[](3)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(samples[2].annotation[0] == 0);
  BOOST_CHECK(samples[2].annotation[1] == 0);
  BOOST_CHECK(samples[2].annotation[2] == 0);
  BOOST_CHECK(samples[3].annotation[0] == 0);
  BOOST_CHECK(samples[3].annotation[1] == 0);
  BOOST_CHECK(samples[3].annotation[2] == 0);
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_overload) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(1, hsm, 1);
  // Check the samples are empty.
  auto &samples = *sdp.get_samples();
  for (int i = 0; i < 4; ++i) {
    BOOST_CHECK(samples[i].data == nullptr);
    BOOST_CHECK(samples[i].annotation == nullptr);
  }
  // Load the first two elements even though only 1 may be loaded.
  auto el_vec = std::vector<size_t>();
  el_vec.push_back(0);
  el_vec.push_back(1);
  hsm -> ensure_available(el_vec);
  // Check these elements for availability.
  bool all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= samples[0].data[i] == im_dta.patch_vec->operator[](0)[i];
    all_elems_correct &= samples[1].data[i] == im_dta.patch_vec->operator[](1)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(samples[0].annotation[0] == 1);
  BOOST_CHECK(samples[0].annotation[1] == 2);
  BOOST_CHECK(samples[0].annotation[2] == 2);
  BOOST_CHECK(samples[1].annotation[0] == 1);
  BOOST_CHECK(samples[1].annotation[1] == -1);
  BOOST_CHECK(samples[1].annotation[2] == -1);
  // Rest empty.
  for (int i = 2; i < 4; ++i) {
    BOOST_CHECK(samples[i].data == nullptr);
    BOOST_CHECK(samples[i].annotation == nullptr);
  }
  // Load the third element.
  el_vec.clear();
  el_vec.push_back(2);
  hsm -> ensure_available(el_vec);
  // Check this element for availability.
  all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= samples[2].data[i] == im_dta.patch_vec->operator[](2)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(samples[2].annotation[0] == 0);
  BOOST_CHECK(samples[2].annotation[1] == 0);
  BOOST_CHECK(samples[2].annotation[2] == 0);
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_ensure_available_s) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(2, hsm, 1);
  // Check the samples are empty.
  auto &samples = *sdp.get_samples();
  for (int i = 0; i < 4; ++i) {
    BOOST_CHECK(samples[i].data == nullptr);
    BOOST_CHECK(samples[i].annotation == nullptr);
  }
  // Load the first element.
  hsm -> ensure_available(0);
  // Check these elements for availability.
  bool all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= samples[0].data[i] == im_dta.patch_vec->operator[](0)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(samples[0].annotation[0] == 1);
  BOOST_CHECK(samples[0].annotation[1] == 2);
  BOOST_CHECK(samples[0].annotation[2] == 2);
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_load_sample) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(2, hsm, 1);
  auto &samples = *sdp.get_samples();

  uint16_t *tmp = new uint16_t[300];
  int16_t *anntmp = new int16_t[3];
  hsm -> load_sample(0, const_cast<Sample<uint16_t, int16_t>*>(&samples[0]), tmp, anntmp);
  bool all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= tmp[i] == im_dta.patch_vec->operator[](0)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Annotations.
  BOOST_CHECK(anntmp[0] == 1);
  BOOST_CHECK(anntmp[1] == 2);
  BOOST_CHECK(anntmp[2] == 2);
  // References.
  BOOST_CHECK(samples[0].annotation == anntmp);
  BOOST_CHECK(samples[0].data == tmp);
  BOOST_CHECK(samples[0].data_step == 1);
  // Cleanup.
  delete[](tmp);
  delete[](anntmp);
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_get_leaf) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  auto sdp = SubsamplingDataProvider<uint16_t, int16_t>(2, hsm, 1);
  auto fsp = std::shared_ptr<VolumeFeatureSelectionProvider>(
    new VolumeFeatureSelectionProvider(2, 10, 10, 3, 2, 1));
  auto dsc = std::shared_ptr<DifferenceSurfaceCalculator<uint16_t, int16_t, int16_t>>(
    new DifferenceSurfaceCalculator<uint16_t, int16_t, int16_t>());
  auto gf = EntropyGainFixture<float>();
  auto to = std::shared_ptr<ClassificationThresholdOptimizer<uint16_t, int16_t, int16_t>>(
    new ClassificationThresholdOptimizer<uint16_t, int16_t, int16_t>(true,
                                                                     2,
                                                                     gf.pent2gain,
                                                                     1E-7f,
                                                                     3));
  auto clm = std::make_shared<ThresholdDecider<uint16_t, int16_t, int16_t>>(fsp, dsc, to, 0);
  auto lm = std::make_shared<HoughLeafManager<uint16_t, int16_t>>(2, 2);
  Tree<uint16_t, int16_t, int16_t,
    std::pair<float, std::shared_ptr<std::vector<int16_t>>>,
    std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>> tree(10, 1, 2, clm, lm);
  auto node_predictor_func = [&tree](const uint16_t *dta,
                                     const size_t &step,
                                     const size_t start_node,
                                     const std::function<void(void*)> &tf) {
                                return tree.predict_leaf(dta, step, start_node, tf);
                              };
  // Check for empty tree.
  for (size_t i = 0; i < 4; ++i)
    BOOST_REQUIRE_EQUAL(hsm -> get_leaf(i, node_predictor_func), static_cast<size_t>(0));
  // Check for grown tree.
  tree.fit_dprov(&sdp);
  for (size_t i = 0; i < 4; ++i)
    BOOST_REQUIRE_EQUAL(hsm -> get_leaf(i, node_predictor_func),
                        tree.predict_leaf(im_dta.patch_vec -> at(i), 1));
}

BOOST_AUTO_TEST_CASE(Correctness_PatchSampleManager_extract_patch) {
  auto im_dta = ImageDataFixture<uint16_t, int16_t>();
  auto hsm = std::shared_ptr<PatchSampleManager<uint16_t, int16_t>>(
    new PatchSampleManager<uint16_t, int16_t>(im_dta.images,
                                              im_dta.patch_desc_arr,
                                              2,
                                              3,
                                              10,
                                              10));
  uint16_t *tmp = new uint16_t[300];
  hsm -> extract_patch(im_dta.image_ptrs_vec -> at(0),
                       tmp,
                       10,
                       10,
                       3,
                       10,
                       10,
                       40,
                       40);
  bool all_elems_correct = true;
  for (int i = 0; i < 300; ++i) {
    if (!all_elems_correct) break;
    all_elems_correct &= tmp[i] == im_dta.patch_vec->operator[](0)[i];
  }
  BOOST_CHECK(all_elems_correct);
  // Cleanup.
  delete[](tmp);
}
BOOST_AUTO_TEST_SUITE_END();