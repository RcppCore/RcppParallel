//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_REAL_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_REAL_HPP_INCLUDED
#include <boost/simd/predicates/functions/is_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( is_real_, tag::cpu_
                          , (A0)
                          , (scalar_< bool_<A0> >)
                          )
  {
    typedef bool result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return true;
    }
  };

} } }


#endif
