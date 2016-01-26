//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    struct sincospi_ : ext::elementwise_<sincospi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sincospi_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sincospi_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::sincospi_, Site> dispatching_sincospi_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::sincospi_, Site>();
    }
    template<class... Args>
    struct impl_sincospi_;
  }
  /*!
    Computes simultaneously the sine and cosine
    of the input in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 s, c;
    tie(s, c) = sincospi(x);
    @endcode

    is similar to:

    @code
    T0 s =  sinpi(x);
    T0 c =  cospi(x);
    @endcode

    @see @funcref{fast_sincospi}, @funcref{sincos}, @funcref{sincosd}
    @param a0 input

    @return A Fusion Sequence containing the sinpi and cospi of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sincospi_, sincospi, 1)

  /*!
    Computes simultaneously the sine and cosine
    of the input in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 s, c;
    s = sincospi(x, c);
    @endcode

    is similar to:

    @code
    T0 s =  sinpi(x);
    T0 c =  cospi(x);
    @endcode

    @param a0 angle in radian
    @param a1 L-Value that will receive the sin of @c a0

    @return the sinpi of a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1&),2)

  /*!
    Computes simultaneously the sine and cosine
    of the input in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 s, c;
    sincospi(x, s, c);
    @endcode

    is similar to:

    @code
    T0 s =  sinpi(x);
    T0 c =  cospi(x);
    @endcode

    @param a0 angle in radian
    @param a1 L-Value that will receive the sinpi of @c a0
    @param a2 L-Value that will receive the cospi of @c a0
  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1&)(A2&),3)

    }

#endif


