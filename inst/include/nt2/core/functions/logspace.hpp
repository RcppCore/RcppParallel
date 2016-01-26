//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LOGSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LOGSPACE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/core/functions/common/generative.hpp>

namespace nt2
{
  /// INTERNAL ONLY
  struct regular_t {};

  /*!
    @brief regularity mark-up
  **/
  const meta::as_<regular_t> regular_ = {};

  namespace tag
  {
    struct logspace_ : ext::state_constant_<logspace_>
    {
      typedef ext::state_constant_<logspace_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logspace_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::logspace_, Site> dispatching_logspace_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::logspace_, Site>();
    }
    template<class... Args>
    struct impl_logspace_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::logspace_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::logspace_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
