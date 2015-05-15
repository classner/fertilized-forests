/* Author: Christian Diller. */
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
// Helper functions
double f1_score(Array<uint, 2, 2>& truth, Array<double, 2, 2>& prediction) {
    double values[4]; //tn, fp, fn, tp
    values[0] = 0.0; values[1] = 0.0; values[2] = 0.0; values[3] = 0.0;
    for(size_t i = 0; i < truth.size(); ++i)
        values[truth[i][0]*2U+static_cast<uint>(prediction[i][1]-prediction[i][0]+1.0)]++;
    double precision = values[3]/(values[3]+values[1]);
    double recall = values[3]/(values[3]+values[2]);
    return 2.0 * (precision*recall) / (precision+recall);
}

Array<float,1,1> point_on_circle(float phi, float r) {
    Array<float,1,1> out = allocate(2);
    out[0] = std::cos(phi) * r; out[1] = std::sin(phi) * r;
    return out;
}

std::pair<Array<float,2,2>, Array<uint,2,2>> make_spiral_fixed(uint n_samples_per_arm=1000, uint n_arms=2, float noise=0.1) {
#define M_PI 3.14159265358979323846
    Array<float,1,1> starting_angles = allocate(n_arms);
    for(float i = 0.f; i < n_arms; ++i)
        starting_angles[i] = i * 2.f * static_cast<float>(M_PI) / static_cast<float>(n_arms);
    Array<float,2,2> points = allocate(n_arms * n_samples_per_arm, 2);
    Array<uint,2,2> ids = allocate(n_arms * n_samples_per_arm, 1);
    for(uint arm_id = 0U; arm_id < n_arms; ++arm_id) {
        float angle = starting_angles[arm_id];
        for(uint point_id = 0U; point_id < n_samples_per_arm; ++point_id) {
            float angle_add = 1.7f/static_cast<float>(point_id+1);
            Array<float,1,1> position = point_on_circle(angle+angle_add*static_cast<float>(M_PI), 1.f + 2.f*angle_add);
            position[0] += -0.152176*noise; position[1] += 0.141444*noise;
            points[arm_id * n_samples_per_arm + point_id] = position;
            ids[arm_id * n_samples_per_arm + point_id][0] = arm_id;
        }
    }
    return std::make_pair(points, ids);
}

//---------------------------------------------------------------------------//
// AdaBoost.M2 boosting implementation
BOOST_AUTO_TEST_CASE(Correctness_Boosting_Result_AdaBoost) {
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    auto X_Y = make_spiral_fixed(1000, 2, 0.5);
    Array<float, 2, 2> X = X_Y.first;
    Array<uint, 2, 2> Y = X_Y.second;

    uint n_trees = 200;
    decltype(soil.idecider_vec_t()) cls;
    decltype(soil.ileafmanager_vec_t()) lm;

    for (uint i = 0U; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 1, 2, 2, 1+i);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, soil.EntropyGain(soil.ShannonEntropy()), 0, 1, 1+i);
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, soil.AlignedSurfaceCalculator(), rcto);
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(1, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.AdaBoost()));

    forest->fit(X, Y);

    auto new_X_Y = make_spiral_fixed(100, 2, 0.75);
    Array<float, 2, 2> new_X = new_X_Y.first;
    Array<uint, 2, 2> new_Y = new_X_Y.second;

    auto predictions = forest->predict(new_X);

#ifdef _WIN32
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 98000);
#else
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 98000);
#endif
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
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    auto X_Y = make_spiral_fixed(1000, 2, 0.5);
    Array<float, 2, 2> X = X_Y.first;
    Array<uint, 2, 2> Y = X_Y.second;

    uint n_trees = 200;
    decltype(soil.idecider_vec_t()) cls;
    decltype(soil.ileafmanager_vec_t()) lm;

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 1, 2, 2, 1+i);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, soil.EntropyGain(soil.ShannonEntropy()), 0, 1, 1+i);
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, soil.AlignedSurfaceCalculator(), rcto);
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(1, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.Samme()));

    forest->fit(X, Y);

    auto new_X_Y = make_spiral_fixed(100, 2, 0.75);
    Array<float, 2, 2> new_X = new_X_Y.first;
    Array<uint, 2, 2> new_Y = new_X_Y.second;

    auto predictions = forest->predict(new_X);

#ifdef _WIN32
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 98492);
#else
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 98507);
#endif
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
    auto soil = Soil<float, float, uint, Result_Types::probabilities>();

    auto X_Y = make_spiral_fixed(1000, 2, 0.5);
    Array<float, 2, 2> X = X_Y.first;
    Array<uint, 2, 2> Y = X_Y.second;

    uint n_trees = 200;
    decltype(soil.idecider_vec_t()) cls;
    decltype(soil.ileafmanager_vec_t()) lm;

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(1, 1, 2, 2, 1+i);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(1, 2, soil.EntropyGain(soil.ShannonEntropy()), 0, 1, 1+i);
        auto tClassifier = soil.ThresholdDecider(stdFeatureSelect, soil.AlignedSurfaceCalculator(), rcto);
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    auto forest = soil.Forest(1, 1, 2, n_trees, cls, lm, soil.BoostedTraining(soil.Samme_R()));

    forest->fit(X, Y);

    auto new_X_Y = make_spiral_fixed(100, 2, 0.75);
    Array<float, 2, 2> new_X = new_X_Y.first;
    Array<uint, 2, 2> new_Y = new_X_Y.second;

    auto predictions = forest->predict(new_X);

#ifdef _WIN32
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 97979);
#else
    BOOST_CHECK_EQUAL(static_cast<uint>(f1_score(new_Y, predictions)*100000.f), 97979);
#endif
}

BOOST_AUTO_TEST_SUITE_END();
