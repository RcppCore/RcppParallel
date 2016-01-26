//==============================================================================
//         Copyright 2015 J.T.Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_BETALN_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_BETALN_HPP_INCLUDED

#include <nt2/euler/functions/betaln.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_nltz.hpp>
#include <boost/assert.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( betaln_, tag::cpu_
                            , (A0)
                            , ((generic_<floating_<A0>>))
                              ((generic_<floating_<A0>>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_ASSERT_MSG(boost::simd::assert_all(logical_and(is_nltz(a0),is_nltz(a1))), "inputs must be positive");
      return(gammaln(a0)+gammaln(a1)-gammaln(a0+a1));
    }
  };
} }

#endif
