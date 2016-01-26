//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_PLEVL_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_PLEVL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
// plevl(x, p)
// This compute the evaluation of a polynomial p of degree N at x
// The polynomial is supposed to be given by an array of N elements
// in decreasing degrees order and the leading coef is supposed to be one
// and not a part of the polynomial
namespace nt2 { namespace tag
  {
    struct plevl_ : ext::elementwise_<plevl_> { typedef ext::elementwise_<plevl_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_plevl_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::plevl_, Site> dispatching_plevl_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::plevl_, Site>();
    }
    template<class... Args>
    struct impl_plevl_;
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::plevl_, plevl, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::plevl_, p1evl, 2)
}


#endif

// modified by jt the 25/12/2010
