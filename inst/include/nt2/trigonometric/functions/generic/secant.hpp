//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_SECANT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_SECANT_HPP_INCLUDED
#include <nt2/trigonometric/functions/secant.hpp>
#include <nt2/include/functions/simd/cosine.hpp>
#include <nt2/include/functions/simd/rec.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT_G( nt2::tag::secant_<mode>, tag::cpu_
                            , (A0)(mode)
                            , (generic_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::rec(nt2::cosine<mode>(a0));
    }
  };
} }

#endif
