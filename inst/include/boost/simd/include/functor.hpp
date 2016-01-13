//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_INCLUDE_FUNCTOR_HPP_INCLUDED
#define BOOST_SIMD_INCLUDE_FUNCTOR_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/functor/preprocessor/function.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch
{
  template<class Tag, class Site>
  struct generic_dispatcher
  {
    /* While ICC supports SFINAE with decltype, it seems to cause
     * infinite compilation times in some cases */
    #if defined(BOOST_NO_SFINAE_EXPR) || defined(__INTEL_COMPILER)
    /*! For compatibility with result_of protocol */
    template<class Sig>
    struct result;

    // result_of needs to SFINAE in this case
    template<class This, class... Args>
    struct result<This(Args...)>
         : boost::dispatch::meta::
           result_of< decltype(dispatching(meta::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args>()...))(Args...) >
    {
    };

    template<class... Args>
    BOOST_FORCEINLINE typename result<generic_dispatcher(Args&&...)>::type
    operator()(Args&&... args) const
    {
      return dispatching(meta::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()...)(static_cast<Args&&>(args)...);
    }
    #else
    template<class... Args>
    BOOST_FORCEINLINE auto
    operator()(Args&&... args) const
    BOOST_AUTO_DECLTYPE_BODY_SFINAE(
      dispatching(meta::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()...)(static_cast<Args&&>(args)...)
    )
    #endif
  };
} }

namespace boost { namespace simd { namespace ext
{
  struct adl_helper {};

  template<class Tag, class Site, class... Ts>
  BOOST_FORCEINLINE boost::dispatch::generic_dispatcher<Tag, Site>
  dispatching(adl_helper, unknown_<Tag>, unknown_<Site>, unknown_<Ts>...)
  {
    return boost::dispatch::generic_dispatcher<Tag, Site>();
  }
} } }

namespace boost { namespace simd
{
  template<class Tag, class Site>
  struct generic_dispatcher
  {
    /* While ICC supports SFINAE with decltype, it seems to cause
     * infinite compilation times in some cases */
    #if defined(BOOST_NO_SFINAE_EXPR) || defined(__INTEL_COMPILER)
    /*! For compatibility with result_of protocol */
    template<class Sig>
    struct result;

    // result_of needs to SFINAE in this case
    template<class This, class... Args>
    struct result<This(Args...)>
         : boost::dispatch::meta::
           result_of< decltype(dispatching(ext::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args>()...))(Args...) >
    {
    };

    template<class... Args>
    BOOST_FORCEINLINE typename result<generic_dispatcher(Args&&...)>::type
    operator()(Args&&... args) const
    {
      return dispatching(ext::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()...)(static_cast<Args&&>(args)...);
    }
    #else
    template<class... Args>
    BOOST_FORCEINLINE auto
    operator()(Args&&... args) const
    BOOST_AUTO_DECLTYPE_BODY_SFINAE(
      dispatching(ext::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()...)(static_cast<Args&&>(args)...)
    )
    #endif
  };
} }

#endif
