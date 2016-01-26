//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_LENGTH_HPP_INCLUDED

#include <nt2/core/functions/length.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( length_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::
            call<tag::length_(typename A0::extent_type)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::length( a0.extent() );
    }
  };
} }

#endif
