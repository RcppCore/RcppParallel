//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_POWLOWLIM_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_POWLOWLIM_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/dispatch/function/make_callable.hpp>
#include <boost/dispatch/hierarchy/functions.hpp>
#include <boost/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct powlowlim_ : boost::dispatch::constant_value_<powlowlim_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,powlowlim_,boost::dispatch::constant_value_<powlowlim_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc5160000UL, 0xc0d0c7c000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,powlowlim_);
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::powlowlim_,powlowlim);
  }

  template<typename T> BOOST_FORCEINLINE auto Powlowlim() BOOST_NOEXCEPT
  -> decltype(functional::powlowlim( boost::dispatch::as_<T>{}))
  {
    return functional::powlowlim( boost::dispatch::as_<T>{} );
  }
} }

#endif
