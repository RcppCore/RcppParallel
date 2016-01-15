//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FLOOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  floor generic tag

      Represents the floor function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct floor_ : ext::elementwise_<floor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<floor_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_floor_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::floor_, Site> dispatching_floor_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::floor_, Site>();
    }
    template<class... Args>
    struct impl_floor_;
  }
  /*!
    Computes the floor of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = floor(x);
    @endcode

    greatest integral value of type @c T less or equal to @c x.

    @see  @funcref{ceil}, @funcref{round}, @funcref{round2even}}, @funcref{trunc}, @funcref{ifloor}
    @param  a0

    @return      an integral value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::floor_, floor, 1)
} }

#endif
