//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SQRS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SQRS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/sqrs.hpp>
#include <boost/simd/include/functions/scalar/sqr.hpp>
#include <boost/simd/include/functions/scalar/abss.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/sqrtvalmax.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( sqrs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return abss(a0) > boost::simd::Sqrtvalmax<result_type>() ? boost::simd::Valmax<result_type>() : sqr(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( sqrs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0 > boost::simd::Sqrtvalmax<result_type>() ? boost::simd::Valmax<result_type>() : sqr(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( sqrs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return sqr(a0);
    }
  };
} } }

#endif
