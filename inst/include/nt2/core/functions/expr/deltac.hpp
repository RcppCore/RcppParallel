//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DELTAC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DELTAC_HPP_INCLUDED

#include <nt2/include/functions/deltac.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( deltac_, tag::cpu_
                            , (A0)(A1)(AST)(T)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                              ((ast_<AST, nt2::container::domain>))
                              ((target_<scalar_<unspecified_<T> > > ))
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 i, A1 j, const AST& s, T const& t)
                                , ( A0 i, A1 j, const AST& s, T const&  )
                                , (nt2::deltac(i, j, nt2::as_size(s), T()))
                                )
  };
} }

#endif
