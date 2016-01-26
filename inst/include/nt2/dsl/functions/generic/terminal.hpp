//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace ext
{
  // Terminal returns ASTs by reference
  BOOST_DISPATCH_REGISTER_TO( terminal_, tag::formal_
                            , (A0)(D)
                            , ((ast_<A0, D>))
                            , boost::dispatch::identity
                            )

  // When evaluating a terminal, get its value
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(D)
                            , ((ast_<A0, D>))
                            )
  {
    typedef typename boost::proto::result_of::value<A0&>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return boost::proto::value(a0);
    }
  };

  // Terminal functions on non-ASTs do nothing
  BOOST_DISPATCH_REGISTER_TO( terminal_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            , boost::dispatch::identity
                            )
  BOOST_DISPATCH_REGISTER_TO( terminal_, tag::cpu_
                            , (A0)
                            , (generic_< unspecified_<A0> >)
                            , boost::dispatch::identity
                            )
} }

#endif
