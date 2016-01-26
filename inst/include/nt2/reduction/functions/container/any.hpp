//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_CONTAINER_ANY_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_CONTAINER_ANY_HPP_INCLUDED

#include <nt2/reduction/functions/any.hpp>
#include <boost/simd/reduction/functions/any.hpp>
#include <nt2/core/container/dsl/reduction.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/core/container/dsl/size.hpp>

#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/constants/false.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( any_, tag::cpu_
                            , (A0)(T)(N)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::any( nt2::is_nez(a0) )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( any_, tag::cpu_
                            , (A0)(T)(N)(A1)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                              (scalar_< integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::any( nt2::is_nez(a0), a1 )
    )
  };
} } }

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<boost::simd::tag::any_,Domain,1,Expr>
        : meta::reduction_size<Expr,1>
  {};

  template<class Domain, class Expr>
  struct  size_of<boost::simd::tag::any_,Domain,2,Expr>
        : meta::reduction_size<Expr,2>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<boost::simd::tag::any_,Domain,N,Expr>
        : meta::reduction_value<boost::simd::tag::any_,Expr>
  {};
} }

#endif
