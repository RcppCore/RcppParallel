//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief divides generic tag

     Represents the divides function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct divides_ : ext::elementwise_<divides_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<divides_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_divides_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::divides_, Site> dispatching_divides_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::divides_, Site>();
   }
   template<class... Args>
   struct impl_divides_;
  }
  /*!
    return the elementwise division of the two parameters
    Infix notation can be used with operator '/'

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = divides(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0/a1;
    @endcode

    @par Alias:
    @c div, @c rdiv

    @see  @funcref{fast_divides}, @funcref{rec}, @funcref{fast_rec}, @funcref{divs}, @funcref{divfloor},
    @funcref{divceil}, @funcref{divround}, @funcref{divround2even}, @funcref{divfix}
    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , divides         , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , div             , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , rdiv            , 2 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
