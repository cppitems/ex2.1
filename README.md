# Exercise EX2.3

This exercise is part **1** of 3 parts of EX2. See also [Item 000](https://cppitems.github.io/#/item/000) for an overview and deadlines. The submission deadline for EX2 (all three parts) is **Mo 29.11.2021, 4pm**. The sources related to EX2.1 are available at [https://github.com/cppitems/ex2.1](https://github.com/cppitems/ex2.1).

## Task description

In this exercise, it is your task to generialize/adopt a provided wrapper-functionality to measure the run time of *callables*, which can be functions or function objects which can be *called* using the `()` operator.

A simple and inflexible implementation of `measureTime` --- which only works for functions with two parameters of the same type --- is provided as a starting point (`include/measureTime.hpp`):

```C++
template<class CALLABLE, class Arg>
double measureTime(CALLABLE &&callable, Arg&& a, Arg&& b) {
  using Clock = std::chrono::high_resolution_clock;
  auto start = Clock::now();    // start time measurement

  // forward the two arguments to the callable `call`
  callable(std::forward<Arg>(a), std::forward<Arg>(b));

  auto stop = Clock::now();     // stop time measurement
  return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
```

However, if two parameters with different type are passed to `measureTime`, this implementation obviously fails.
The provided implementation will also fail if the number of parameters is not exactly 2.

**Be aware that your solution must support any number of parameters and therefore adding overloads with different numbers of arguments will not lead you to a reasonable solution**

**You have to implement the wrapping-functionality solely in `include/measureTime.hpp` and are not allowed to change any other files.**

In order to allow for any number of different parameters, you should use the following concepts:

- **perfect forwarding** (to support any combination of "value-ness", "const-ness" and "reference-ness" for the list of arguments) in combination with a
- **variadic template (template parameter pack)** (to be able to forward any number of arguments)

**Note**: For this exercise, you can assume that the `measureTime` wrapper-functionality only needs to support functions with return type `void`.

## Tests

The first test `tests/TestA_two_args.cpp` works out of the box and should show you how perfect forwarding will be used:
```C++
  double a = 1.;
  double b = 3.;
  // normal function call
  add(a, b);

  // function call to measure the runtime
  double duration = measureTime(add, a, b);
```
You can build and run this test individually using (from the build folder):
```bash
make TestA_two_args 
./tests/TestA_two_args 
```

The other two tests `TestB_two_different_args` and `TestC_multiple_args` do what their names suggest and initially fail (before you adopt the implementation).

## Benchmark

Once your implementation passes all tests, you can run the benchmarks provided in `src/meaasureTransform.cpp` to see how different transformations of vectors (using `std::transform`) perform. You are not required to understand the benchmarked functions in detail.

By default, building the benchmark is disabled in CMake and therefore it has to be turned on using:
```bash
cmake .. -D BUILD_BENCHMARK=ON
```
Runnning `make` will now also build the benchmark, which you can execute using
```bash
./MeasureTransform
```