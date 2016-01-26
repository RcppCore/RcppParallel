//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SETSYMDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SETSYMDIFF_HPP_INCLUDED

#include <nt2/core/functions/setsymdiff.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/unique.hpp>
#include <algorithm>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::setsymdiff_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type      t_type;
    typedef typename t_type::value_type                                   value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      container::table<value_type> a = unique(boost::proto::child_c<0>(in));
      container::table<value_type> b = unique(boost::proto::child_c<1>(in));
      container::table<value_type> r(of_size(min(numel(a), numel(b)), 1));
      auto last = std::set_symmetric_difference(a.begin(),a.end(),b.begin(),b.end(),r.begin());
      r.resize(nt2::of_size(last-r.begin(), 1));
      return out = r;
    }
  };
} }

#endif
