//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_NORMSTAT_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_NORMSTAT_HPP_INCLUDED
#include <nt2/statistics/functions/normstat.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT   ( normstat_, tag::cpu_
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
      m = mu;
      v = sqr(sigma);
    }
  };

  BOOST_DISPATCH_IMPLEMENT   ( normstat_, tag::cpu_
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
      v = sqr(sigma);
      return mu;
    }
  };

  BOOST_DISPATCH_IMPLEMENT   ( normstat_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_ < floating_<A0> > )
                                      (scalar_ < floating_<A1> > )
                                    )
  {
    typedef std::pair<A0,A0> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& mu, A1 const& sigma) const
    {
      return result_type(mu, sqr(sigma));
    }
  };
} }

#endif
