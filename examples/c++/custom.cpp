#include <fertilized/fertilized.h>
#include <iostream>

using namespace fertilized;

// For detailed explanations to this file, see the 'Custom tutorial' in the
// examples section of www.fertilized-forests.org.

int main() {
  Array<float, 2, 2> X;
  Array<uint, 2, 2> Y;
  // Instead of implementing
  // make_spiral(&X, &Y);
  // we will use some simple data here:
  X = allocate(10, 2);
  X.deep() = 1.f;
  X[view(0, 5)] = 0.f;
  Y = allocate(10, 1);
  Y.deep() = 1;
  Y[view(0, 5)] = 0;

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

  auto nb = soil.NoBagging();
  auto training = soil.ClassicTraining(nb);

  auto forest = soil.Forest(depth, 1, 2, n_trees, cls, lm, training);

  forest -> fit(X, Y);
  Array<float, 2, 2> new_data = allocate(10, 2);
  float *raw_data = new_data.getData();
  std::iota(raw_data, raw_data+10, 0.f);
  std::iota(raw_data+10, raw_data+20, 0.f);
  auto predictions = forest -> predict(new_data);
  std::cout << "Forest predictions: " << std::endl;
  std::cout << predictions << std::endl;
  return 0;
}
