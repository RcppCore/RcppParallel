//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_KRON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_KRON_HPP_INCLUDED

#include <nt2/core/functions/kron.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Generates kron from 2 scalar
  BOOST_DISPATCH_IMPLEMENT( kron_, tag::cpu_,
                            (A0)(A1),
                            (scalar_<unspecified_<A0>>)
                            (scalar_<unspecified_<A1>>)
                          )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1 & a1) const
    {
      return a0*a1;
    }
  };

  /// INTERNAL ONLY
  /// Generates kron from  one scalar one expression one scalar
  BOOST_DISPATCH_IMPLEMENT( kron_, tag::cpu_,
                            (A0)(A1),
                            ((ast_<A0, nt2::container::domain>))
                            (scalar_<unspecified_<A1>>)
                          )
  {
      BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                             a0*a1)
  };

  /// INTERNAL ONLY
  /// Generates kron from one expression one scalar
  BOOST_DISPATCH_IMPLEMENT( kron_, tag::cpu_,
                            (A0)(A1),
                            (scalar_<unspecified_<A0>>)
                            ((ast_<A1, nt2::container::domain>))
                          )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           a0*a1)
  };
  /// INTERNAL ONLY
  /// Generates kron from 2 expressions
  // The algorithm is based on a Bruno Luong Maylab one so :
  // Copyright (c) 2009, Bruno Luong
  // All rights reserved.

  // Redistribution and use in source and binary forms, with or without
  // modification, are permitted provided that the following conditions are
  // met:

  //     * Redistributions of source code must retain the above copyright
  //       notice, this list of conditions and the following disclaimer.
  //     * Redistributions in binary form must reproduce the above copyright
  //       notice, this list of conditions and the following disclaimer in
  //       the documentation and/or other materials provided with the distribution

  // THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  // AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  // IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  // ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  // LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  // CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  // SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  // INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  // CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  // ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  // POSSIBILITY OF SUCH DAMAGE.
  BOOST_DISPATCH_IMPLEMENT( kron_, tag::cpu_,
                            (A0)(A1),
                            ((ast_<A0, nt2::container::domain>))
                            ((ast_<A1, nt2::container::domain>))
                          )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           (nt2::reshape(bsxfun(nt2::functor<tag::multiplies_>()
                                               , reshape(a0, 1, height(a0), 1, width(a0))
                                               , reshape(a1, height(a1), 1, width(a1), 1))
                                        , height(a0)*height(a1), width(a0)*width(a1)
                                        ))
                           )
  };
} }

#endif
