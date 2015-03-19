// Author: Christian Diller
#include <fertilized/fertilized.h>

#include "boost/test/unit_test.hpp"

#include "setup.h"

using namespace fertilized;

BOOST_AUTO_TEST_SUITE(Correctness_Boosting);

#ifdef SERIALIZATION_ENABLED
BOOST_AUTO_TEST_CASE(Correctness_Boosting_Serialization) {
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();
    uint n_trees = 200;
    std::vector<std::shared_ptr<fertilized::Tree<float, float, uint, std::vector<float>, std::vector<float>>>> adaBoostTrees;
    for (uint i = 0; i < n_trees; ++i)
        adaBoostTrees.push_back(soil.StandardClassificationTree(
                    2, // number of classes
                    2, // number of features
                    1)); //Max depth

    auto adaBoostForest = soil.ForestFromTrees(adaBoostTrees, soil.BoostedTraining(soil.AdaBoost()));
    auto adaBoostDeserialized = serialize_deserialize(adaBoostForest);
    BOOST_REQUIRE(*adaBoostForest == *adaBoostDeserialized);

    std::vector<std::shared_ptr<fertilized::Tree<float, float, uint, std::vector<float>, std::vector<float>>>> sammeTrees;
    for (uint i = 0; i < n_trees; ++i)
        sammeTrees.push_back(soil.StandardClassificationTree(
                    2, // number of classes
                    2, // number of features
                    1)); //Max depth

    auto sammeForest = soil.ForestFromTrees(sammeTrees, soil.BoostedTraining(soil.Samme()));
    auto sammeDeserialized = serialize_deserialize(sammeForest);
    BOOST_REQUIRE(*sammeForest == *sammeDeserialized);

    std::vector<std::shared_ptr<fertilized::Tree<float, float, uint, std::vector<float>, std::vector<float>>>> sammeRTrees;
    for (uint i = 0; i < n_trees; ++i)
        sammeRTrees.push_back(soil.StandardClassificationTree(
                    2, // number of classes
                    2, // number of features
                    1)); //Max depth

    auto sammeRForest = soil.ForestFromTrees(sammeRTrees, soil.BoostedTraining(soil.Samme_R()));
    auto sammeRDeserialized = serialize_deserialize(sammeRForest);
    BOOST_REQUIRE(*sammeRForest == *sammeRDeserialized);
}
#endif

//---------------------------------------------------------------------------//
// AdaBoost.M2 boosting implementation
BOOST_AUTO_TEST_CASE(Correctness_Boosting_Result_AdaBoost) {
    Array<float, 2, 2> X;
    Array<uint, 2, 2> Y;
    X = allocate(10, 2);
    X.deep() = 1.f;
    X[view(0, 5)] = 0.f;
    Y = allocate(10, 1);
    Y.deep() = 1;
    Y[view(0, 5)] = 0;

    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    uint depth = 1;
    uint n_trees = 200;
    // These variables will contain the classifiers and leaf managers for each
    // tree.
    decltype(soil.idecider_vec_t()) cls; // Classifiers
    decltype(soil.ileafmanager_vec_t()) lm;  // Leaf managers

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 2, 2, 2, 1+i);
        auto linSurface = soil.LinearSurfaceCalculator(400, 2, 1+i);

        // RandomizedClassificationThresholdOptimizer
        auto shannon = soil.ShannonEntropy();
        auto entropyGain = soil.EntropyGain(shannon);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, entropyGain, 0, 1, 1+i);

        // ThresholdDecider
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, linSurface, rcto);

        // ClassificationLeafManager
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(depth, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.AdaBoost()));

    forest->fit(X, Y);

    Array<float, 2, 2> new_data = allocate(10, 2);
    float *raw_data = new_data.getData();
    std::iota(raw_data, raw_data+10, 0.f);
    std::iota(raw_data+10, raw_data+20, 0.f);

    auto predictions = forest->predict(new_data);

    BOOST_REQUIRE(predictions[0][0] > predictions[0][1]);
    BOOST_REQUIRE(predictions[1][0] < predictions[1][1]);
    BOOST_REQUIRE(predictions[2][0] < predictions[2][1]);
    BOOST_REQUIRE(predictions[3][0] < predictions[3][1]);
    BOOST_REQUIRE(predictions[4][0] < predictions[4][1]);
    BOOST_REQUIRE(predictions[5][0] > predictions[5][1]);
    BOOST_REQUIRE(predictions[6][0] < predictions[6][1]);
    BOOST_REQUIRE(predictions[7][0] < predictions[7][1]);
    BOOST_REQUIRE(predictions[8][0] < predictions[8][1]);
    BOOST_REQUIRE(predictions[9][0] < predictions[9][1]);
}

//---------------------------------------------------------------------------//
// SAMME boosting implementation
BOOST_AUTO_TEST_CASE(Correctness_Boosting_InputCheck_Samme) {
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();
    BOOST_CHECK_THROW(soil.Samme(-1.f), Fertilized_Exception);
    BOOST_CHECK_THROW(soil.Samme(0.f), Fertilized_Exception);
    BOOST_CHECK_THROW(soil.Samme(2.f), Fertilized_Exception);
}

