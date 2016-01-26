//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_RANDN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_RANDN_HPP_INCLUDED

#include <nt2/core/functions/randn.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/core/utility/randstream.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // randn evaluation
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1,nt2::tag::randn_
                                      , boost::mpl::long_<2>
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      // Setup lhs memory using size informations from rhs
      a0.resize( boost::proto::value(boost::proto::child_c<0>(a1)) );

      // Forward to current randnom_stream and fill the data
      current_prng_.generator_->randn(a0.data(),0,nt2::numel(a0));

      return a0;
    }
  };
} }

#endif
