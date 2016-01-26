//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_REPNUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_REPNUM_HPP_INCLUDED

#include <nt2/core/functions/repnum.hpp>
#include <nt2/include/functions/as_size.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( repnum_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
   BOOST_DISPATCH_RETURNS ( 2, ( const A0& a0, const A1& a1)
                          , (nt2::repnum( a0, nt2::as_size(a1)))
                          )
  };
} }

#endif
