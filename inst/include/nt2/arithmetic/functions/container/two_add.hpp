//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_CONTAINER_TWO_ADD_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_CONTAINER_TWO_ADD_HPP_INCLUDED

#include <nt2/arithmetic/functions/two_add.hpp>
#include <nt2/include/functions/tie.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( two_add_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0,A1 const& a1,A2 & r0,A3& r1) const
    {
      nt2::tie(r0,r1) = nt2::two_add(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( two_add_, tag::cpu_
                            , (A0)(S0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< unspecified_<S0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,S0 const& a1,A1 & r0,A2& r1) const
    {
      nt2::tie(r0,r1) = nt2::two_add(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( two_add_, tag::cpu_
                            , (A0)(S0)(A1)(A2)
                            , (scalar_< unspecified_<S0> >)
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(S0 const& a0,A0 const& a1,A1 & r0,A2& r1) const
    {
      nt2::tie(r0,r1) = nt2::two_add(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( two_add_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (unspecified_<A2>)
                            )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0,A1 const& a1,A2& r1) const
    {
      result_type r0;
      nt2::tie(r0,r1) = nt2::two_add(a0,a1);
      return r0;
    }
  };
} } }

#endif
