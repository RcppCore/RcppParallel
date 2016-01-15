//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLIT_LOW_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief split_low generic tag

     Represents the split_low function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct split_low_ : ext::unspecified_<split_low_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<split_low_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_split_low_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::split_low_, Site> dispatching_split_low_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::split_low_, Site>();
   }
   template<class... Args>
   struct impl_split_low_;
  }

  /*!
    @brief SIMD register type-based split_low

    @c split_low extract the lower half of a SIMD register and convert it
    to the appropriate SIMD register type of corresponding cardinal.

    @see split_low, split, slice
    @param a0 Value to process

    @return THe lower half of a0 converted to the appropriate SIMD type
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::split_low_, split_low, 1)
} }

#endif
