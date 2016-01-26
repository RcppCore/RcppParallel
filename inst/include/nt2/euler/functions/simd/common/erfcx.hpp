//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFCX_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFCX_HPP_INCLUDED

#include <nt2/euler/functions/erfcx.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/functions/simd/erfc.hpp>
#include <nt2/include/functions/simd/expx2.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/twoofive.hpp>
#include <nt2/include/constants/six.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#endif

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( erfcx_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<double_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 lim1 = nt2::splat<A0>(0.65);
      A0 lim2 = nt2::splat<A0>(2.2);
      A0 lim3 = Six<A0> ();
      bA0 less_l1 = nt2::lt(a0, lim1);
      A0 r1 = nt2::Zero<A0>();
      std::size_t nb = nt2::inbtrue(less_l1);
      if(nb > 0)
      {
        r1 = expx2(a0)*erfc(a0);
        if (nb >= meta::cardinal_of<A0>::value)
          return r1;
      }

      bA0 less_l2 = nt2::lt(a0, lim2);
      bA0 in_l1_l2 = nt2::logical_andnot(less_l2, less_l1);
      std::size_t nb1 = nt2::inbtrue(in_l1_l2);
      if(nb1 > 0)
      {
        nb += nb1;
        r1 = nt2::if_else(in_l1_l2, details::erf_kernel<A0>::erfc2(a0), r1);
        if (nb >= meta::cardinal_of<A0>::value)
          return r1;
      }

      bA0 less_l3 = nt2::lt(a0, lim3);
      bA0 in_l2_l3 = nt2::logical_andnot(less_l3, less_l2);
      nb1 = nt2::inbtrue(in_l2_l3);
      if(nb1 > 0)
      {
        nb += nb1;
        r1 = nt2::if_else(in_l2_l3, details::erf_kernel<A0>::erfc3(a0), r1);
        if (nb >= meta::cardinal_of<A0>::value)
          return r1;
      }

      bA0 in_l3_inf = nt2::logical_not(less_l3);

      r1 = nt2::if_else(in_l3_inf, details::erf_kernel<A0>::erfc4(rec(a0)), r1);
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_zero_else(eq(a0, Inf<A0>()), r1);
      #else
      return r1;
      #endif
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( erfcx_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<single_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 r = if_else(is_less(a0,  Twothird<A0>())
                    , expx2(a0)*erfc(a0)
                    , details::erf_kernel<A0>::erfc2(a0/oneplus(a0)-Twoofive<A0>())
                    );
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_zero_else(eq(a0, Inf<A0>()), r);
      #else
      return r;
      #endif
    }
  };

} }

#endif
