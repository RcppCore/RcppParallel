//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWENTY_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWENTY_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twenty generic tag

     Represents the Twenty constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Twenty,double,20, 0x41a00000,0x4034000000000000ll)
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Twenty, Site> dispatching_Twenty(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Twenty, Site>();
   }
   template<class... Args>
   struct impl_Twenty;
  }
  /*!
    Generates value 20

    @par Semantic:

    @code
    T r = Twenty<T>();
    @endcode

    is similar to:

    @code
    T r = T(20);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twenty, Twenty)
} }

#include <boost/simd/constant/common.hpp>

#endif
