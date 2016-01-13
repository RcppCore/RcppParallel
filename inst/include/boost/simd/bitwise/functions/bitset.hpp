//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_BITSET_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_BITSET_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  bitset generic tag

      Represents the bitset function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct bitset_ : ext::elementwise_<bitset_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitset_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_bitset_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::bitset_, Site> dispatching_bitset_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::bitset_, Site>();
    }
    template<class... Args>
    struct impl_bitset_;
  }
  /*!
    Returns x with the ith bit set

    @par semantic:
    For any given value @c x of type @c T, i  of type @c I:

    @code
    as_integer<T> r = bitset(x, i);
    @endcode

    @see  @funcref{bitset}
    @param  x
    @param  i

    @return      a value of the type of the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitset_, bitset, 2)
} }

#endif
