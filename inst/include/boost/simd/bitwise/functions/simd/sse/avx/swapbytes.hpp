//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_SIMD_AVX_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_SIMD_AVX_SWAPBYTES_HPP_INCLUDED

#include <boost/simd/bitwise/functions/swapbytes.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/simd/native.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, boost::simd::tag::avx_
                          , (A0)
                          , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                          )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                   stype;
      typedef simd::native<stype, boost::simd::tag::sse_ >        svtype;

      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      return _mm256_insertf128_si256(_mm256_castsi128_si256(boost::simd::swapbytes(a00))
                                    , boost::simd::swapbytes(a01), 1);
    }
  };
} } }

#endif
