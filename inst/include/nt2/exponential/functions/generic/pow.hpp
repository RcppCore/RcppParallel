//==============================================================================
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NUMSCALE SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_HPP_INCLUDED

#include <nt2/exponential/functions/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  template<unsigned long long Exp, unsigned long long Odd = Exp%2>
  struct pow_expander;

  template<unsigned long long Exp>
  struct pow_expander<Exp, 0ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call(A0 const& a0)
    {
      return pow_expander<Exp/2>::call(sqr(a0));
    }
  };

  template<unsigned long long Exp>
  struct pow_expander<Exp, 1ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call(A0 const& a0)
    {
      return a0*pow_expander<Exp/2>::call(sqr(a0));
    }
  };

  template<>
  struct pow_expander<0ULL, 0ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call(A0 const&)
    {
      return One<A0>();
    }
  };

  template<>
  struct pow_expander<0ULL, 1ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call(A0 const&)
    {
      return One<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (mpl_integral_< scalar_< uint_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return pow_expander<A1::value>::call(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (mpl_integral_< scalar_< int_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return eval(a0, boost::mpl::bool_<(A1::value >= 0)>());
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, boost::mpl::true_) const
    {
      return pow_expander<A1::value>::call(a0);
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, boost::mpl::false_) const
    {
      return pow_expander<-A1::value>::call(rec(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (scalar_< uint_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 base = a0;
      A1 exp = a1;

      result_type result = One<result_type>();
      while(exp)
      {
        if(is_odd(exp))
            result *= base;
        exp >>= 1;
        base = sqr(base);
      }

      return result;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< integer_<A0> >)
                              (generic_< int_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( boost::simd::assert_all(a1 >= 0), "integral pow with signed exponent" );

      typedef typename meta::as_unsigned<A1>::type utype;
      return pow(a0, bitwise_cast<utype>(a1));
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< int_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_unsigned<A1>::type utype;
      typename meta::as_logical<A1>::type ltza1 = is_ltz(a1);
      result_type p = pow(a0, bitwise_cast<utype>(negif(ltza1, a1)));
      return if_else(ltza1, rec(p), p);
    }
  };
} }

#endif
