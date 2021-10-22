# areclose

## C/C++ equivalent of Python's `math.isclose` function ##

(well that should be called `areclose` too! 🙂)

## Explanation

Determining whether two input values are close to each other or not is done according to given absolute and relative tolerances.

**Absolute tolerance** is obvious, as the maximum allowed difference between the two input values. This tolerance value must be at least zero.

The default value for this is `0` because it is not possible to determine an appropriate tolerance without knowing the likely values expected in a given use case.

**Relative tolerance** is the maximum allowed difference, but, relative to the larger absolute input value of the two. A relative tolerance of 5% is specified as `0.05`. This value must be greater than zero and normally less than 1 to be meaningful.

A good default value for this is `1e-09`, which assures that the two values are the same within about 9 decimal digits.

Using an absolute tolerance is important for comparisons near zero. This is because when both input values are lesser in magnitude than 1, a relative comparison test is very unlikely to be satisfied.

Providing `0` as input for either kind of tolerance will switch off that type of tolerance checking.

## Note

The IEEE 754 special values of `NaN`, `inf`, and `-inf` will be handled according to IEEE rules.  Specifically, `NaN` is not considered close to any other value, including `NaN`.  `inf` and `-inf` are only considered close to themselves.

If passed invalid tolerance values `false` is always returned.

The implementation is based on CPython, but has one small improvement from Boost.

## Usage

Copy-paste the appropriate header for your language into your project and `#include` it where required.

### C

`bool areclose(double a, double b)` 

… is for testing with default tolerances.

`bool areclose2(double a, double b, double abs_tol, double rel_tol)`

… allows you to customize the tolerance values.

### C++

All the functionality is embodied in the `AreClose` functor class. Its members are as follows:

The default constructor `AreClose()` initializes a functor with default tolerances.

The constructor `AreClose(double absTol, double relTol)` allows you to specify the tolerances.

`isValid` returns whether an functor has valid tolerances. An invalid functor will always test false.

`double absoluteTolerance()` and `double relativeTolerance()` are getters.

`bool setAbsoluteTolerance(double)` and `bool setRelativeTolerance(double)` are setters. They return the success status based on whether the input value is valid. Invalid values are not set.

`static bool invalidTolerance(double)` checks for invalid tolerance values.

Use as:

```
AreClose areclose{2e-12, 4 * DBL_EPSILON};
if (areclose(a, b)) …
```

## License

© 2021, Shriramana Sharma, samjnaa-at-gmail-dot-com

Use, modification and distribution are permitted subject to the "BSD-2-Clause"-type license stated in the accompanying file LICENSE.txt.
