//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMAX_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMAX_HPP_INCLUDED

#include <boost/simd/swar/functions/cummax.hpp>
#include <boost/simd/swar/functions/cummin.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/swar/include/functions/shuffle.hpp>
#include <boost/simd/swar/functions/details/cum_helper.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT ( cummax_, tag::cpu_
                           , (A0)(X)
                           , ((simd_<arithmetic_<A0>,X>))
                           )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return helper<meta::cardinal_of<A0>::value>::unroll(a0);
    }

    private:

    template<std::size_t CARD, std::size_t PASS = CARD>
    struct helper
    {
      BOOST_FORCEINLINE static A0 unroll(const A0 & a0)
      {
        A0 tmp =  helper<CARD, PASS/2>::unroll(a0);
        return max(tmp,  shuffle<details::cum_helper<CARD, PASS>>(tmp));
      }
    };

    template<std::size_t CARD> struct helper<CARD, 0>
    {
      BOOST_FORCEINLINE static A0 unroll(const A0 & a0)
      {
        return a0;
      }
    };

  };
} } }

#endif
