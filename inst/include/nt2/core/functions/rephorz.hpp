//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPHORZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPHORZ_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct rephorz_ : ext::elementwise_<rephorz_>
    {
      typedef ext::elementwise_<rephorz_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rephorz_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::rephorz_, Site> dispatching_rephorz_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::rephorz_, Site>();
    }
    template<class... Args>
    struct impl_rephorz_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::rephorz_, rephorz, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::rephorz_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::rephorz_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                ::child_c<Expr&,0>::value_type::extent_type base_t;

    typedef typename make_size< base_t::static_size==1
                              ? 2
                              : base_t::static_size
                              >::type                       result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[1] *= boost::proto::value(boost::proto::child_c<1>(e));
      return sizee;
    }
  };
} }

#endif
