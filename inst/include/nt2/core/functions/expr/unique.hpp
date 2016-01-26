//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_UNIQUE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_UNIQUE_HPP_INCLUDED

#include <nt2/core/functions/unique.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sort.hpp>
#include <algorithm>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1,nt2::tag::unique_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type      t_type;
    typedef typename t_type::value_type                                   value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      container::table<value_type> a = sort(colvect(boost::proto::child_c<0>(in)));
      auto last =  std::unique(a.begin(), a.end());
      a.resize(nt2::of_size(last-a.begin(), 1));
      return out = a;
    }
  };
} }

#endif
