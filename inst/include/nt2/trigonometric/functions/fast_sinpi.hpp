//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_sinpi generic tag

     Represents the fast_sinpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_sinpi_ : ext::elementwise_<fast_sinpi_>
    {
      typedef ext::elementwise_<fast_sinpi_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fast_sinpi_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::fast_sinpi_, Site> dispatching_fast_sinpi_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::fast_sinpi_, Site>();
   }
   template<class... Args>
   struct impl_fast_sinpi_;
  }
  /*!
    sine of angle in \f$\pi\f$ multiples, in the interval
    \f$[-1/4, 1/4]\f$, nan outside.


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_sinpi(x);
    @endcode

    is similar to:

    @code
    T0 r = sinpi(x);
    @endcode

    provided that x belongs to \f$[-1/4, 1/4]\f$

    @see @funcref{sin}, @funcref{sinpi}, @funcref{sincospi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sinpi_, fast_sinpi, 1)
}

#endif


