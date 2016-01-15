//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SWAPBYTES_HPP_INCLUDED

#include <boost/simd/bitwise/functions/swapbytes.hpp>
#include <boost/simd/include/functions/shuffle.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    template<std::size_t N> struct swap_bytes_helper
    {
      template<typename I, typename C>
      struct apply : boost::mpl::int_<N*(I::value/N)+N-1-I::value%N>
      {};
    };
  }
} }

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( swapbytes_,  tag::simd_
                          , (A0)(X)
                          , ((simd_<arithmetic_<A0>, X>))
                          )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      using s0        = typename meta::scalar_of<A0>::type;
      using i8        = typename meta::vector_of<uint8_t, sizeof(A0)>::type;
      using pattern_t = details::swap_bytes_helper<sizeof(s0)>;

      return bitwise_cast<A0>(shuffle<pattern_t>(bitwise_cast<i8>(a0)));
    }
  };
} } }

#endif
