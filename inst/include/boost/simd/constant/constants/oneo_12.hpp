//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_12_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_12_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneo_12 generic tag

     Represents the Oneo_12 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_12, double, 0
                                , 0x3daaaaab, 0x3fb5555555555555ll
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Oneo_12, Site> dispatching_Oneo_12(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Oneo_12, Site>();
   }
   template<class... Args>
   struct impl_Oneo_12;
  }
  /*!
    Generates value 1/12

    @par Semantic:

    @code
    T r = Oneo_12<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(12);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_12, Oneo_12)
} }

#include <boost/simd/constant/common.hpp>

#endif

