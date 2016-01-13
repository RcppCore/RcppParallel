//==============================================================================
//         Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_CUM_HELPER_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_CUM_HELPER_HPP_INCLUDED

#include <boost/simd/include/functions/simd/shuffle.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/mpl/int.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  template<std::size_t N,  std::size_t PASS = 1>
  struct cum_helper
  {
    template<typename I, typename C>
    struct apply : boost::mpl::int_<((I::value == 0) ? 0 : I::value-1) >{};

  };
  template<std::size_t N>
  struct cum_helper<N, 2>
  {
    template<typename I, typename C>
    struct apply : boost::mpl::int_<I::value == 0 ? 0:(I::value < 7 ? ((I::value-1)/3 ? 4:1):(I::value-2))>{};

  };
  template<std::size_t N>
  struct cum_helper<N, 4>
  {
    template<typename I, typename C>
    struct apply : boost::mpl::int_<I::value < 4 ? I::value : (I::value < 7 ? 3 :(I::value-4))>{};

  };
  template<std::size_t N>
  struct cum_helper<N, 8>
  {
    template<typename I, typename C>
    struct apply : boost::mpl::int_<I::value < 7 ? I::value : 7>{};

  };
} } }

#endif
