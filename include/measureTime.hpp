#pragma once

#include <chrono>
#include <utility>

// Change this function, so it can be used to measure
// the execution time of a function with an arbitrary
// number of arguments
template<class CALLABLE, class Arg>
double measureTime(CALLABLE &&callable, Arg&& a, Arg&& b) {
  using Clock = std::chrono::high_resolution_clock;
  auto start = Clock::now();    // start time measurement

  // forward the two arguments to the callable `call`
  callable(std::forward<Arg>(a), std::forward<Arg>(b));

  auto stop = Clock::now();     // stop time measurement
  return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
