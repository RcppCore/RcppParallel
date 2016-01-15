//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_NOT_IMAG_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_NOT_IMAG_HPP_INCLUDED

#include <boost/simd/predicates/functions/is_not_imag.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( is_not_imag_, tag::cpu_
                          , (A0)
                          , (scalar_< bool_<A0> >)
                          )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return !a0; }
  };
} } }


#endif
