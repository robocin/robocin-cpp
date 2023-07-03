# utility

A collection of utility functions and classes.

## Table of Contents

- [angular](#angular)
- [concepts](#concepts)
- [epsilon](#epsilon)
- [fuzzy_compare](#fuzzy_compare)
- [type_traits](#type_traits)

<a name="angular"></a>

## [`angular`](angular.h)

The [angular](angular.h) header provides a set of functions to perform operations on angular values.

- `degreesToRadians`: convert degrees to radians;
- `radiansToDegrees`: convert radians to degrees;
- `normalizeAngle`: normalize an angle to the range [-pi, pi];
- `smallestAngleDiff`: calculate the smallest angle difference between two angles;
- `absSmallestAngleDiff`: calculate the absolute value of the smallest angle difference between two angles;

> **Note**: As in the standard library, additional overloads are provided for all integer types, which are treated
> as `double`.

<a name="concepts"></a>

## [`concepts`](concepts.h)

The [concepts](concepts.h) header provides a set of concepts extended the standard library.

- `arithmetic`: a concept that represents a type that is either an integral or floating point type;

<a name="epsilon"></a>

## [`epsilon`](epsilon.h.in)

The [epsilon](epsilon.h.in) is a [CMake configure file](https://cmake.org/cmake/help/latest/command/configure_file.html)
that defines the epsilon value passed to CMake during project build through the `ROBOCIN_FLOAT_EPSILON`,
`ROBOCIN_DOUBLE_EPSILON` and `ROBOCIN_LONG_DOUBLE_EPSILON` flags (see [CMakeLists.txt](CMakeLists.txt)).

These values will be used by the library to perform real number comparisons.

* The existence of these values can be verified as follows:

```cpp
robocin::has_epsilon<float>::value;
robocin::has_epsilon<double>::value;
robocin::has_epsilon<long double>::value;
```

or:

```cpp
robocin::has_epsilon_v<float>;
robocin::has_epsilon_v<double>;
robocin::has_epsilon_v<long double>;
```

* When provided, you can access them without using:

```cpp
robocin::has_epsilon<float>::epsilon;
robocin::has_epsilon<double>::epsilon;
robocin::has_epsilon<long double>::epsilon;
```

or:

```cpp
robocin::epsilon_v<float>;
robocin::epsilon_v<double>;
robocin::epsilon_v<long double>;
```

<a name="fuzzy_compare"></a>

## [`fuzzy_compare`](fuzzy_compare.h)

The [fuzzy_compare](fuzzy_compare.h) header provides a set of functions to perform fuzzy comparisons and functor classes
to be used with the standard library algorithms. There are many ways to compare real numbers, but for the applications
that RobôCIn and other robotics teams use, the way chosen is to compare the absolute difference against
a [tolerance margin](#epsilon):

```cpp
// check if a floating point number 'is zero':
std::abs(value) <= epsilon;

// check if two floating point numbers 'are equal':
std::abs(lhs - rhs) <= epsilon;
```

- `fuzzyIsZero`: check if a floating point number is close to zero;
- `fuzzyCmpEqual`: check if two floating point numbers are close to each other;
- `fuzzyCmpNotEqual`: check if two floating point numbers are not close to each other;
- `fuzzyCmpThreeWay`: check if two floating point numbers are close to each other, returning a C++20 three-way
  comparison result (see
  [Three-way comparison](https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison));
- `fuzzyCmpLess`: check if a floating point number is less than another;
- `fuzzyCmpLessEqual`: check if a floating point number is less than or equal to another;
- `fuzzyCmpGreater`: check if a floating point number is greater than another;
- `fuzzyCmpGreaterEqual`: check if a floating point number is greater than or equal to another.
- Functors:
    - `FuzzyIsZero`: functor to check if a floating point number is close to zero;
    - `FuzzyEqualTo`: functor to check if two floating point numbers are close to each other;
    - `FuzzyNotEqualTo`: functor to check if two floating point numbers are not close to each other;
    - `FuzzyThreeWay`: functor to perform a three-way comparison between two floating point numbers;
    - `FuzzyLess`: functor to check if a floating point number is less than another;
    - `FuzzyLessEqual`: functor to check if a floating point number is less than or equal to another;
    - `FuzzyGreater`: functor to check if a floating point number is greater than another;
    - `FuzzyGreaterEqual`: functor to check if a floating point number is greater than or equal to another.

> **Note**: The `fuzzy*` functions / `Fuzzy*` functors with implicit epsilon are only available when
> the [epsilon](#epsilon) is defined.
> Otherwise, you must explicitly pass the epsilon value to the function / during construction.

<a name="type_traits"></a>

## [`type_traits`](type_traits.h)

The [type_traits](type_traits.h) header provides a set of type traits extended the standard library.

- `common_floating_point_for_comparison`: a type trait that represents the common floating point type for comparison
  between two arithmetic types (the tolerance of the lowest precision floating point is prioritized);
  - `common_floating_point_for_comparison_t`: a helper alias for `common_floating_point_for_comparison::type`;
