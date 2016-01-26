//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Averageributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MEANOF_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MEANOF_HPP_INCLUDED

#include <nt2/arithmetic/functions/meanof.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(meanof(nt2::real(a0), nt2::real(a1)),meanof(nt2::imag(a0), nt2::imag(a1))) ;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < arithmetic_<A0> > > )
                              (generic_< dry_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(meanof(nt2::real(a0), nt2::real(a1))) ;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(meanof(nt2::real(a0), nt2::real(a1)),nt2::imag(a1)*Half<A0>()) ;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_ < arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
     typedef typename nt2::meta::as_real<A0>::type rtype;
       return result_type(meanof(nt2::real(a0), nt2::real(a1)),nt2::imag(a1)*Half<rtype>()) ;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(meanof(nt2::real(a0), nt2::real(a1)),nt2::imag(a0)*Half<A1>()) ;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( meanof_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< dry_ < arithmetic_<A1> > >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename nt2::meta::as_real<A1>::type rtype;
      return result_type(meanof(nt2::real(a0), nt2::real(a1)),nt2::imag(a0)*Half<rtype>()) ;
    }
  };
} } }

#endif
