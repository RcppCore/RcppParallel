//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS
  @copyright 2015 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMQUO_HPP_INCLUDED

#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/round2even.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/dispatch/function/overload.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::generic_< bd::floating_<A0> >
                          , bd::generic_< bd::floating_<A0> >
                          , bd::generic_< bd::integer_<A1> >
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE
      result_type operator() ( A0 a0,A0 a1,A1& a3
                              , typename std::enable_if< std::is_same<
                                     typename bd::as_integer_t<A0,signed>
                                    , A1>::value>* = 0
                             ) const BOOST_NOEXCEPT
    {
      result_type a2;
      boost::simd::remquo(a0, a1, a2, a3);
      return a2;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0)
                          , bd::cpu_
                          , bd::generic_< bd::floating_<A0> >
                          , bd::generic_< bd::floating_<A0> >
                          )
  {
    using quo_t = bd::as_integer_t<A0, signed>;
    using result_type = std::pair<A0,quo_t>;

    BOOST_FORCEINLINE result_type operator() ( A0 a0,A0 a1) const BOOST_NOEXCEPT
    {
      A0 first;
      quo_t second;
      boost::simd::remquo( a0, a1, first, second );
      return result_type(first, second);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::generic_<bd::floating_<A0> >
                          , bd::generic_<bd::floating_<A0> >
                          , bd::generic_<bd::floating_<A0> >
                          , bd::generic_<bd::integer_ <A1> >
                          )
  {

    BOOST_FORCEINLINE void operator() ( A0 a0, A0 a1,A0& a2, A1& a3
                                      , typename std::enable_if< std::is_same<
                                        typename bd::as_integer_t<A0,signed>
                                      , A1>::value>* = 0
                                      ) const BOOST_NOEXCEPT
    {
      A0 const d = round2even(a0/a1);

#if defined(BOOST_SIMD_NO_INVALIDS)
      a2 = if_allbits_else(is_eqz(a1), a0-d*a1);
#else
      a2 = if_allbits_else(logical_or(is_invalid(a0), is_eqz(a1)), a0-d*a1);
#endif

      a3 = toint(d);
    }
  };
} } }


#endif
