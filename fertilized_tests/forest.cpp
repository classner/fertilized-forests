// Author: Christoph Lassner.
#include <fertilized/global.h>

#include <random>
#include "boost/test/unit_test.hpp"
#include "timeit.h"
//
#include <fertilized/fertilized.h>

#include "setup.h"
//#include "fertilized/threshold_optimizer.h"
//#include "fertilized/serialization.h"
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <memory>
//
//
//#include "fertilized/forest.h"
//#include "fertilized/trees.h"
//#include "fertilized/leafs.h"
//#include "fertilized/classifiers.h"
//#include "fertilized/features.h"
//#include "fertilized/splitting_strategy.h"
//#include "fertilized/data_providers.h"
//
using namespace fertilized;
//
//
//struct ForestDataFixture {
//  std::shared_ptr<int> data;
//  std::shared_ptr<unsigned int> annotations;
//
//  ForestDataFixture() {
//    data = std::shared_ptr<int>(new int[100], []( int *p ) { delete[] p; } );
//    annotations = std::shared_ptr<unsigned int>(new unsigned int[10], []( unsigned int *p ) { delete[] p; } );
//    std::iota(data.get(), data.get() + 100, 0);
//    std::iota(annotations.get(), annotations.get() + 10, 0);
//  };
//};
//
//typedef std::shared_ptr<IClassifierManager<int, int, unsigned int>> class_man_ptr_t;
//typedef std::shared_ptr<ILeafManager<int, unsigned int, std::vector<float>, std::vector<float>>> leaf_man_ptr_t;
//
//typedef UnchangedDataProvider<int, unsigned int> data_prov_t;
//typedef Tree<int, int, unsigned int, std::vector<float>, std::vector<float>> tree_t;
//typedef Forest<int, int, unsigned int, std::vector<float>, std::vector<float>> forest_t;
//typedef ITraining<int, int, unsigned int, std::vector<float>, std::vector<float>> training_t;
//typedef ClassicTraining<int, int, unsigned int, std::vector<float>, std::vector<float>> ctraining_t;
//typedef EqualSplittingStrategy<int, int, unsigned int, std::vector<float>, std::vector<float>> esplit_str_t;
//typedef LocalExecutionStrategy<int, int, unsigned int, std::vector<float>, std::vector<float>> lexec_strat_t;
//
BOOST_AUTO_TEST_SUITE(Correctness_Forests);

BOOST_AUTO_TEST_CASE(Correctness_Forests_threaded_prediction) {
  std::mt19937 rng;
  rng.seed(1);
  auto dist_float = std::normal_distribution<float>(0., 1.);
  auto dist_uint = std::uniform_int_distribution<uint>(0, 1);
  auto s = Soil<>();
  auto tf = s.StandardClassificationForest(2, 3);
  Array<float, 2, 2> data = allocate(100, 3);
  auto dptr = &data[0][0];
  for (size_t i = 0; i < 300; ++i) {
      *(dptr++) = dist_float(rng);
  }
  Array<uint, 2, 2> annotation = allocate(100, 1);
  auto aptr = &annotation[0][0];
  for (size_t i = 0; i < 100; ++i) {
      *(aptr++) = dist_uint(rng);
  }
  tf -> fit(data, annotation);
  // Get results serially.
  auto res_serial = tf -> predict(data);
  // Get results in parallel.
  auto res_parallel = tf -> predict(data, 2);
  BOOST_CHECK(all(equal(res_serial, res_parallel)));
  //auto timestruct = PredictTimer<Forest<float, float, uint, std::vector<float>, std::vector<float>>, Array<float, 2, 2>>(tf.get(), &data);
  //float time = Utility::timeit<std::chrono::nanoseconds>(&timestruct, false, 3, 2);
  //std::cout << time;
};


//
//BOOST_FIXTURE_TEST_CASE(Correctness_Forest_Constructor, ForestDataFixture) {
//  auto classifier_managers = std::vector<class_man_ptr_t>(2);
//  auto leaf_managers = std::vector<leaf_man_ptr_t>(2);
//
//  for(size_t i = 0; i < 2; ++i) {
//    auto fsp = std::shared_ptr<IFeatureSelectionProvider>(
//                    new StandardFeatureSelectionProvider(5, 1, 10, 10));
//    auto fc = std::shared_ptr<IdentityFeatureCalculator<int, unsigned int>>(
//                        new IdentityFeatureCalculator<int, unsigned int>());
//    auto gc = std::shared_ptr<IGainCalculator<float>>(
//      new EntropyGain<float>(
//        std::shared_ptr<ShannonEntropy<float>>(new ShannonEntropy<float>())));
//    
//    auto to = std::shared_ptr<IThresholdOptimizer<int, int, unsigned int>>(
//    new ClassificationThresholdOptimizer<int, int>(true, 10, std::move(gc)));
//
//    classifier_managers[i] = class_man_ptr_t(
//      new ThresholdClassifier<int, int, unsigned int>(std::move(fsp), std::move(fc), std::move(to)));
//
//    leaf_managers[i] = leaf_man_ptr_t(new ClassificationLeafManager<int>(10));
//  }
//
//  std::shared_ptr<esplit_str_t> st(new esplit_str_t());
//  std::shared_ptr<training_t> t(new ctraining_t(std::move(st)));
//
//  std::shared_ptr<IForestDataProvider<int, unsigned int>> fdt =
//    std::make_shared<UnchangedFDataProvider<int, unsigned int>>(
//              data, annotations, 10, 10, true);
//
//  auto est = std::shared_ptr<lexec_strat_t>(new lexec_strat_t());
//
//  auto f1 = std::shared_ptr<forest_t>(
//    new forest_t(20, 1, 2, 2, classifier_managers, leaf_managers, t));
//  f1 -> fit(std::move(fdt), est.get());
//
//  std::vector<int> testv(10);
//  auto result = f1 -> predict(testv);
//
//
//  std::stringstream ss;
//  {
//
////    auto foo = std::shared_ptr<IGainCalculator<float>>(
////      new EntropyGain<float>(std::make_shared<InducedPEntropy<float>>(3)));
//    boost::archive::text_oarchive oa(ss);
//    fertilized::register_fertilized_objects(oa);
//    oa << f1;
//  }
//////  std::cout << ss;
//  {
//    std::shared_ptr<forest_t> f2;
////    std::shared_ptr<IGainCalculator<float>> foo2;
//    boost::archive::text_iarchive is(ss);
//    fertilized::register_fertilized_objects(is);
//    is >> f2;
//    auto result2 = f2 -> predict(testv);
//  }
//
//};
//
BOOST_AUTO_TEST_SUITE_END();
