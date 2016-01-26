//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_PROPERTIES_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_PROPERTIES_HPP_INCLUDED

#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <memory>

/*!
  @brief Check if constructing some type is impossible at runtime
**/
#define NT2_TEST_IS_NOT_CONSTRUCTIBLE(X,...)                                    \
NT2_TEST_ASSERT (( std::unique_ptr < BOOST_PP_REMOVE_PARENS(X) >               \
                                  ( new BOOST_PP_REMOVE_PARENS(X) __VA_ARGS__) \
                ))                                                              \
/**/

#endif
