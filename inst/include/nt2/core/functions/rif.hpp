//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RIF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RIF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/rif.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/core/functions/common/generative.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Define the cic function tag

      Define a hierarchizable Tag representing the cic function in generic
      contexts.
    **/
    BOOST_SIMD_CONSTANT_REGISTER( rif_, double
                                , 1, 0x3f800000UL, 0x3ff0000000000000ULL
                                )
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::rif_, Site> dispatching_rif_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::rif_, Site>();
    }
    template<class... Args>
    struct impl_rif_;
  }

  #define M0(z,n,t)                                   \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::rif_, rif, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::rif_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::rif_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
