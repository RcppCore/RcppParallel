//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_ERFCX_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_ERFCX_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief erfcx generic tag

     Represents the erfcx function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct erfcx_ : ext::elementwise_<erfcx_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<erfcx_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_erfcx_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::erfcx_, Site>
   dispatching_erfcx_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::erfcx_, Site>();
   }
   template<class... Args>
   struct impl_erfcx_;
  }
  /*!
    Computes the  underflow-compensating function erfcx(z) = exp(z^2) erfc(z)


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = erfcx(x);
    @endcode

    Computes: \f$\displaystyle e^{x^2}\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$

    @see @funcref{erf}, @funcref{erfc}, @funcref{erfinv}, @funcref{erfccinv}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::erfcx_, erfcx, 1)
}

#endif

