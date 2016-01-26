//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERFCX_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERFCX_HPP_INCLUDED

#include <nt2/euler/functions/erfcx.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/functions/scalar/erfc.hpp>
#include <nt2/include/functions/scalar/expx2.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/six.hpp>
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

#include <boost/simd/sdk/config.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( erfcx_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if(a0 == Inf<A0>()) return Zero<A0>();
      if(nt2::is_nan(a0)) return a0;
#endif
      if(a0 < 0.65)
      {
        return expx2(a0)*erfc(a0);
      }
      else if (a0 < 2.2)
      {
        return details::erf_kernel<A0>::erfc2(a0);
      }
      else if(a0< A0(6))
      {
        return details::erf_kernel<A0>::erfc3(a0);
      }
      else
      {
        return details::erf_kernel<A0>::erfc4(rec(a0));
      }
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( erfcx_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if(a0 == Inf<A0>()) return Zero<A0>();
      if(nt2::is_nan(a0)) return a0;
#endif
      if(a0 < Twothird<A0>())
      {
        return expx2(a0)*erfc(a0);
      }
      else
      {
        A0 z =  a0/oneplus(a0)- 0.4f;
        return details::erf_kernel<A0>::erfc2(z);
      }
    }
  };
} }

#endif
