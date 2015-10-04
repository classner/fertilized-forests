/* Author: Christian Diller. */
#include <fertilized/fertilized.h>
#include <iostream>

#include <random>

using namespace fertilized;

// This file is based on the 'Custom tutorial'
// from the examples section of www.fertilized-forests.org.

Array<float,1,1> point_on_circle(float phi, float r) {
    Array<float,1,1> out = allocate(2);
    out[0] = std::cos(phi) * r; out[1] = std::sin(phi) * r;
    return out;
}

std::pair<Array<float,2,2>, Array<uint,2,2>> make_spiral(
  uint n_samples_per_arm=100, uint n_arms=2, float noise=0.25) {
#define M_PI 3.14159265358979323846
    Array<float,1,1> starting_angles = allocate(n_arms);
    for(float i = 0.f; i < n_arms; ++i) {
        starting_angles[i] = i * 2.f * static_cast<float>(M_PI) /
                                       static_cast<float>(n_arms);
    }
    Array<float,2,2> points = allocate(n_arms * n_samples_per_arm, 2);
    Array<uint,2,2> ids = allocate(n_arms * n_samples_per_arm, 1);
    float maxpifac = 1.7f;
    for(uint arm_id = 0U; arm_id < n_arms; ++arm_id) {
        float angle = starting_angles[arm_id];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.f, maxpifac);
        for(uint point_id = 0U; point_id < n_samples_per_arm; ++point_id) {
            float angle_add = dis(gen);
            Array<float,1,1> position = point_on_circle(
              angle + angle_add*static_cast<float>(M_PI),
              1.f + 2.f*angle_add);
            std::normal_distribution<> d(0.0, noise * angle_add);
            position[0] += d(gen); position[1] += d(gen);
            points[arm_id * n_samples_per_arm + point_id] = position;
            ids[arm_id * n_samples_per_arm + point_id][0] = arm_id;
        }
    }
    return std::make_pair(points, ids);
}

double f1_score(Array<uint, 2, 2>& truth, Array<double, 2, 2>& prediction) {
    double values[4]; //tn, fp, fn, tp
    values[0] = 0.0; values[1] = 0.0; values[2] = 0.0; values[3] = 0.0;
    for(size_t i = 0; i < truth.size(); ++i) {
        values[truth[i][0]*2U +
          std::min(static_cast<uint>(prediction[i][1] - prediction[i][0] + 1.0),
                   1U)]++;
    }
    double precision = values[3] / (values[3] + values[1]);
    double recall = values[3] / (values[3] + values[2]);
    return 2.0 * (precision * recall) / (precision + recall);
}

int main() {
    // We will use make_spiral to generate some sample data
    std::cout << "Generating training data..." << std::endl;
    auto X_Y = make_spiral(25);
    Array<float, 2, 2> X = X_Y.first;
    Array<uint, 2, 2> Y = X_Y.second;

    auto soil = Soil<float,
                     float,
                     uint,
                     Result_Types::probabilities>();

    uint depth = 12;
    uint n_trees = 200;
    // These variables will contain the classifiers and leaf managers for each
    // tree.
    decltype(soil.idecider_vec_t()) cls; // Classifiers
    decltype(soil.ileafmanager_vec_t()) lm;  // Leaf managers

    for (uint i = 0; i < n_trees; ++i) {
        auto stdFeatureSelect = soil.StandardFeatureSelectionProvider(
          1, 2, 2, 2, 1+i);
        auto linSurface = soil.LinearSurfaceCalculator(400, 2, 1+i);

        // RandomizedClassificationThresholdOptimizer
        auto shannon = soil.ShannonEntropy();
        auto entropyGain = soil.EntropyGain(shannon);
        auto rcto = soil.RandomizedClassificationThresholdOptimizer(
          1, 2, entropyGain, 0, 1, 1+i);

        // ThresholdDecider
        auto tClassifier = soil.ThresholdDecider(
          stdFeatureSelect, linSurface, rcto);

        // ClassificationLeafManager
        auto leafMgr = soil.ClassificationLeafManager(2);

        cls.push_back(tClassifier);
        lm.push_back(leafMgr);
    }

    // Choose the boosting algorithm, supported are Samme, Samme_R and AdaBoost
    auto algorithm = soil.Samme();
    auto training = soil.BoostedTraining(algorithm);

    auto forest = soil.Forest(depth, 1, 2, n_trees, cls, lm, training);

    std::cout << "Fitting forest..." << std::endl;
    forest->fit(X, Y);

    std::cout << std::endl;

    // First, generate new data and display raw prediction results
    std::cout << "Generating data..." << std::endl;
    auto new_X_Y = make_spiral(5);
    Array<float, 2, 2> new_X = new_X_Y.first;
    Array<uint, 2, 2> new_Y = new_X_Y.second;
    auto predictions = forest->predict(new_X);
    std::cout << "Forest predictions: " << std::endl;
    std::cout << predictions << std::endl << std::endl;

    // Generate more data and calculate F1 score from prediction results
    std::cout << "Generating data..." << std::endl;
    new_X_Y = make_spiral(100);
    new_X = new_X_Y.first; new_Y = new_X_Y.second;
    predictions = forest->predict(new_X);
    std::cout << "Prediction F1 score is "
              << f1_score(new_Y, predictions)
              << std::endl;
    return 0;
}
