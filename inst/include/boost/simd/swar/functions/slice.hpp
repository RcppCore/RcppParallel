//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SLICE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SLICE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief slice generic tag

      Represents the slice function in generic contexts.
    **/
    struct slice_ : ext::unspecified_<slice_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<slice_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_slice_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::slice_, Site> dispatching_slice_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::slice_, Site>();
    }
    template<class... Args>
    struct impl_slice_;
  }

  /*!
    @brief SIMD register type-based slicing

    @c slice slices a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v.

    @param a0 Value to splice

    @return A Fusion Sequence containing the two sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::slice_, slice, 1)

  /*!
    @brief SIMD register type-based slice

    @c slice slices a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v.

    @param a0 Value to slice
    @param a1 L-Value that will receive the second sub-part of @c a0

    @return The first sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::slice_, slice
                                            , (A0 const &)(A1&)
                                            , 2
                                            )

  /*!
    @brief SIMD register type-based slice

    @c slice slices a SIMD register @c v in two SIMD register of half the
    cardinal of @c v containing the same value than @c v.

    @param a0 Value to slice
    @param a1 L-Value that will receive the first sub-part of @c a0
    @param a2 L-Value that will receive the second sub-part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::slice_, slice
                                            , (A0 const &)(A1&)(A1&)
                                            , 2
                                            )

} }

#endif
