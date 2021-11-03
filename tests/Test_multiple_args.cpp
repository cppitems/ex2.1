#include <cstdlib>
#include <iostream>
#include <array>

#include <measureTime.hpp>

using T = double;

// some random functions doing something with wildly different parameters
void add2(T& a, T b) {
  a += b;
}

void add3(T& a, float& b, int c) {
  a += b * c;
}

void add5(T&a, T b, const T c, const T& d, int e) {
  a += (b / (c + d)) * e;
}

void add10(T&a, const T b, const T& c, const T d, int e, float f, char g, float& h, std::array<T, 3>& i, bool j) {
  if(j) {
    a *= b - c + d * (f * h) / (g * i[2]);
  } else {
    a += (b / (c + d)) * e + f / h - g * i[0];
  }
}

int main() {

  double a = 1.;
  double b = 3.;
  float c = 0.1f;
  std::array<T, 3> vec = {1, 1, 1};
  // normal function calls
  add2(a, b);

  // function calls to measure the runtime
  double duration = measureTime(add2, a, b);
  std::cout << "add2 took " << duration << " ms" << std::endl;

  duration = measureTime(add3, a, c, 4);
  std::cout << "add3 took " << duration << " ms" << std::endl;

  duration = measureTime(add5, a, 3.1, 12., b, 11);
  std::cout << "add5 took " << duration << " ms" << std::endl;

  duration = measureTime(add10, a, 4.2, b, 2.7, 3, 0.4f, 'b', c, vec, true);
  std::cout << "add10 took " << duration << " ms" << std::endl;

  return EXIT_SUCCESS;
}
