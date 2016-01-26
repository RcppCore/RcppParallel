//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED

#include <nt2/dsl/functions/evaluate.hpp>
#include <nt2/include/functions/run.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( evaluate_
                                    , tag::formal_
                                    , (A0)(D)
                                    , ((ast_<A0, D>))
                                    )
  {
    typedef typename boost::dispatch::meta::call<nt2::tag::run_(A0&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return nt2::run(a0);
    }
  };
} }

#endif
