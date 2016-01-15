//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_SWAPBYTES_HPP_INCLUDED

#include <boost/simd/bitwise/functions/swapbytes.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< ints8_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< ints16_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
     return shl(a0, 8)|shr(a0, 8);
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< type32_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type val = ((shl(a0, 8) & 0xFF00FF00 ) | (shr(a0, 8) & 0xFF00FF ));
      return shl(val, 16) | shr(val,16);
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< type64_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type val = (shl(a0, 8) & 0xFF00FF00FF00FF00ULL ) | (shr(a0, 8) & 0x00FF00FF00FF00FFULL );
      val = (shl(val, 16) & 0xFFFF0000FFFF0000ULL ) | (shr(val, 16) & 0x0000FFFF0000FFFFULL );
      return shl(val, 32) | shr(val,32);
    }
  };
} } }

#endif
