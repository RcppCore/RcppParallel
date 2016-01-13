//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MINEXPONENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MINEXPONENT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Minexponent generic tag

     Represents the Minexponent constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Minexponent : ext::pure_constant_<Minexponent>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Minexponent> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Minexponent( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Minexponent::apply<boost::dispatch::meta::single_<T>,Dummy>
      : meta::int_c<boost::simd::int32_t,-126> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Minexponent::apply<boost::dispatch::meta::double_<T>,Dummy>
        : meta::int_c<boost::simd::int64_t,-1022> {};
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Minexponent, Site> dispatching_Minexponent(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Minexponent, Site>();
   }
   template<class... Args>
   struct impl_Minexponent;
  }
  /*!
    Generates the smallest floating point exponent.

    @par Semantic:

    @code
    T r = Minexponent<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r =  -1022;
    else if T is float
      r = -126;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Minexponent, Minexponent)
} }

#include <boost/simd/constant/common.hpp>

#endif
