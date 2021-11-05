#include <cstdlib>
#include <iostream>

#include <measureTime.hpp>

void add(double& a, double b) {
  a += b;
}

int main() {

  double a = 1.;
  // normal function call
  add(a, 3.);

  // function call to measure the runtime
  double duration = measureTime(add, a, 3.);

  std::cout << "Adding took " << duration << " ms" << std::endl;

  return EXIT_SUCCESS;
}
