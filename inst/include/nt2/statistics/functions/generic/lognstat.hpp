//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNSTAT_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNSTAT_HPP_INCLUDED
#include <nt2/statistics/functions/lognstat.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/sqr.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT   ( lognstat_, tag::cpu_
                             , (A0)(A1)(A2)(A3)
                             , (scalar_ < floating_<A0> > )
                               (scalar_ < floating_<A1> > )
                               (scalar_ < floating_<A2> > )
                               (scalar_ < floating_<A3> > )
                             )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()( A0 const& mu, A1 const& sigma
                                            , A2 & m, A3 & v) const
    {
      A0 s2 = sqr(sigma);
      m = exp(mu +Half<A0>()*s2);
      v = exp(Two<A0>()*mu+s2)*expm1(s2);
    }
  };

  BOOST_DISPATCH_IMPLEMENT   ( lognstat_, tag::cpu_
                             , (A0)(A1)(A2)
                             , (scalar_ < floating_<A0> > )
                               (scalar_ < floating_<A1> > )
                               (scalar_ < floating_<A2> > )
                             )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()( A0 const& mu, A1 const& sigma
                                            , A2 & v) const
    {
      A0 m;
      lognstat(mu, sigma, m, v);
      return m;
    }
  };

  BOOST_DISPATCH_IMPLEMENT   ( lognstat_, tag::cpu_
                             , (A0)(A1)
                             , (scalar_ < floating_<A0> > )
                               (scalar_ < floating_<A1> > )
                             )
  {
    typedef std::pair<A0,A0> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& mu, A1 const& sigma) const
    {
      A0 m, v;
      lognstat(mu, sigma, m, v);
      return result_type(m, v);
    }
  };
} }

#endif
