//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_EXPRECNEGC_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_EXPRECNEGC_HPP_INCLUDED

#include <nt2/exponential/functions/exprecnegc.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>

namespace nt2 {
  namespace ext {
    BOOST_DISPATCH_IMPLEMENT  ( exprecnegc_, tag::cpu_
                                , (A0)
                                , (generic_< floating_<A0> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(1)
      {
        return -expm1(-rec(a0));
      }
    };
  }
}

#endif
