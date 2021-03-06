///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for the fixed_point basic narrowing constructors.

#define BOOST_TEST_MODULE test_negatable_basic_narrowing_constructors
#define BOOST_LIB_DIAGNOSTIC

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_negatable_basic_narrowing_constructors)
{
  bool result = true;

  {
    // This fixed-point negatable type has only 2 IntegralRange digits.
    // For all practical purposes, all constructions and assignments
    // must be explicit.
    //
    // For example, the following should fail.
    //  fixed_point_type x = std::uint8_t(1U);
    // But the following should succeed.
    //  fixed_point_type x(std::uint8_t(1U));

    typedef boost::fixed_point::negatable<2, -5> fixed_point_type;

    fixed_point_type x(std::uint8_t(1U));

    x = fixed_point_type(1U);

    x = static_cast<fixed_point_type>(1U);

    result &= (x == 1U);
  }

  {
    typedef boost::fixed_point::negatable<8, -7> fixed_point_type;

    // This is OK because 8 range digits in fixed_point_type
    // allow for non-narrowing conversion to boost::uint8_t.
    fixed_point_type x = boost::uint8_t(1U);

    // Here we require explicit construction from 16-bit
    // unsiged integer boost::uint16_t.
    // In other words,
    // fixed_point_type z = boost::uint16_t(1U);
    // will not work because uint16_t has more
    // digits than the IntegralRange digits of y.

    // But using explicit construction, this code
    // sequence is OK.
    fixed_point_type y(boost::uint16_t(1U));

    result &= (x == 1U);
    result &= (y == 1U);
  }

  {
    typedef boost::fixed_point::negatable<16, -15> fixed_point_type;

    // This is OK because 16 range digits in fixed_point_type
    // allow for non-narrowing conversion to boost::uint16_t.
    fixed_point_type x = boost::uint16_t(1U);

    // This is OK because conversion from 8-bit unsigned
    // integer to fixed_point_type is non-narrowing anyway.
    fixed_point_type y = boost::uint8_t(1U);

    // Here we require explicit construction from 32-bit
    // unsiged integer boost::uint32_t.
    // In other words,
    // fixed_point_type z = boost::uint32_t(1U);
    // will not work because uint32_t has more
    // digits than the IntegralRange digits of z.

    // But using explicit construction, this code
    // sequence is OK.
    fixed_point_type z(boost::uint32_t(1U));

    result &= (x == 1U);
    result &= (y == 1U);
    result &= (z == 1U);
  }

  {
    typedef boost::fixed_point::negatable<64, -63> fixed_point_type;

    fixed_point_type x;

    // These are all OK because x has 64 IntegralRange digits.
    x = boost::uint8_t(1U);
    x = boost::uint16_t(1U);
    x = boost::uint32_t(1U);
    x = boost::uint64_t(1U);

    result &= (x == 1U);
  }

  // If the code compiles, then the test passes.
  BOOST_CHECK(result);
}
