//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_CONSTANTS_FASTGAMMALARGELIM_HPP_INCLUDED
#define NT2_EULER_CONSTANTS_FASTGAMMALARGELIM_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Fastgammalargelim, double
                                , 0, 0x41200000         // 10.f
                                , 0x4040800000000000ll  // 30.
                                )
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::Fastgammalargelim, Site> dispatching_Fastgammalargelim(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::Fastgammalargelim, Site>();
    }
    template<class... Args>
    struct impl_Fastgammalargelim;
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Fastgammalargelim, Fastgammalargelim);
}

#endif
