//==============================================================================
//         Copyright 2015 - J.T. Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  round generic tag

      Represents the round function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct round_ : ext::elementwise_<round_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<round_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_round_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::round_, Site> dispatching_round_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::round_, Site>();
    }
    template<class... Args>
    struct impl_round_;
  }
  /*!
    Computes the rounded to nearest integer away from 0

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = round(x);
    @endcode

    Returns the nearest integer to x.

    @par Note:

    aways from 0 means that half integer values are rounded to the nearest
    integer of greatest absolute value

    @param  x value to be rounded

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round_, round, 1)
  /*!
    round(x,n) rounds aways from 0 to n digits:

    @par semantic:
    For any given value @c x of type @c T and integer n :

    @code
    T r = round(x, n);
    @endcode

    is equivalent to

    @code
    T r = round(x*exp10(n)*exp10(-n));
    @endcode

    @par Note:

    n > 0: round to n digits to the right of the decimal point.

    n = 0: round to the nearest integer.

    n < 0: round to n digits to the left of the decimal point.

    aways from 0 means that half integer values are rounded to the nearest
    integer of greatest absolute value

    @param  x value to be rounded
    @param  n number of digits

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round_, round, 2)
} }

#endif
