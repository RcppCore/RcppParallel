//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Allbits generic tag

     Represents the Allbits constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Allbits : ext::pure_constant_<Allbits>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Allbits> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c<typename Target::type, -1>
      {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Allbits( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_ < apply < boost::dispatch::meta::uint32_<uint32_t>
                                  , Dummy
                                  >::value
                          > {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_ < apply < boost::dispatch::meta::uint64_<uint64_t>
                                  , Dummy
                                  >::value
                          > {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<T, 0xFF> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<T, 0xFFFFU> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFUL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFFFFFFFFFULL> {};

  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Allbits, Site> dispatching_Allbits(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Allbits, Site>();
   }
   template<class... Args>
   struct impl_Allbits;
  }
  /*!
    Generates a value in the chosen type all bits of which are set to 1.

    @par Semantic:

    @code
    T r = Allbits<T>();
    @endcode

    is similar to

    @code
    if T is floating point
      r =  Nan<T>();
    else if T is signed integral
      r = -1;
    else
      r = Valmax<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Allbits, Allbits)
} }

#include <boost/simd/constant/common.hpp>

#endif
