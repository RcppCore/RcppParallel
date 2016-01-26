//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/expr_type.hpp>
#include <nt2/sdk/unit/details/once.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <iostream>

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE__(...) #__VA_ARGS__

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE_(text) NT2_PP_STRINGIZE__ text

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE(...) NT2_PP_STRINGIZE_((__VA_ARGS__))

/*!
  @brief Check for type equality

  For a given @c Expression, consider the test successful if and only if

  @code
  boost::is_same<boost::mpl::apply<Lambda,decltype(Expression)>::type,Type>::value == true
  @endcode

  @usage{test_type_expr.cpp}
**/
#define NT2_TEST_EXPR_TYPE(Expression, Lambda, Type)                           \
do {                                                                           \
  nt2::unit::test_count()++;                                                   \
  std::cout << " * Test expression `"                                          \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Expression)) << "`\n"  \
            << "       with lambda `"                                          \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Lambda)) << "`\n"      \
            << "        is of type `"                                          \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Type)) << "`\n"        \
            << "               aka `"                                          \
            << nt2::type_id<BOOST_PP_REMOVE_PARENS(Type)>() << "`\n";         \
                                                                               \
   nt2::details::                                                              \
   check_expr_equality( (nt2::details                                          \
                            ::expr_type <BOOST_PP_REMOVE_PARENS(Lambda)>      \
                                        (BOOST_PP_REMOVE_PARENS(Expression))  \
                        )                                                      \
                      , nt2::details                                           \
                        ::is_same_as<BOOST_PP_REMOVE_PARENS(Type)>            \
                        (nt2::details                                          \
                            ::expr_type<BOOST_PP_REMOVE_PARENS(Lambda)>       \
                             (BOOST_PP_REMOVE_PARENS(Expression))             \
                        )                                                      \
                      );                                                       \
} NT2_TEST_ONCE                                                          \
/**/

/*!
  @brief Check for typeinfo equality

  For a given @c Type, consider the test successful if and only if
  @c typeid(Type) evaluates to @c Info.

  @usage{test_type_info.cpp}
**/
#define NT2_TEST_TYPE_INFO(Info, Type)                                         \
do {                                                                           \
  nt2::unit::test_count()++;                                                   \
  std::cout << " * Test type info `"                                           \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Info)) << "`\n"        \
            << "       is of type `"                                           \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Type)) << "`\n"        \
            << "              aka `"                                           \
            << nt2::type_id<BOOST_PP_REMOVE_PARENS(Type)>() << "`\n";         \
  if(typeid(BOOST_PP_REMOVE_PARENS(Type)) == Info)                            \
  {                                                                            \
    std::cout << " **passed**\n\n";                                            \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    nt2::unit::error_count()++;                                                \
    std::cout << " **failed**    is `"                                         \
              << nt2::details::demangle((Info).name())                         \
              << "`\n\n";                                                      \
  }                                                                            \
} NT2_TEST_ONCE                                                          \
/**/

/*!
  @brief Check for typeinfo equality

  For a given type @c T, consider the test successful if and only if
  @c boost::is_same<T,Type>::value evaluates to @c true.

  @usage{test_type_is.cpp}
**/
#define NT2_TEST_TYPE_IS(T, Type)                                              \
do {                                                                           \
  nt2::unit::test_count()++;                                                   \
  std::cout << " * Test type   `"                                              \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(T)) << "`\n"           \
            << "          is   `"                                              \
            << NT2_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(Type)) << "`\n"        \
            << "         aka   `"                                              \
            << nt2::type_id<BOOST_PP_REMOVE_PARENS(Type)>() << "`\n";         \
                                                                               \
   nt2::details::                                                              \
   check_type_equality< BOOST_PP_REMOVE_PARENS(T)                             \
                      >( boost::mpl::bool_                                     \
                         < boost::is_same< BOOST_PP_REMOVE_PARENS(Type)       \
                                         , BOOST_PP_REMOVE_PARENS(T)          \
                                         >::value                              \
                         >()                                                   \
                       );                                                      \
} NT2_TEST_ONCE                                                          \
/**/

#endif
