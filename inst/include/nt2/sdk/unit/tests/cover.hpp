//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/unit/details/cover.hpp>
#include <nt2/sdk/unit/details/once.hpp>
#include <vector>
#include <string>

/// INTERNAL ONLY
#if !defined(NT2_NB_RANDOM_TEST)
#define NT2_NB_RANDOM_TEST 128
#endif

/*!
  @brief Perform precision coverage test on arbitrary function

  For a given function @c FUNC, checks if the application of @c FUNC on the
  set of data @c INPUTS is within a given ULP tolerance relatively to a set
  of reference value @c REF

  @param FUNC   Polymorphic function to test
  @param INPUTS Preprocessor sequence of tuples containing references data and
                the types to use to perform the computation.
  @param REF    Reference data to check against
  @param N      Maximum ULP tolerance
**/
#define NT2_COVER_FN_ULP_EQUAL(FUNC, INPUTS, REF, N)                           \
do                                                                             \
{                                                                              \
  std::string desc = nt2::details::                                            \
                    cover_test_name(FUNC, NT2_ENUM_REFERENCES(INPUTS));        \
                                                                               \
  nt2::unit::test_count()++;                                                   \
  ::nt2::details::test_cover_ulp( desc.c_str(),__FILE__,__LINE__               \
                                , FUNC, (REF), N                               \
                                , NT2_ENUM_REFERENCES(INPUTS)                  \
                                );                                             \
} NT2_TEST_ONCE                                                          \
/**/

/*!
  @brief Perform precision coverage test on an NT2 functor

  For a given fucntor tag @c TAG, checks if the application of the associated
  function on the set of data @c INPUTS is within a given ULP tolerance
  relatively to a set of reference value @c REF

  @param TAG    Tag for the function to test.
  @param INPUTS Preprocessor sequence of tuples containing references data and
                the types to use to perform the computation.
  @param REF    Reference data to check against
  @param N      Maximum ULP tolerance
**/
#define NT2_COVER_ULP_EQUAL(TAG, INPUTS, REF, N)                               \
do                                                                             \
{                                                                              \
  std::string desc = nt2::details::                                            \
                    cover_test_name(TAG(), NT2_ENUM_REFERENCES(INPUTS));       \
                                                                               \
  nt2::unit::test_count()++;                                                   \
  ::nt2::details::test_cover_ulp( desc.c_str(),__FILE__,__LINE__               \
                                , nt2::functor<TAG>(), (REF), N                \
                                , NT2_ENUM_REFERENCES(INPUTS)                  \
                                );                                             \
} NT2_TEST_ONCE                                                          \
/**/

#endif
