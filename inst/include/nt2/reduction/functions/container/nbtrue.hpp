//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_CONTAINER_NBTRUE_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_CONTAINER_NBTRUE_HPP_INCLUDED

#include <nt2/reduction/functions/nbtrue.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/core/container/dsl.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( nbtrue_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::sum(nt2::real(nt2::if_one_else_zero(a0)))
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( nbtrue_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, const A1& a1),
      nt2::sum(nt2::real(nt2::if_one_else_zero(a0)), a1)
    )
  };
} } }

#endif
