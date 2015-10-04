#include <fertilized/fertilized.h>
#include <iostream>
using namespace fertilized;

// For detailed explanations to this file, see the 'Regression tutorial' in the
// examples section of www.fertilized-forests.org.

int main() {
  Array<float, 2, 2> X;
  Array<float, 2, 2> Y;
  // We will use some simple data here:
  X = allocate(10, 2);
  X.deep() = 1.f;
  X[view(0, 5)] = 0.f;
  Y = allocate(10, 1);
  Y.deep() = 1.f;
  Y[view(0, 5)] = 0.f;

  auto soil = Soil<float,
                   float,
                   float,
                   Result_Types::regression>();

  uint input_dim = 2;
  uint n_trees = 5;
  uint max_depth = 2;
  uint n_thresholds = 2;
  auto forest = soil.StandardRegressionForest(input_dim,
                                              max_depth,
                                              input_dim,
                                              n_thresholds,
                                              n_trees);

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
