//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_CUMMIN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_CUMMIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/constant/constants/inf.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief cummin generic tag

      Represents the cummin function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct cummin_ : ext::cumulative_<cummin_, tag::min_, tag::Inf>
    {
      /// @brief Parent hierarchy
      typedef ext::cumulative_<cummin_, tag::min_, tag::Inf> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cummin_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::cummin_, Site> dispatching_cummin_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::cummin_, Site>();
    }
    template<class... Args>
    struct impl_cummin_;
  }
  /*!
    @brief compute the cumulate minimum of the vector elements

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = cummin(a0);
    @endcode

    is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i] += min(r[i-1], r[i]);
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cummin_, cummin, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cummin_, cummin, 2)
} }

#endif
