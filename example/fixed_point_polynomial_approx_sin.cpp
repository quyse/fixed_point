
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Paul A. Bristow 2015.
// Copyright Christopher Kormanyos 2015.

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

// This file also includes Doxygen-style documentation about the function of the code.
// See http://www.doxygen.org for details.

//! \file

//! \brief Example program showing a polynomial approximation of sin(negatable).

// Below are snippets of code that are included into Quickbook file fixed_point.qbk.

#include <iomanip>
#include <iostream>

#include <boost/fixed_point/fixed_point.hpp>

namespace local
{
  template<typename NumericType>
  NumericType sin(const NumericType& x)
  {
    // This subroutine computes sin(x) using a polynomial approximation.
    // This polynomial approximation provides about 4 decimal digits
    // of precision in the range -pi/2 < x < +pi/2.

    // The coefficients in the polynomial approximation originate
    // from C. Kormanyos, Real-Time C++ (Springer, Heidelberg, 2013).
    // See Sect. 13.3, in particular Eqs. 13.4 and 13.5 therein.

    // Use the scaled argument chi = x / (pi / 2).
    const NumericType chi  = (x * 2) / NumericType(3.14159265358979323846L);

    // Compute chi^2, as this is also used in the polynomial approximation.
    const NumericType chi2 = chi * chi;

    // Perform the polynomial approximation using coefficient
    // manipulation via the method of Horner.
    return ((         0.0722739F
             * chi2 - 0.6425639F)
             * chi2 + 1.5704128F)
             * chi;
  }
}

int main()
{
  // Here we compute sin(n/4) for 1 <= n < 7 for a fixed-point negatable type.
  for(int n = 1; n < 7; ++n)
  {
    typedef boost::fixed_point::negatable<7, -24> fixed_point_type;

    const fixed_point_type x = fixed_point_type(n) / 4;

    std::cout << std::setprecision(4)
              << std::fixed
              << local::sin(x)
              << "\t";
  }
  std::cout << std::endl;

  // Compare with the control values of sin(n/4) computed
  // with a built-in floating-point type.
  for(int n = 1; n < 7; ++n)
  {
    using std::sin;

    const float x = float(n) / 4;

    std::cout << std::setprecision(4)
              << std::fixed
              << sin(x)
              << "\t";
  }
  std::cout << std::endl;
}
