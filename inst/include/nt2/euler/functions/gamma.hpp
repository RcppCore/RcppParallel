//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_GAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_GAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gamma generic tag

     Represents the gamma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gamma_ : ext::elementwise_<gamma_> { typedef ext::elementwise_<gamma_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_gamma_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::gamma_, Site> dispatching_gamma_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::gamma_, Site>();
   }
   template<class... Args>
   struct impl_gamma_;
  }
  /*!
    Computes Gamma function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = gamma(a0);
    @endcode

    Computes \f$ \displaystyle \Gamma(a_0)=\int_0^\infty t^{a_0-1}e^{-t}dt\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gamma_, gamma, 1)
}

#endif

