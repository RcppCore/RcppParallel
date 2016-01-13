//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ABS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/abs.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( abs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type utype;

      utype mask = a0 >> (sizeof(result_type)*8 - 1);
      return (a0 + mask) ^ mask;
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( abs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      #ifdef BOOST_SIMD_HAS_FABSF
       return ::fabsf(a0);
      #else
       return (a0 > 0) ? a0 : -a0;
      #endif
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( abs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
       return ::fabs(a0);
    }
  };
  BOOST_DISPATCH_IMPLEMENT          ( abs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( abs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< bool_<A0> >)
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
