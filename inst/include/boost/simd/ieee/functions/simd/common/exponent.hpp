//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_EXPONENT_HPP_INCLUDED

#include <boost/simd/ieee/functions/exponent.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/exponentbits.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>

#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#endif

#if defined(__INTEL_COMPILER) && defined(BOOST_SIMD_HAS_AVX_SUPPORT) && !defined(BOOST_SIMD_HAS_AVX2_SUPPORT)
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( exponent_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<integer_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return Zero<result_type>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( exponent_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {

    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type             s_type;
      const int nmb= int(Nbmantissabits<s_type>());
      result_type x = shri(exponentbits(a0), nmb);

      // workaround for ICC 14.0.3, tested on AVX
      #if defined(__INTEL_COMPILER) && defined(BOOST_SIMD_HAS_AVX_SUPPORT) && !defined(BOOST_SIMD_HAS_AVX2_SUPPORT)
      x = x - if_else(a0, Maxexponent<A0>(), Zero<result_type>());
      #else
      x = selsub(a0, x, Maxexponent<A0>());
      #endif

      #ifndef BOOST_SIMD_NO_INVALIDS
      return if_zero_else( is_invalid(a0), x );
      #else
      return x;
      #endif
    }
  };
} } }

#endif
