//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_COTANGENT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_COTANGENT_HPP_INCLUDED
#include <nt2/trigonometric/functions/cotangent.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo.hpp>
#include <nt2/trigonometric/functions/simd/common/impl/trigo.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT_G( nt2::tag::cotangent_<mode>, tag::cpu_
                            , (A0)(mode)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    typedef typename boost::simd::meta::is_native<A0>::type is_native_t;
    NT2_FUNCTOR_CALL(1)
    {
      return details::trig_base<A0,radian_tag,is_native_t,mode>::cota(a0);
    }
  };
} }

#endif
