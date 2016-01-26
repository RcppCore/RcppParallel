//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO2_1_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO2_1_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>
namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio2_1 generic tag

     Represents the Pio2_1 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 1.57079632673412561417e+00
    BOOST_SIMD_CONSTANT_REGISTER( Pio2_1, double
                                , 1, 0x3fc90f80
                                , 0x3FF921FB54400000ll
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Pio2_1, Site> dispatching_Pio2_1(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Pio2_1, Site>();
   }
   template<class... Args>
   struct impl_Pio2_1;
  }
  /*!
    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio2_1<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio2_1, Pio2_1);
}

#endif

