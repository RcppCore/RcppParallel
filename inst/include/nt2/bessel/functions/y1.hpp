//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_Y1_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_Y1_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief y1 generic tag

     Represents the y1 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct y1_ : ext::elementwise_<y1_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<y1_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_y1_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::y1_, Site> dispatching_y1_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::y1_, Site>();
   }
   template<class... Args>
   struct impl_y1_;
  }
  /*!
    Bessel function of the second kind of order 1.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = y1(a0);
    @endcode

    Computes \f$\displaystyle \lim_{\nu \rightarrow 1} \frac{\cos(\nu\pi)J_{\nu}(x)-J_{-\nu}(x)}{\cos(\nu\pi)}\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::y1_, y1, 1)
}

#endif