BOOST_AUTO_TEST_CASE(Correctness_Boosting_Result_Samme) {
    Array<float, 2, 2> X;
    Array<uint, 2, 2> Y;
    X = allocate(10, 2);
    X.deep() = 1.f;
    X[view(0, 5)] = 0.f;
    Y = allocate(10, 1);
    Y.deep() = 1;
    Y[view(0, 5)] = 0;

    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    uint depth = 1;
    uint n_trees = 200;
    // These variables will contain the classifiers and leaf managers for each
    // tree.
    decltype(soil.idecider_vec_t()) cls; // Classifiers
    decltype(soil.ileafmanager_vec_t()) lm;  // Leaf managers

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 2, 2, 2, 1+i);
        auto linSurface = soil.LinearSurfaceCalculator(400, 2, 1+i);

        // RandomizedClassificationThresholdOptimizer
        auto shannon = soil.ShannonEntropy();
        auto entropyGain = soil.EntropyGain(shannon);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, entropyGain, 0, 1, 1+i);

        // ThresholdDecider
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, linSurface, rcto);

        // ClassificationLeafManager
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(depth, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.Samme()));

    forest->fit(X, Y);

    Array<float, 2, 2> new_data = allocate(10, 2);
    float *raw_data = new_data.getData();
    std::iota(raw_data, raw_data+10, 0.f);
    std::iota(raw_data+10, raw_data+20, 0.f);

    auto predictions = forest->predict(new_data);

    BOOST_REQUIRE(predictions[0][0] == predictions[0][1]);
    BOOST_REQUIRE(predictions[1][0] < predictions[1][1]);
    BOOST_REQUIRE(predictions[2][0] < predictions[2][1]);
    BOOST_REQUIRE(predictions[3][0] < predictions[3][1]);
    BOOST_REQUIRE(predictions[4][0] < predictions[4][1]);
    BOOST_REQUIRE(predictions[5][0] == predictions[5][1]);
    BOOST_REQUIRE(predictions[6][0] < predictions[6][1]);
    BOOST_REQUIRE(predictions[7][0] < predictions[7][1]);
    BOOST_REQUIRE(predictions[8][0] < predictions[8][1]);
    BOOST_REQUIRE(predictions[9][0] < predictions[9][1]);
}

//---------------------------------------------------------------------------//
// SAMME.R boosting implementation
BOOST_AUTO_TEST_CASE(Correctness_Boosting_InputCheck_Samme_R) {
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();
    BOOST_CHECK_THROW(soil.Samme_R(-1.f), Fertilized_Exception);
    BOOST_CHECK_THROW(soil.Samme_R(0.f), Fertilized_Exception);
    BOOST_CHECK_THROW(soil.Samme_R(2.f), Fertilized_Exception);
}

BOOST_AUTO_TEST_CASE(Correctness_Boosting_Result_Samme_R) {
    Array<float, 2, 2> X;
    Array<uint, 2, 2> Y;
    X = allocate(10, 2);
    X.deep() = 1.f;
    X[view(0, 5)] = 0.f;
    Y = allocate(10, 1);
    Y.deep() = 1;
    Y[view(0, 5)] = 0;

    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    uint depth = 1;
    uint n_trees = 200;
    // These variables will contain the classifiers and leaf managers for each
    // tree.
    decltype(soil.idecider_vec_t()) cls; // Classifiers
    decltype(soil.ileafmanager_vec_t()) lm;  // Leaf managers

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 2, 2, 2, 1+i);
        auto linSurface = soil.LinearSurfaceCalculator(400, 2, 1+i);

        // RandomizedClassificationThresholdOptimizer
        auto shannon = soil.ShannonEntropy();
        auto entropyGain = soil.EntropyGain(shannon);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, entropyGain, 0, 1, 1+i);

        // ThresholdDecider
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, linSurface, rcto);

        // ClassificationLeafManager
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(depth, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.Samme_R()));

    forest->fit(X, Y);

    Array<float, 2, 2> new_data = allocate(10, 2);
    float *raw_data = new_data.getData();
    std::iota(raw_data, raw_data+10, 0.f);
    std::iota(raw_data+10, raw_data+20, 0.f);

    auto predictions = forest->predict(new_data);

    BOOST_REQUIRE(predictions[0][0] == predictions[0][1]);
    BOOST_REQUIRE(predictions[1][0] < predictions[1][1]);
    BOOST_REQUIRE(predictions[2][0] < predictions[2][1]);
    BOOST_REQUIRE(predictions[3][0] < predictions[3][1]);
    BOOST_REQUIRE(predictions[4][0] < predictions[4][1]);
    BOOST_REQUIRE(predictions[5][0] == predictions[5][1]);
    BOOST_REQUIRE(predictions[6][0] < predictions[6][1]);
    BOOST_REQUIRE(predictions[7][0] < predictions[7][1]);
    BOOST_REQUIRE(predictions[8][0] < predictions[8][1]);
    BOOST_REQUIRE(predictions[9][0] < predictions[9][1]);
}

BOOST_AUTO_TEST_SUITE_END();
