//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED

#include <nt2/euler/functions/erfc.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<double_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 lim1 = nt2::splat<A0>(0.65);
      A0 lim2 = nt2::splat<A0>(2.2);
      A0 lim3 = nt2::splat<A0>(6);
      bA0 less_0 = nt2::is_ltz(a0);
      bA0 less_l1 = nt2::lt(x, lim1);
      A0 r1 = nt2::Zero<A0>();

      std::size_t nb = nt2::inbtrue(less_l1);
      if(nb > 0)// x <  0.65
      {
        r1 = nt2::oneminus(x*details::erf_kernel<A0>::erf1(xx));
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(less_0, nt2::Two<A0>()-r1, r1);
      }
      bA0 less_l2 = nt2::lt(x, lim2);
      bA0 in_l1_l2 = nt2::logical_andnot(less_l2, less_l1);
      A0 ex = nt2::exp(-xx);

      std::size_t nb1 = nt2::inbtrue(in_l1_l2);
      if(nb1 > 0) // x >= 0.65 && x <  2.2
      {
        A0 z = ex*details::erf_kernel<A0>::erfc2(x);
        r1 = nt2::if_else(in_l1_l2, z, r1);
        nb += nb1;
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(less_0, Two<A0>()-r1, r1);
      }

      bA0 less_l3 = nt2::lt(x, lim3);
      bA0 in_l2_l3 = nt2::logical_andnot(less_l3, less_l2);

      std::size_t nb2 = nt2::inbtrue(in_l2_l3);
      if(nb2 > 0) // x >= 2.2  && x < 6
      {
        A0 z =  ex*details::erf_kernel<A0>::erfc3(x);
        r1 = nt2::if_else(in_l2_l3, z, r1);
        nb += nb2;
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(less_0, Two<A0>()-r1, r1);
      }
      bA0 in_l3_inf = nt2::logical_not(less_l3);
      A0 z = ex*details::erf_kernel<A0>::erfc4(rec(x));
      r1 = nt2::if_else(in_l3_inf, z, r1);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return  nt2::if_else(less_0, nt2::Two<A0>()-r1, r1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<single_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      bA0 less_0 = nt2::is_ltz(a0);
      A0 r1 = nt2::Zero<A0>();
      bA0 less_l1 = nt2::lt(x, Twothird<A0>());
      A0 z = x/oneplus(x);

      std::size_t nb = nt2::inbtrue(less_l1);
      if(nb > 0)
      {
        r1 = details::erf_kernel<A0>::erfc3(z);
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(less_0, nt2::Two<A0>()-r1, r1);
      }
      z -= nt2::splat<A0>(0.4);
      A0 r2 = exp(-sqr(x))*details::erf_kernel<A0>::erfc2(z);
      r1 = if_else(less_l1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return nt2::if_else(less_0, nt2::Two<A0>()-r1, r1);
    }
  };
} }

#endif
