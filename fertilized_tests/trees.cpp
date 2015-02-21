// Author: Christoph Lassner.
#include <fertilized/global.h>

#include <random>
#include "boost/test/unit_test.hpp"
#include "timeit.h"
#include "setup.h"
//
#include <fertilized/fertilized.h>
//
//#include "fertilized/threshold_optimizer.h"
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include "fertilized/serialization.h"
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//#include "fertilized/trees.h"
//#include "fertilized/leafs.h"
//#include "fertilized/classifiers.h"
//#include "fertilized/features.h"
//#include "fertilized/data_providers.h"
//#include "fertilized/threshold_optimizer.h"
//
//#include <random>
//
//// include headers that implement a archive in simple text format
//
////int t = dummy::bogus::bogus_method();
//
using namespace fertilized;

//struct IntExampleDataFixture {
//  std::shared_ptr<int> data;
//  std::shared_ptr<unsigned int> annotations;
//
//  IntExampleDataFixture() {
//    data = std::shared_ptr<int>(new int[100], []( int *p ) { delete[] p; } );
//    annotations = std::shared_ptr<unsigned int>(new unsigned int[10], []( unsigned int *p ) { delete[] p; } );
//    std::iota(data.get(), data.get() + 100, 0);
//    std::iota(annotations.get(), annotations.get() + 10, 0);
//  };
//};
//
//typedef std::unique_ptr<IClassifierManager<int, int, int>> class_man_ptr_t;
//typedef std::unique_ptr<ILeafManager<int, int, float, float>> leaf_man_ptr_t;
////typedef std::unique_ptr<IFeatureManager<int, int, int>> feat_man_ptr_t;
//typedef UnchangedDataProvider<int, unsigned int> data_prov_t;
//typedef Tree<int, int, int, float, float> tree_t;
//
//
BOOST_AUTO_TEST_SUITE(Correctness_Trees);

BOOST_AUTO_TEST_CASE(Correctness_Trees_Basic) {
  auto s = Soil<>();
  auto tf = s.StandardClassificationForest(2, 3);
  Array<float, 2, 2> data = allocate(10, 3);
  data.deep() = 1.f;
  Array<uint, 2, 2> annotation = allocate(10, 1);
  annotation.deep() = 1;
  annotation[view(0,5)] = 0;
  tf -> fit(data, annotation);
#ifdef SERIALIZATION_ENABLED
  tf -> save("tmp.txt");
  auto rtf = s.ForestFromFile("tmp.txt");
  BOOST_REQUIRE(*(tf.get()) == *(rtf.get()));
  auto tt = s.StandardClassificationTree(2, 10, 5, 2, 2);
  tt -> save("tmp.txt");
  auto rtt = s.TreeFromFile("tmp.txt");
  BOOST_REQUIRE(*(tt.get()) == *(rtt.get()));
#endif
};

BOOST_AUTO_TEST_CASE(Correctness_Trees_threaded_prediction) {
  std::mt19937 rng;
  rng.seed(1);
  auto dist_float = std::normal_distribution<float>(0., 1.);
  auto dist_uint = std::uniform_int_distribution<uint>(0, 1);
  auto s = Soil<>();
  auto tf = s.StandardClassificationTree(2, 3);
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
  //auto timestruct = PredictTimer<Tree<float, float, uint, std::vector<float>, std::vector<float>>, Array<float, 2, 2>>(tf.get(), &data);
  //float time = Utility::timeit<std::chrono::nanoseconds>(&timestruct, false, 3, 2);
  //std::cout << time;
};

//
//BOOST_FIXTURE_TEST_CASE(Correctness_Tree_Constructor, IntExampleDataFixture) {
//  //FORCE_LINK_THAT(fertilized_SERIALIZATION_CPP);
//  //int r =  testfunc(5);
//
//  auto fsp1 = std::unique_ptr<IFeatureSelectionProvider>(
//    new StandardFeatureSelectionProvider(5, 1, 10, 10));
//  std::unique_ptr<IFeatureCalculator<int, int, unsigned int>> fc1 =
//      std::unique_ptr<IdentityFeatureCalculator<int, unsigned int>>(
//    new IdentityFeatureCalculator<int, unsigned int>());
//
//  auto gc1 = std::unique_ptr<IGainCalculator<float>>(
//    new EntropyGain<float>(
//      std::unique_ptr<ShannonEntropy<float>>(new ShannonEntropy<float>())));
//
//
//  std::unique_ptr<IThresholdOptimizer<int, int, unsigned int>> to1 =
//    std::unique_ptr<ClassificationThresholdOptimizer<int, int>>(
//    new ClassificationThresholdOptimizer<int, int>(true, 10, std::move(gc1)));
//
//  auto c1 = std::unique_ptr<IClassifierManager<int, int, unsigned int>>(
//    new ThresholdClassifier<int, int, unsigned int>(std::move(fsp1), std::move(fc1), std::move(to1)));
//
//
//  auto l1 = std::unique_ptr<ILeafManager<int, unsigned int, std::vector<float>, std::vector<float>>>(
//    new ClassificationLeafManager<int>(10));
//
//  std::shared_ptr<IDataProvider<int, unsigned int>> d1 = std::make_shared<UnchangedDataProvider<int, unsigned int>>(data, annotations, 10, 10, true);
//
//  auto t1 = std::make_shared<Tree<int, int, unsigned int, std::vector<float>, std::vector<float>>>
//              (20, 1, 2, std::move(c1), std::move(l1));
//  t1 -> fit(d1.get());
//  t1 -> set_weight(0.3f);
//
//  std::vector<int> testv(10);
//  auto result = t1 -> predict(testv);
//
//    std::stringstream ss;
//  {
//    auto foo = std::shared_ptr<IThresholdOptimizer<int, int, unsigned int>>(
//          new ClassificationThresholdOptimizer<int, int>(
//               true, 2, std::shared_ptr<IGainCalculator<float>>(
//                 new EntropyGain<float>(std::make_shared<InducedPEntropy<float>>(3)))));
//
//    //auto foo = std::shared_ptr<IGainCalculator<float>>(
//    //  new EntropyGain<float>(std::make_shared<InducedPEntropy<float>>(3)));
//    boost::archive::text_oarchive oa(ss);
//    fertilized::register_fertilized_objects(oa);
//    oa << t1;
//  }
////  std::cout << ss;
//  {
//    std::shared_ptr<Tree<int, int, unsigned int, std::vector<float>, std::vector<float>>> foo2;
//    //std::shared_ptr<IGainCalculator<float>> foo2;
//    boost::archive::text_iarchive is(ss);
//    fertilized::register_fertilized_objects(is);
//    is >> foo2;
//    float test = foo2 -> get_weight();
//    auto result2 = foo2 -> predict(testv);
//  }
//};
//
BOOST_AUTO_TEST_SUITE_END();
