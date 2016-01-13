//==============================================================================
//          Copyright 2015 - J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TENPOWER_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TENPOWER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  tenpower generic tag

      Represents the tenpower function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tenpower_ : ext::elementwise_<tenpower_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tenpower_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_tenpower_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::tenpower_, Site> dispatching_tenpower_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::tenpower_, Site>();
    }
    template<class... Args>
    struct impl_tenpower_;
  }

  /*!
    @brief Returns \f$10^n\f$ in the floating type  corresponding to A0

    @par semantic:
    For any given value n  of integral type @c I, and T of type as_floating<I>::type

    @code
    T r = tenpower(n);
    @endcode

    code is similar to:

    @code
    T r = exp10(T(n));
    @endcode

    @par Note:

    This function is not defined for floating entries

    @param  n

    @return a value of the floating associated type.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tenpower_, tenpower, 1)
} }
#endif
