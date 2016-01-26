//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ARG_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ARG_HPP_INCLUDED
#include <nt2/arithmetic/functions/arg.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/atan2.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( arg_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::atan2(nt2::imag(a0),nt2::real(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( arg_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::arg(nt2::real(a0));
    }
  };
} } }

#endif
