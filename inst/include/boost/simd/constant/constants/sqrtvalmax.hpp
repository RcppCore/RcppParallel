//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sqrtvalmax generic tag

     Represents the Sqrtvalmax constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Sqrtvalmax : ext::pure_constant_<Sqrtvalmax>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Sqrtvalmax> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename Target::type
                          , typename Target::
                            type( (typename Target::type(1)
                                  << (sizeof(typename Target::type)*CHAR_BIT/2))-1
                                )
                          >
      {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Sqrtvalmax( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply< boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x5f800000> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x5ff0000000000001ll> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<T, 11> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<T, 181> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int32_<T>,Dummy>
          : meta::int_c<T, 46340> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int64_<T>,Dummy>
          : meta::int_c<T, 3037000499ll> {};
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Sqrtvalmax, Site> dispatching_Sqrtvalmax(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Sqrtvalmax, Site>();
   }
   template<class... Args>
   struct impl_Sqrtvalmax;
  }
  /*!
    Generates the square root of the greatest finite representable value

    @par Semantic:

    @code
    T r = Sqrtvalmax<T>();
    @endcode

    is similar to:

    @code
    T r =  sqrt(Valmax<T>();
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrtvalmax, Sqrtvalmax)
} }

#include <boost/simd/constant/common.hpp>

#endif
