///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for the nextafter function of (fixed_point).

#include <cmath>

#define BOOST_TEST_MODULE test_negatable_func_nextafter
#define BOOST_LIB_DIAGNOSTIC

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_negatable_func_nextafter)
{
  typedef boost::fixed_point::negatable<7, -8> fixed_point_type;
  typedef fixed_point_type::float_type         float_point_type;

  const fixed_point_type tol = ldexp(fixed_point_type(1), fixed_point_type::resolution + 1);

  using std::ldexp;
  using std::nextafter;

  const fixed_point_type increment = ldexp(float_point_type(1), -8);

  // Check positive argument.
  fixed_point_type x;
  float_point_type y;

  x = nextafter(fixed_point_type(0), fixed_point_type(1) / 10);
  y = +increment;

  BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);

  // Check negative argument.
  x = nextafter(fixed_point_type(0), fixed_point_type(-1) / 10);
  y = -increment;

  BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);

  // Check zero argument.
  x = nextafter(fixed_point_type(0), fixed_point_type(0));
  y = nextafter(float_point_type(0), float_point_type(0));

  BOOST_CHECK_EQUAL(x, fixed_point_type(y));
  BOOST_CHECK_EQUAL(x, fixed_point_type(0));

  // Check identical arguments.
  x = nextafter(fixed_point_type(0.25F), fixed_point_type(0.25F));
  y = nextafter(float_point_type(0.25F), float_point_type(0.25F));

  BOOST_CHECK_EQUAL(x, fixed_point_type(y));
  BOOST_CHECK_EQUAL(x, fixed_point_type(0.25F));

  x = nextafter(fixed_point_type(-0.25F), fixed_point_type(-0.25F));
  y = nextafter(float_point_type(-0.25F), float_point_type(-0.25F));

  BOOST_CHECK_EQUAL(x, fixed_point_type(y));
  BOOST_CHECK_EQUAL(x, fixed_point_type(-0.25F));

  // Check the maximum argument.
  x = nextafter((std::numeric_limits<fixed_point_type>::max)() - fixed_point_type(increment),
                (std::numeric_limits<fixed_point_type>::max)());

  BOOST_CHECK_EQUAL(x, (std::numeric_limits<fixed_point_type>::max)());
}