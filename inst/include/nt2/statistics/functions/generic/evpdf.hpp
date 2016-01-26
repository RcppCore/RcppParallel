//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_EVPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_EVPDF_HPP_INCLUDED
#include <nt2/statistics/functions/evpdf.hpp>
#include <boost/assert.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/uminus.hpp>
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( evpdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        result_type tmp = exp(a0);
        tmp *= exp(-tmp);
#ifndef BOOST_SIMD_NO_INFINITIES
        return if_zero_else(eq(a0, Inf<A0>()), tmp);
#else
        return tmp;
#endif
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( evpdf_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        result_type tmp = exp((a0-a1));
        tmp *= exp(-tmp);
#ifndef BOOST_SIMD_NO_INFINITIES
        return if_zero_else(eq(a0, Inf<A0>()), tmp);
#else
        return tmp;
#endif
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( evpdf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "sigma parameter must be positive");
        A0 invsig =  rec(a2);
        result_type tmp = exp((a0-a1)*invsig);
        tmp *= exp(-tmp)*invsig;
#ifndef BOOST_SIMD_NO_INFINITIES
        return if_zero_else(eq(a0, Inf<A0>()), tmp);
#else
        return tmp;
#endif

      }
  };

} }

#endif
