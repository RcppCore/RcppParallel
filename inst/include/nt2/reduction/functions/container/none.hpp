//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_CONTAINER_NONE_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_CONTAINER_NONE_HPP_INCLUDED

#include <nt2/reduction/functions/none.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/all.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( none_, tag::cpu_
                            , (A0)(T)(N)
                            , ((expr_< generic_<fundamental_<A0> >,T,N >))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::all( nt2::is_eqz(a0) )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( none_, tag::cpu_
                            , (A0)(T)(N)(A1)
                            , ((expr_< generic_<fundamental_<A0> >,T,N >))
                              (scalar_< integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::all( nt2::is_eqz(a0), a1 )
    )
  };
} } }

#endif
