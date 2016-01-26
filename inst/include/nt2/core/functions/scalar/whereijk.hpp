//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_WHEREIJK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_WHEREIJK_HPP_INCLUDED

#include <nt2/core/functions/whereijk.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( whereijk_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      return a0(0,0,0) ? a1 : a2;
    }
  };
} }

#endif

