#include <fertilized/fertilized.h>
#include <iostream>
using namespace fertilized;

// For detailed explanations to this file, see the 'Basic tutorial' in the
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
  std::cout << "X:" << std::endl;
  std::cout << X << std::endl;
  std::cout << "Y:" << std::endl;
  std::cout << Y << std::endl;

  auto soil = Soil<>();

  auto tree = soil.StandardClassificationTree(
              2, // number of classes
              2); // number of features
  tree -> fit(X, Y);

  Array<float, 2, 2> new_data = allocate(10, 2);
  float *raw_data = new_data.getData();
  std::iota(raw_data, raw_data+10, 0.f);
  std::iota(raw_data+10, raw_data+20, 0.f);
  std::cout << "New data:" << std::endl;
  std::cout << new_data << std::endl;
  Array<double, 2, 2> predictions = tree -> predict(new_data);

  std::cout << "Tree predictions: " << std::endl;
  std::cout << predictions << std::endl;

  auto forest = soil.StandardClassificationForest(
              2,  // number of classes,
              2); // number of features
  forest -> fit(X, Y);
  predictions = forest -> predict(new_data);
  std::cout << "Forest predictions: " << std::endl;
  std::cout << predictions << std::endl;
};