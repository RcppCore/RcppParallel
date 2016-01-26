//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNPDF_HPP_INCLUDED
#include <nt2/statistics/functions/lognpdf.hpp>
#include <boost/assert.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/normpdf.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( lognpdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x = if_else(is_lez(a0), Inf<A0>(), a0);
      return normpdf(log(x))/x;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( lognpdf_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        A0 x = if_else(is_lez(a0), Inf<A0>(), a0);
        return normpdf(log(x), a1)/x;
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( lognpdf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(a2)), "sigma(s) must be positive");
      A0 x = if_else(is_lez(a0), Inf<A0>(), a0);
      return  normpdf(log(x), a1, a2)/x;
    }
  };


} }

#endif
