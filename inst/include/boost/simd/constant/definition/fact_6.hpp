//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FACT_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FACT_6_HPP_INCLUDED

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
    struct fact_6_ : boost::dispatch::constant_value_<fact_6_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fact_6_,boost::dispatch::constant_value_<fact_6_>);
      BOOST_SIMD_REGISTER_CONSTANT(720,0x44340000U,0x4086800000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,fact_6_);
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fact_6_,fact_6);
  }

  template<typename T> BOOST_FORCEINLINE auto Fact_6() BOOST_NOEXCEPT
  -> decltype(functional::fact_6( boost::dispatch::as_<T>{}))
  {
    return functional::fact_6( boost::dispatch::as_<T>{} );
  }
} }

#endif
