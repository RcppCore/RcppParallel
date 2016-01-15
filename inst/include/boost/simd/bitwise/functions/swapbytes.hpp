//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SWAPBYTES_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  swapbytes generic tag

      Represents the swapbytes function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct swapbytes_ : ext::elementwise_<swapbytes_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<swapbytes_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_swapbytes_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::swapbytes_, Site> dispatching_swapbytes_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::swapbytes_, Site>();
    }
    template<class... Args>
    struct impl_swapbytes_;
  }
  /*!
    Reverse the byte order of each scalar value

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = swapbytes(x);
    @endcode


    @param  x

    @return      a value of the unsigned integer type associated to the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::swapbytes_, swapbytes, 1)
} }

#endif
