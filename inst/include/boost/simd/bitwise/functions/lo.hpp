//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_LO_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_LO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  lo generic tag

      Represents the lo function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct lo_ : ext::elementwise_<lo_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<lo_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lo_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lo_, Site> dispatching_lo_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lo_, Site>();
    }
    template<class... Args>
    struct impl_lo_;
  }
  /*!
    Returns the low part of the entry
    as an unsigned integer of the size of
    the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T,unsigned> r = lo(x);
    @endcode

    @see  @funcref{hi}
    @param  a0

    @return      a value of the unsigned integer
    type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lo_, lo, 1)
} }

#endif
