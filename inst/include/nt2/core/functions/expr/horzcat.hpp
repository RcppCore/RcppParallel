//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HORZCAT_HPP_INCLUDED

#include <nt2/core/functions/horzcat.hpp>
#include <nt2/include/functions/cat.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates horzcat from 1 variable
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( horzcat_, tag::cpu_,
                              (A0),
                              (unspecified_<A0>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  // Generates linearize_ from 2 variables
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( horzcat_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::call < tag::cat_ ( std::size_t
                                            , A0 const&
                                            , A1 const&
                                            )
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1) const
    {
      return cat(2u,a0,a1);
    }
  };
} }

#endif
