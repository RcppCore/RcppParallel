//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPNUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPNUM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    struct  repnum_ : ext::state_constant_<repnum_>
    {
      typedef ext::state_constant_<repnum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_repnum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::repnum_, Site> dispatching_repnum_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::repnum_, Site>();
    }
    template<class... Args>
    struct impl_repnum_;
  }

  #define M0(z,n,t)                                                           \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::repnum_, repnum, n)                   \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)
  #undef M0
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::repnum_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::repnum_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
