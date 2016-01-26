//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SQUEEZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SQUEEZE_HPP_INCLUDED

#include <nt2/core/functions/squeeze.hpp>

#include <nt2/memory/functions/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates squeeze
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( squeeze_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::squeeze_
                                          , container::domain
                                          , A0&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto::
              make_expr < nt2::tag::squeeze_
                        , container::domain
                        > ( boost::ref(a0) );
    }
  };
} }

#endif
