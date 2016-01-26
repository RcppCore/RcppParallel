//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_MINUSEYE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_MINUSEYE_HPP_INCLUDED

#include <nt2/include/functions/minuseye.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/homot.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/sdk/meta/strip.hpp>
namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( minuseye_, tag::cpu_,
                              (A0),
                              (scalar_<arithmetic_<A0 > >)(scalar_<arithmetic_<A0> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(2
                          , (A0 const& a0, A0 const& a1)
                          , (a0-a1)
                          );
  };
  BOOST_DISPATCH_IMPLEMENT  ( minuseye_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))(scalar_<arithmetic_<A1> > )
                            )
  {
    typedef typename meta::strip<A0>::type stA0;
    typedef typename stA0::value_type value_type;
    BOOST_DISPATCH_RETURNS(2
                          , (A0 const& a, A1 const& l)
                          , (a+nt2::homot( -value_type(l), extent(a)))
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( minuseye_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::strip<A0>::type stA0;
    typedef typename stA0::value_type value_type;
    BOOST_DISPATCH_RETURNS(1
                          , (A0 const& a)
                          , (a-nt2::eye(extent(a), nt2::meta::as_<value_type>()))
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( minuseye_, tag::cpu_,
                              (A0),
                              (scalar_<arithmetic_<A0 > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1
                          , (A0 const& a0)
                          , (minusone(a0))
                          );


  };
} }


#endif

