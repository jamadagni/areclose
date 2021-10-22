// areclose
// ========
//
// C equivalent of Python's math.isclose function
// [well that should be called areclose too! :-)]
// Has one small improvement from Boost.
//
// Copyright © 2021, Shriramana Sharma, samjnaa-at-gmail-dot-com
//
// Use, modification and distribution are permitted subject to the
// "BSD-2-Clause"-type license stated in the accompanying file LICENSE.txt

// NOTES:
// Code adapted from https://github.com/python/cpython/blob/master/Modules/mathmodule.c#L2932
// The logic of the formulation is well argued out at https://www.python.org/dev/peps/pep-0485/
// The default values are also from there.
// See also: https://docs.python.org/dev/library/math.html#math.isclose

#include <stdbool.h>
#include <float.h>
#include <math.h>

// A tolerance may be zero to switch off that particular type of tolerance checking
// but if it is non-zero then it should be finite and at least 4 × machine epsilon
// See: https://www.boost.org/doc/libs/1_75_0/libs/math/doc/html/math_toolkit/roots_noderiv/root_termination.html
#define INVALID_TOLERANCE(tol) !(tol == 0.0 || (tol >= 4 * DBL_EPSILON && isfinite(tol)))

inline bool areclose2(double a, double b, double abs_tol, double rel_tol)
{
    if (INVALID_TOLERANCE(abs_tol) || INVALID_TOLERANCE(rel_tol))
        return false;

    // The following is needed to catch infinities of the same sign since their
    // difference is NAN. And rarely, finite inputs may also be equal.
    if (a == b)
        return true;

    // Since an infinity would have an infinite relative tolerance,
    // any finite number would be considered relatively close to an infinity.
    // Further we need to catch infinities of opposite signs whose
    // difference is infinite and would compare equal to their relative
    // tolerance. The following is needed for both those cases:
    if (isinf(a) || isinf(b))
        return false;

    // The below is effectively the same as:
    // abs(a - b) <= max(abs_tol, rel_tol * max(abs(a), abs(b)))
    double diff = fabs(a - b);
    return diff <= abs_tol ||
           diff <= fabs(rel_tol * a) ||
           diff <= fabs(rel_tol * b);
}

#define areclose(A, B) areclose2(A, B, 0, 1e-09)
