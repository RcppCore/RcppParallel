//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_ZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_ZERO_CROSSING_RATE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the zero_crossing_rate functor
    **/
    struct zero_crossing_rate_ : ext::abstract_<zero_crossing_rate_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<zero_crossing_rate_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_zero_crossing_rate_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::zero_crossing_rate_, Site> dispatching_zero_crossing_rate_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::zero_crossing_rate_, Site>();
    }
    template<class... Args>
    struct impl_zero_crossing_rate_;
  }
  /*!
    @brief rate of sign changes along a signal

    Computes the rate of sign changes along a signal along a given dimension

    @par Semantic

    For any table expression and integer:

    @code
    auto r = zero_crossing_rate(s, n);
    @endcode

    is equivalent to:

    @code
    auto r = mean(if_one_else_zero(is_ltz(adjprod(s, n))), n));
    @endcode

    n default to firstnonsingleton(s)

    @see @funcref{mean}, @funcref{adjprod}, @funcref{if_one_else_zero}

    @param a0 Table expression to process
    @param a1 optional normalization


    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zero_crossing_rate, 2)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zcr, 2)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zero_crossing_rate, 1)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zcr, 1)
}

#endif
