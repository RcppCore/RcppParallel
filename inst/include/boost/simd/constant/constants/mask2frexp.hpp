//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MASK2FREXP_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MASK2FREXP_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mask2frexp generic tag

     Represents the Mask2frexp constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Mask2frexp : ext::pure_constant_<Mask2frexp>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Mask2frexp> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Mask2frexp( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Mask2frexp::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,0x3f000000UL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Mask2frexp::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,0x3fe0000000000000ULL> {};

  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Mask2frexp, Site> dispatching_Mask2frexp(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Mask2frexp, Site>();
   }
   template<class... Args>
   struct impl_Mask2frexp;
  }
  /*!
    Generates the maximum exposant of floating point numbers

    @par Semantic:

    @code
    as_integer<T> r = Mask2frexp<T>();
    @endcode

    @code
    if T is double
      r =  4602678819172646912ll;
    else if T is float
      r =  1056964608;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mask2frexp, Mask2frexp)
} }

#include <boost/simd/constant/common.hpp>

#endif
