//==============================================================================
//         Copyright 2015  J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_WHEREIJK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_WHEREIJK_HPP_INCLUDED

#include <nt2/core/functions/whereijk.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( whereijk_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereijk_, container::domain>
                                ( a0
                                , boost::cref(a1)
                                , boost::cref(a2)
                                )
                              )
                          );
  };

  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( whereijk_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereijk_, container::domain>
                                ( a0
                                , boost::cref(a1)
                                , a2
                                )
                              )
                          );
  };

  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( whereijk_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereijk_, container::domain>
                                ( a0
                                , a1
                                , boost::cref(a2)
                                )
                              )
                          );
  };
} }

#endif
