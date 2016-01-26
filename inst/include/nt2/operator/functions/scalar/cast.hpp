//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_SCALAR_CAST_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_SCALAR_CAST_HPP_INCLUDED

#include <nt2/operator/functions/cast.hpp>

namespace nt2 { namespace ext
{
  // scalar impl general
  BOOST_DISPATCH_IMPLEMENT  ( cast_, tag::cpu_
                            , (A0)(To)
                            , (scalar_< unspecified_<A0> >)
                              (target_< scalar_< unspecified_<To> > >)
                            )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return result_type(a0);
    }
  };
} }

#endif
