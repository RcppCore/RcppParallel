//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_CONTAINER_ALL_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_CONTAINER_ALL_HPP_INCLUDED

#include <nt2/reduction/functions/all.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/reduction.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/is_nez.hpp>

#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/true.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( all_, tag::cpu_
                            , (A0)(T)(N)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::all( nt2::is_nez(a0) )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( all_, tag::cpu_
                            , (A0)(T)(N)(A1)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                              (scalar_< integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::all( nt2::is_nez(a0), a1 )
    )
  };
} } }

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::all_,Domain,1,Expr>
        : meta::reduction_size<Expr,1>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::all_,Domain,2,Expr>
        : meta::reduction_size<Expr,2>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::all_,Domain,N,Expr>
        : meta::reduction_value<boost::simd::tag::all_,Expr>
  {};
} }

#endif
