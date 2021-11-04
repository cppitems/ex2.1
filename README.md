# Exercise EX2.3

This exercise is part **1** of 3 parts of EX2. See also [Item 000](https://cppitems.github.io/#/item/000) for an overview and deadlines. The submission deadline for EX2 (all three parts) is **Mo 29.11.2021, 4pm**. The sources related to EX2.1 are available at [https://github.com/cppitems/ex2.1](https://github.com/cppitems/ex2.1).

## Task description

In this exercise, it is your task to implement a wrapper-functionality to measure the run time of *callables*, which are just functions or function objects which can be *called* using the `()` operator.

The functionality to measure the run time is already provided in `src/MeasureTransform.cpp`, which will be used to measure the time taken by any function passed.

You are provided with a simple and inflexible implementation of `measureTime`, which only works for functions with two parameters of the same type:
```C++
template<class CALLABLE, class Arg>
double measureTime(CALLABLE &&call, Arg&& a, Arg&& b) {
  using Clock = std::chrono::high_resolution_clock;
  auto start = Clock::now();    // start time measurement

  // forward the two arguments to the callable `call`
  call(std::forward<Arg>(a), std::forward<Arg>(b));

  auto stop = Clock::now();     // stop time measurement
  return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
```

**Adapt the the function `measureTime` to allow for an arbitrary number of function arguments with arbitrary and possibly differing types.**

**You have to implement the wrapping-functionality solely in `include/measureTime.hpp` and are not allowed to change any other files.**

Further, your implementation has to support all use cases present in `src/MeasureTransform.cpp`, meaning a different number of function parameters passed to the *callable*. This will allow a user of this library to measure the timing of any function with any number of passed arguments.

## Tests

The first test `tests/Test_two_args.cpp` works out of the box and should show you how perfect forwarding will be used:

For example, if we want to measure the time it takes to execute a simple `add` function:
```C++
void add(double& a, double b) {
  a += b;
}

// normal function call
double a = 1.;
add(a, 3.);

// function call to measure the runtime
double duration = measureTime(add, a, 3.);
```

However, if two parameters with different type are passed, this implementation fails. This is the case in the next test: `tests/Test_two_different_args`.

The provided implementation will also fail if the number of parameters is not exactly 2.

**Be aware that your solution must support any number of parameters and therefore adding overloads with different numbers of arguments will not lead you to a reasonable solution**

In order to allow for any number of different parameters, you should use the following concepts:

- **perfect forwarding** (to support any combination of "value-ness", "const-ness" and "reference-ness" for the list of arguments) in combination with a
- **variadic template** (to be able to forward any number of arguments)


**Note**: For this exercise, you can assume that the `measureTime` wrapper-functionality only needs to support functions with return type `void`.

Prepare yourself for a discussion on the concepts involved in your solution.

## Benchmark

Once your implementation passes all tests, you can run the benchmark to see how the std algorithm `std::transform` performs when used with different types. You are not required to understand the benchmarked functions in detail.

By default, building of the benchmark is disabled in CMake and therefore it has to be turned on using:
```bash
cmake .. -D BUILD_BENCHMARK=ON
```
Runnning `make` will now also build the benchmark, which you can execute using
```bash
./MeasureTransform
```