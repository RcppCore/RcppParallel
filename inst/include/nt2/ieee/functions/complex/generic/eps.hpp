//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_EPS_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_EPS_HPP_INCLUDED
#include <nt2/ieee/functions/eps.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( eps_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::eps(nt2::abs(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( eps_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::eps(nt2::real(a0));
    }
  };

} } }

#endif
