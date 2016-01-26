//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_GENERIC_DB2POW_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_GENERIC_DB2POW_HPP_INCLUDED

#include <nt2/signal/functions/db2pow.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp10.hpp>
#include <nt2/include/constants/ten.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( db2pow_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return sqrt(a1)*nt2::exp10(a0/Two<result_type>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( db2pow_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::exp10(a0/Two<result_type>());
    }
  };
} }

#endif
