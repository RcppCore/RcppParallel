//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/sfinae_enable_if.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/traits.hpp>

#define BOOST_SIMD_OVERLOAD_UNARY_OP(Tag, Op)                                  \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
sfinae_enable_if< is_value<A0>                                                 \
                , dispatch::meta::                                             \
                  call< Tag(A0 const&) >                                       \
                >::type                                                        \
operator Op                                                                    \
(                                                                              \
  A0 const & a0                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0);                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_UNARY_OP_INC(Tag, TagInc, Op)                      \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0&                                                                 \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0                                                                      \
)                                                                              \
{                                                                              \
  return a0 = typename dispatch::make_functor<TagInc, A0>::type()(a0);         \
}                                                                              \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0                                                                  \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0,                                                                     \
  int                                                                          \
)                                                                              \
{                                                                              \
  A0 const that = a0;                                                          \
  operator Op(a0);                                                             \
  return that;                                                                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                 \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
sfinae_enable_if< mpl::and_< is_value<A0>, is_value<A1> >                      \
                , dispatch::meta::                                             \
                  call<Tag(A0 const&, A1 const&)>                              \
                >::type                                                        \
operator Op                                                                    \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0, a1);             \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN(Tag, Op)                          \
BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                         \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0&                                                                 \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0       & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0 const&                                                           \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
/**/

namespace boost { namespace simd
{
  template<class T>
  struct is_value
   : mpl::or_< boost::dispatch::details::is_mpl_integral<T>
             , boost::is_fundamental<T>
             , meta::is_native<T>
             , proto::is_expr<T>
             >
  {
  };

  namespace tag
  {
    struct unary_plus_;
    struct unary_minus_;
    struct complement_;
    struct logical_not_;
    struct inc_;
    struct dec_;

    struct bitwise_and_;
    struct bitwise_or_;
    struct bitwise_xor_;
    struct plus_;
    struct minus_;
    struct divides_;
    struct multiplies_;
    struct modulo_;
    struct shift_left_;
    struct shift_right_;
    struct logical_and_;
    struct logical_or_;

    struct is_equal_;
    struct is_not_equal_;
    struct is_less_;
    struct is_greater_;
    struct is_less_equal_;
    struct is_greater_equal_;
  }

  // unary operators
  BOOST_SIMD_OVERLOAD_UNARY_OP( tag::unary_plus_  ,  + )
  BOOST_SIMD_OVERLOAD_UNARY_OP( tag::unary_minus_ ,  - )
  BOOST_SIMD_OVERLOAD_UNARY_OP( tag::complement_  ,  ~ )
  BOOST_SIMD_OVERLOAD_UNARY_OP( tag::logical_not_ ,  ! )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( tag::plus_    , tag::inc_, ++ )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( tag::minus_   , tag::dec_, -- )

  // binary operators
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::bitwise_and_ , &  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::bitwise_or_  , |  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::bitwise_xor_ , ^  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::plus_        , +  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::minus_       , -  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::divides_     , /  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::multiplies_  , *  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::modulo_      , %  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::shift_left_  , << )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( tag::shift_right_ , >> )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::logical_and_        , && )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::logical_or_         , || )

  // comparison operators
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_equal_           , == )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_not_equal_       , != )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_less_            , <  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_greater_         , >  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_less_equal_      , <= )
  BOOST_SIMD_OVERLOAD_BINARY_OP( tag::is_greater_equal_   , >= )
} }

#undef BOOST_SIMD_OVERLOAD_UNARY_OP
#undef BOOST_SIMD_OVERLOAD_UNARY_OP_INC
#undef BOOST_SIMD_OVERLOAD_BINARY_OP
#undef BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN

#endif
