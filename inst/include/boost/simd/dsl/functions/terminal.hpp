//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct terminal_;
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::terminal_, Site> dispatching_terminal_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::terminal_, Site>();
    }
    template<class... Args>
    struct impl_terminal_;
  }
  namespace tag
  {
    struct terminal_ : ext::elementwise_<terminal_>
    {
      typedef ext::elementwise_<terminal_> parent;

      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_terminal_( ext::adl_helper(), static_cast<Args&&>(args)... ) )

    };
  }

  template<class Expr>
  BOOST_FORCEINLINE typename boost::dispatch::meta::call<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type(Expr const&)>::type
  terminal(Expr const& e)
  {
    return boost::dispatch::functor<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type>()(e);
  }

  template<class Expr>
  BOOST_FORCEINLINE typename boost::dispatch::meta::call<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type(Expr&)>::type
  terminal(Expr& e)
  {
    return boost::dispatch::functor<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type>()(e);
  }
} }

#endif
