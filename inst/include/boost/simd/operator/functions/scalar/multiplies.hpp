//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/times.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT ( multiplies_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0 * a1; }
  };

  BOOST_DISPATCH_IMPLEMENT ( multiplies_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint16_<A0> >)
                                      (scalar_< uint16_<A0> >)
                                    )
  {
    /* When multiplying two unsigned chars or two unsigned shorts, promotion to int occurs.
     * Therefore 65535*65535 (2^32) of two unsigned short produces a signed integer overflow, which is UB.
     * We want unsigned multiplication of two integers to be well-defined regardless of size, hence this special case.
     *
     * The problem could also occur for unsigned char but it is assumed that 'int' is 32-bit, and therefore
     * large enough to contain 2^16 even in signed.
     */
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return A0((unsigned int)a0 * (unsigned int)a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT ( multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                                      (mpl_integral_< scalar_< arithmetic_<A1> > >)
                                    )
  {
    typedef typename mpl::times<A0, A1>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const&) const
    {
      return result_type();
    }
  };

  BOOST_DISPATCH_IMPLEMENT ( multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< arithmetic_<A0> >)
                                      (mpl_integral_< scalar_< arithmetic_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return a0*A1::value;
    }
  };

  BOOST_DISPATCH_IMPLEMENT ( multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                                      (scalar_< arithmetic_<A1> >)
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1) const
    {
      return a1*A0::value;
    }
  };
} } }

#endif
