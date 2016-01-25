//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_ELEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_ELEVEN_HPP_INCLUDED

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
    struct eleven_ : boost::dispatch::constant_value_<eleven_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,eleven_,boost::dispatch::constant_value_<eleven_>);
      BOOST_SIMD_REGISTER_CONSTANT(11,0x41300000U,0x4026000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,eleven_);
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::eleven_,eleven);
  }

  template<typename T> BOOST_FORCEINLINE auto Eleven() BOOST_NOEXCEPT
  -> decltype(functional::eleven( boost::dispatch::as_<T>{}))
  {
    return functional::eleven( boost::dispatch::as_<T>{} );
  }
} }

#endif
