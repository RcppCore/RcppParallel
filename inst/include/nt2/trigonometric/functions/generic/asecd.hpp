//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_ASECD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_ASECD_HPP_INCLUDED

#include <nt2/trigonometric/functions/asecd.hpp>
#include <nt2/include/functions/simd/indeg.hpp>
#include <nt2/include/functions/simd/asec.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( asecd_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::indeg(nt2::asec(a0));
    }
  };
} }


#endif
