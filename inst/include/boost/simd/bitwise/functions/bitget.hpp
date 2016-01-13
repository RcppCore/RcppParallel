//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_BITGET_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_BITGET_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  bitget generic tag

      Represents the bitget function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct bitget_ : ext::elementwise_<bitget_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitget_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_bitget_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::bitget_, Site> dispatching_bitget_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::bitget_, Site>();
    }
    template<class... Args>
    struct impl_bitget_;
  }
  /*!
    Returns the value of th ith bit in x as an unsigned integer

    @par semantic:
    For any given value @c x of type @c T, i  of type @c I:

    @code
    as_integer<T> r = bitget(x, i);
    @endcode

    r contains is 0 or 2^i according to the fact the ith bit of x is 0 or 1

    @see  @funcref{bitset}
    @param  x
    @param  i

    @return      a value of the unsigned integer type associated to the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitget_, bitget, 2)
} }

#endif
