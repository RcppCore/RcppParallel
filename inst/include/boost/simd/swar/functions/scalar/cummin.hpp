//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_CUMMIN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_CUMMIN_HPP_INCLUDED

#include <boost/simd/swar/functions/cummin.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT ( cummin_, tag::cpu_
                           , (A0)
                           , (scalar_< unspecified_<A0> >)
                           )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} } }


#endif
