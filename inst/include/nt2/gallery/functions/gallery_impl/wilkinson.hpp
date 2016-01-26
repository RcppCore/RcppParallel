//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_WILKINSON_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_WILKINSON_HPP_INCLUDED
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2{ namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( wilkinson_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0>>)
                              (target_<scalar_< unspecified_<T>>>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, T const& tgt),
                           (boost::proto::make_expr<nt2::tag::wilkinson_
                           , container::domain>( tgt, _2D(a0,a0)) )
      );
  };

  BOOST_DISPATCH_IMPLEMENT  ( wilkinson_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0>>)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0),
                           (boost::proto::make_expr<nt2::tag::wilkinson_
                           , container::domain>( meta::as_<double>(), _2D(a0,a0)) )
      );
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::wilkinson_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                     result_type;
    typedef typename A0::value_type  value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      _2D sz = boost::proto::value(boost::proto::child_c<1>(in));
      std::size_t n = sz[0];
      value_type m = (n-1)/2;
      out.resize(of_size(n, n));
      auto e = ones(n-1, 1, meta::as_<value_type>());
      out = from_diag(abs(_(-m, m))) + from_diag(e,1) + from_diag(e,-1);
      return out;
    }
  };
} }


#endif

