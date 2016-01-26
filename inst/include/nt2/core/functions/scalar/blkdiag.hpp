//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/include/functions/cons.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( blkdiag_, tag::cpu_, (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 const& result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      return a;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( blkdiag_, tag::cpu_, (A0)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                            )
  {
    typedef nt2::container::table<A0,of_size_<2,2> >  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return nt2::cons<A0>(nt2::of_size(2,2),a0,A0(0),A0(0),a1);
    }
  };
} }

#endif
