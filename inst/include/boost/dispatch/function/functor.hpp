//==================================================================================================
/*
  Copyright 2012 - 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_DISPATCH_FUNCTION_FUNCTOR_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTION_FUNCTOR_HPP_INCLUDED

#include <boost/dispatch/hierarchy/default_site.hpp>
#include <boost/dispatch/hierarchy_of.hpp>
#include <boost/config.hpp>
#include <utility>

#define BOOST_DISPATCH_IMPL_TAG_CALL(TAG,SITE,TS,AS)                                                \
TAG::dispatch_to(SITE(),boost::dispatch::hierarchy_of_t<TS>()...)( std::forward<TS>(AS)...)         \
/**/

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-function
    @brief Adaptable dispactch-enabled function object

    @tparam Tag
    @tparam Site
  **/
  template<typename Tag, typename Site = boost::dispatch::default_site<Tag>>
  struct functor
  {
    /*!

    **/
    template<typename Other, typename... Args> BOOST_FORCEINLINE
    auto on(Args&&... args) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args))
    {
      return BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args);
    }

    /*!
      @brief Architectural target rebinding

      Creates an instance of functor which shares current functor's tag but
      dispatched over a specific architecture hierarchy.

      @return a instance of functor dispatching specifically on architecture Other

      @tparam Other New architecture target to generate a functor for
    **/
    template<typename Other>
    static BOOST_FORCEINLINE functor<Tag,Other> rebind() BOOST_NOEXCEPT { return {}; }

    /*!

    **/
    template<typename... Args> BOOST_FORCEINLINE
    auto operator()(Args&&... args) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Site,Args,args)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Site,Args,args))
    {
      return BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Site,Args,args);
    }
  };
} }

#endif
