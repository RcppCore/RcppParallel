//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSPI_HPP_INCLUDED
#include <nt2/trigonometric/functions/cospi.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo.hpp>
#include <nt2/trigonometric/functions/simd/common/impl/trigo.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( cospi_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::if_else(nt2::is_odd(a0),Mone<result_type>(),nt2::One<result_type>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cospi_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    typedef typename boost::simd::meta::is_native<A0>::type is_native_t;
    NT2_FUNCTOR_CALL(1)
    {
      return details::trig_base<A0,pi_tag,is_native_t,big_>::cosa(a0);
    }
  };
} }


#endif
