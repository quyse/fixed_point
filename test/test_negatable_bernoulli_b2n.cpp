///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for bernoulli_b2n(fixed_point). Along the way, also test numerous fixed_point arithmetic operations.

#define BOOST_TEST_MODULE test_negatable_bernoulli_b2n
#define BOOST_LIB_DIAGNOSTIC

#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/math/special_functions/bernoulli.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_negatable_bernoulli_b2n)
{
  // Test bernoulli_b2n() for negatable. Compute an array of
  // fixed-point Bernoulli numbers and test them with
  // multiprecision floating-point control values.

  BOOST_CONSTEXPR_OR_CONST std::size_t number_of_bernoulli_b2n = 22U;

  BOOST_CONSTEXPR_OR_CONST int resolution_of_bernoulli_b2n = -280;

  // Make a very large fixed-point type with an unusually asymetric large integral range.
  typedef boost::fixed_point::negatable<2047 + resolution_of_bernoulli_b2n,
                                        resolution_of_bernoulli_b2n,
                                        boost::fixed_point::round::nearest_even>
  fixed_point_type;

  // Define a fixed-point vector for storing the Bernoulli numbers.
  std::vector<fixed_point_type> b2n_fixed;

  // Fill the the fixed-point vector with even Bernoulli numbers.
  boost::math::bernoulli_b2n<fixed_point_type>(0, number_of_bernoulli_b2n, std::back_inserter(b2n_fixed));

  // Define a less-wide fixed-point type for manipulating the results.
  typedef boost::fixed_point::negatable<511 + resolution_of_bernoulli_b2n,
                                        resolution_of_bernoulli_b2n,
                                        boost::fixed_point::round::nearest_even>
  fixed_point_result_type;

  // Define a less-wide floating-point type for verifying the results.
  typedef fixed_point_type::float_type float_point_result_type;

  std::vector<fixed_point_result_type> b2n_fixed_result(number_of_bernoulli_b2n);

  // Define storage for multiprecision floating-point control values.
  std::vector<float_point_result_type> b2n_float_control;

  // Fill the the floating-point vector with control values.
  boost::math::bernoulli_b2n<float_point_result_type>(0, number_of_bernoulli_b2n, std::back_inserter(b2n_float_control));

  // Transform the Bernoulli number arrays. This tests the fixed-point
  // class populating an STL container in combination with an algorithm
  // and a lambda function.
  std::transform(b2n_fixed.cbegin(),
                 b2n_fixed.cend(),
                 b2n_fixed_result.begin(),
                 [](const fixed_point_type& b2n) -> fixed_point_result_type
                 {
                   return fixed_point_result_type(b2n);
                 });


  // Set a judiciously selected tolerance for these tests.
  const fixed_point_result_type tolerance = ldexp(fixed_point_result_type(1), -160);

  // Search for a potential mismatch between the fixed-point
  // Bernoulli numbers and the floating-point Bernoulli numbers

  const std::pair<std::vector<fixed_point_result_type>::const_iterator,
                  std::vector<float_point_result_type>::const_iterator> result_of_mismatch_search =
    std::mismatch(b2n_fixed_result.cbegin(),
                  b2n_fixed_result.cend(),
                  b2n_float_control.cbegin(),
                  [&tolerance](const fixed_point_result_type& a, const float_point_result_type& b) -> bool
                  {
                    const fixed_point_result_type fraction = fabs(a / fixed_point_result_type(b));
                    const fixed_point_result_type delta    = fabs(1 - fraction);

                    const bool comparison_is_ok = (delta <= tolerance);

                    BOOST_CHECK_EQUAL(comparison_is_ok, true);

                    return comparison_is_ok;
                  });

  BOOST_CHECK_EQUAL(result_of_mismatch_search.first == b2n_fixed_result.cend(), true);
}