//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  twopower generic tag

      Represents the twopower function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct twopower_ : ext::elementwise_<twopower_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<twopower_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_twopower_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::twopower_, Site> dispatching_twopower_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::twopower_, Site>();
    }
    template<class... Args>
    struct impl_twopower_;
  }

  /*!
    Returns \f$2^n\f$ (0 if n is less than zero)

    @par semantic:
    For any given value n  of integral type @c I:

    @code
    T r = twopower(n);
    @endcode

    code is similar to:

    @code
    T r = 1 << n;
    @endcode

    @par Note:

    This function is not defined for floating entries

    @see  @funcref{ilog2}
    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::twopower_, twopower, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::twopower_, iexp2, 1)
} }
#endif
