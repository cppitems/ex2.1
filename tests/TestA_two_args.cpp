#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <measureTime.hpp>

void add(double& a, double& b) {
  a += b;
}

int main() {

  double a = 1.;
  double b = 3.;
  // normal function call
  add(a, b);

  // function call to measure the runtime
  double duration = measureTime(add, a, b);

  std::cout << "Adding took " << duration << " ms" << std::endl;

  return EXIT_SUCCESS;
}
