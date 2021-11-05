#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include <measureTime.hpp>

template <typename T> void func1(std::vector<T> &a) {
  std::transform(std::begin(a), std::end(a), std::begin(a),
                 [](const T &item) { return std::sin(item); });
}

template <typename T> void func2(const std::vector<T> &a, std::vector<T> &res) {
  std::transform(std::begin(a), std::end(a), std::begin(res),
                 [](const T &item) { return std::sin(std::sin(item)); });
}

template <typename T> void func3(const std::vector<T> &a, std::vector<T> &res) {
  std::transform(a.begin(), a.end(), res.begin(), res.begin(),
                 [](const T &a, const T &b) { return std::sin(a) + std::sin(b); });
}

template <typename T>
void func4(const std::vector<T> &a, const std::vector<T> &b,
           std::vector<T> &res) {
  std::transform(a.begin(), a.end(), b.begin(), res.begin(),
                 [](const T &a, const T &b) { return std::sin(a) + std::sin(b); });
}

template <typename CTNR> void print(const CTNR &ctnr) {
  using value_type = typename CTNR::value_type;
  std::for_each(ctnr.begin(), ctnr.end(),
                [](const value_type &item) { std::cout << item << ", "; });
  std::cout << std::endl;
}

void outputTime(std::string funcCall, double t) {
  std::cout << std::left << std::setw(10) << "Call " << std::setw(50)
            << funcCall << " took " << t << " ms" << std::endl;
}

template <class T> void testTrackTime(const std::size_t size) {
  std::vector<T> vec1(size, 1.0);
  std::vector<T> vec2(size, 2.0);
  std::vector<T> vec3(size, 3.0);

  // using 'measureTime' from 'timer.hpp'
  double duration = 0.;
  duration = measureTime(func1<T>, vec1);
  outputTime("func1<T>, vec1", duration);

  duration = measureTime(func2<T>, vec1, vec2);
  outputTime("func2<T>, vec1, vec2", duration);

  duration = measureTime(func3<T>, vec1, vec2);
  outputTime("func3<T>, vec1, vec2", duration);

  duration = measureTime(func4<T>, std::vector<T>(size, 1.0), vec2, vec3);
  outputTime("func4<T>, std::vector<T>(size, 1.0), vec2, vec3", duration);
}

int main() {
  const std::size_t size = 5'000'000;

  std::cout << "using T = double;" << std::endl;
  testTrackTime<double>(size);

  std::cout << "using T = float;" << std::endl;
  testTrackTime<float>(size);

  {
    std::cout << "lambda function object" << std::endl;
    using T = double;
    auto lambda_fill = [](auto &ctnr) {
      std::fill(ctnr.begin(), ctnr.end(), T{1});
    };
    std::vector<T> vec(size);
    lambda_fill(vec);
    double duration = measureTime(lambda_fill, vec);
    outputTime("lambda_fill, vec", duration);
  }
}