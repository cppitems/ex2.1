#pragma once

#include <chrono>
#include <utility>

// implement your wrapping-functionality 'track_time' here
template<class CALLABLE, class Arg>
double measureTime(CALLABLE &&call, Arg&& a, Arg&& b) {
  using Clock = std::chrono::high_resolution_clock;
  auto start = Clock::now();    // start time measurement

  // forward the two arguments to the callable `call`
  call(std::forward<Arg>(a), std::forward<Arg>(b));

  auto stop = Clock::now();     // stop time measurement
  return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
