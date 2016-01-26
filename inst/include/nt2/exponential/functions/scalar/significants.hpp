//==============================================================================
//          Copyright 2015 - J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SIGNIFICANTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SIGNIFICANTS_HPP_INCLUDED

#include <nt2/exponential/functions/significants.hpp>
#include <nt2/include/functions/scalar/round.hpp>
#include <nt2/include/functions/scalar/tenpower.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/if_zero_else.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/functions/scalar/log10.hpp>
#include <nt2/include/functions/scalar/minus.hpp>
#include <nt2/include/functions/scalar/iceil.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#endif

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( significants_, tag::cpu_
                          , (A0)(A1)
                          , ((scalar_< floating_<A0>>))
                            ((scalar_< integer_<A1>>))
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( assert_all(is_gtz(a1))
                      , "Number of significant digits must be positive"
                      );
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0;
      if (is_eqz(a0)) return a0;
      iA0 exp = a1 - iceil(log10(abs(a0)));
      A0 fac = tenpower(exp);
      A0 scaled = round(a0*fac);
#ifndef BOOST_SIMD_NO_INVALIDS
      A0 r = if_else(is_invalid(a0), a0, scaled/fac);
#else
      A0 r =  scaled/fac;
#endif
      return r;
    }
  };

} }

#endif
