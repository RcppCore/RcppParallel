//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_COMPLEX_GENERIC_IS_NAN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_COMPLEX_GENERIC_IS_NAN_HPP_INCLUDED

#include <nt2/predicates/functions/is_nan.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  // complex
  BOOST_DISPATCH_IMPLEMENT  ( is_nan_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename  nt2::meta::as_real<A0>::type rA0;
    typedef typename meta::as_logical<rA0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return logical_or(is_nan(nt2::imag(a0)),is_nan(nt2::real(a0)));
    }
  };



  // dry
  BOOST_DISPATCH_IMPLEMENT  ( is_nan_, tag::cpu_, (A0),
                              (generic_< dry_< arithmetic_<A0> > > )
                            )
  {
    typedef typename  nt2::meta::as_real<A0>::type rA0;
    typedef typename meta::as_logical<rA0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return is_nan(nt2::real(a0));
    }
  };
} } }

#endif
