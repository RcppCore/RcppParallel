//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_ALLBITS_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_ALLBITS_HPP_INCLUDED

#include <nt2/boolean/functions/if_else_allbits.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT   ( if_else_allbits_, tag::cpu_, (A0)(A1)
                             , (generic_< logical_<A0> >)
                               (generic_< complex_<floating_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(if_else_allbits(a0, nt2::real(a1)), if_else_allbits(a0, nt2::imag(a1)));
    }
  };
  BOOST_DISPATCH_IMPLEMENT   ( if_else_allbits_, tag::cpu_, (A0)(A1)
                             , (generic_< complex_<floating_<A0> > >)
                               (generic_< complex_<floating_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(if_else_allbits(is_nez(a0), nt2::real(a1)), if_else_allbits(is_nez(a0), nt2::imag(a1)));
    }
  };
} } }

#endif
