//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_CONTAINER_CUMMAX_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_CONTAINER_CUMMAX_HPP_INCLUDED

#include <nt2/swar/functions/cummax.hpp>
#include <boost/simd/swar/functions/cummax.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct size_of<boost::simd::tag::cummax_,Domain, N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<boost::simd::tag::cummax_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
