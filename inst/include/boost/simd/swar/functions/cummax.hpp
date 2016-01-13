//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_CUMMAX_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_CUMMAX_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/operator/functions/plus.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/constant/constants/minf.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief cummax generic tag

      Represents the cummax function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct cummax_ : ext::cumulative_<cummax_, tag::max_, tag::Minf>
    {
      /// @brief Parent hierarchy
      typedef ext::cumulative_<cummax_, tag::max_, tag::Minf> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cummax_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::cummax_, Site> dispatching_cummax_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::cummax_, Site>();
    }
    template<class... Args>
    struct impl_cummax_;
  }
  /*!
    @brief compute the cumulate maximum of the vector elements

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = cummax(a0);
    @endcode

    is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i] += max(r[i-1], r[i]);
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cummax_, cummax, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cummax_, cummax, 2)
} }

#endif
