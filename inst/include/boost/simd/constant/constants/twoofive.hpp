//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TWOOFIVE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TWOOFIVE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Twoofive generic tag

     Represents the Twoofive constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twoofive, double, 0
                                , 0x3ecccccd, 0x3fd999999999999all
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Twoofive, Site> dispatching_Twoofive(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Twoofive, Site>();
   }
   template<class... Args>
   struct impl_Twoofive;
  }
  /*!
   Generates value 2/5 == 0.4

    @par Semantic:

    @code
    T r = Twoofive<T>();
    @endcode

    is similar to:

    @code
    T r = T(2)/T(5);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twoofive, Twoofive)
} }

#include <boost/simd/constant/common.hpp>

#endif

