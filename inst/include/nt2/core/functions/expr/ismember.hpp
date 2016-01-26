//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ISMEMBER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ISMEMBER_HPP_INCLUDED

#include <nt2/core/functions/ismember.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/inc.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/unique.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::ismember_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type      t_type;
    typedef typename t_type::value_type                                   value_type;
    typedef typename meta::as_integer<value_type>::type                       i_type;

    result_type operator()(A0& out, const A1& in) const
    {
      container::table<value_type> a = colvect(boost::proto::child_c<0>(in));
      container::table<value_type> b = unique(boost::proto::child_c<1>(in));
      container::table<i_type> c = bsearch(rowvect(b), rowvect(a));
      i_type n = numel(b);
      auto c1 =  min(inc(c), n);
      finalize(out, in, a, b, c, c1, N());
      out.resize(boost::proto::child_c<0>(in).extent());
      return out;
    }
  private :
    template < class T1,  class T2, class T3, class T4>
      static BOOST_FORCEINLINE void finalize(A0& out, A1&,
                                             const T1& a, const T2& b,
                                             const T3& c, const T4& c1,
                                             boost::mpl::long_<2> const&)
    {
      out = logical_or(eq(a, b(c)), eq(a, b(c1)));
    }
    template < class T1,  class T2, class T3, class T4>
    static BOOST_FORCEINLINE void finalize(A0& out, A1&in,
                                           const T1& a, const T2& b,
                                           const T3& c,  const T4& c1,
                                           boost::mpl::long_<3> const&)
    {
      value_type tol = boost::proto::child_c<2>(in)*max(abs(a));
      out = logical_or(le(abs(a-b(c)), tol), le(abs(a-b(c1)), tol));
    }

  };
} }

#endif
