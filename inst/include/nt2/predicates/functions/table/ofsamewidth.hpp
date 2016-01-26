//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_OFSAMEWIDTH_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_OFSAMEWIDTH_HPP_INCLUDED

#include <nt2/predicates/functions/ofsamewidth.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( ofsamewidth_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return width(a0) == width(a1);
    }
  };
} }

#endif
