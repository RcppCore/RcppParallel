//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_SIGNIFICANTS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_SIGNIFICANTS_HPP_INCLUDED

#include <nt2/exponential/functions/significants.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( significants_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(significants(nt2::real(a0), a1),significants(nt2::imag(a0), a1));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( significants_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< dry_<floating_<A0> > >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(nt2::significants(nt2::real(a0), a1));
    }
  };
} }


#endif
