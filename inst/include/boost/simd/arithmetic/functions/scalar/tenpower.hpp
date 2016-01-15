//==============================================================================
//         Copyright 2015 - J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TENPOWER_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TENPOWER_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/tenpower.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/scalar/is_odd.hpp>
#include <boost/simd/include/functions/scalar/rec.hpp>
#include <boost/dispatch/attributes.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( tenpower_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef  typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 exp) const
    {
      result_type result = One<result_type>();
      result_type base = Ten<result_type>();
      bool neg = exp < 0;
      exp =  boost::simd::abs(exp);
      while(exp)
      {
        if (is_odd(exp)) result *= base;
        exp >>= 1;
        base = sqr(base);
      }
      return neg ? rec(result) : result;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( tenpower_, tag::cpu_
                            , (A0)
                            , (scalar_< uint_<A0> >)
                            )
  {
    typedef  typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 exp) const
    {
      result_type result = One<result_type>();
      result_type base = Ten<result_type>();
      while(exp)
      {
        if (is_odd(exp)) result *= base;
        exp >>= 1;
        base = sqr(base);
      }
      return result;
    }
  };
} } }

#endif
