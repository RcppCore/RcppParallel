//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_PLUS_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_PLUS_HPP_INCLUDED

#include <nt2/operator/functions/plus.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

// for optimize
#include <nt2/include/functions/fma.hpp>

namespace boost { namespace simd { namespace ext
{
  // complex/complex
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type( nt2::real(a0) + nt2::real(a1)
                        , nt2::imag(a0) + nt2::imag(a1)
                        );
    }
  };

  // complex/real
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type( nt2::real(a0) + nt2::real(a1)
                        , nt2::imag(a1)
                        );
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type( nt2::real(a0) + nt2::real(a1)
                        , nt2::imag(a0)
                        );
    }
  };

  // dry/complex
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename nt2::meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(nt2::real(a1)+nt2::real(a0), nt2::imag(a1));
    }
  };

  // complex/dry
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > > )
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef typename nt2::meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(nt2::real(a0)+nt2::real(a1), nt2::imag(a0));
    }
  };

  // dry/arithmetic
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(nt2::real(a0)+a1);
    }
  };

  // arithmetic/dry
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)

                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(nt2::real(a1)+a0);
    }
  };

  // dry/dry
  BOOST_DISPATCH_IMPLEMENT  ( plus_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< dry_< arithmetic_<A0> > >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<result_type>(nt2::real(a0)+nt2::real(a1));
    }
  };

} } }

#endif
