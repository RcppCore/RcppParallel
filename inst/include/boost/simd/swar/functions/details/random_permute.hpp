//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_RANDOM_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_RANDOM_PERMUTE_HPP_INCLUDED

#include <boost/dispatch/meta/as.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace details
{
  template<int... IndexMap>
  struct random_permute
  {
    template<int N, int... I> struct nth_t;

    template<int I0, int... In>
    struct nth_t<0, I0, In...> : std::integral_constant<int,I0>
    {};

    template<int N, int I0, int... In>
    struct nth_t<N, I0, In...> : nth_t<N-1, In...>::type
    {};

    template<typename Index, typename Cardinal>
    struct apply : nth_t<Index::value,IndexMap...>
    {};
  };

  template<int... IndexMap>
  using random_permute_t = boost::dispatch::meta
                                ::as_<details::random_permute<IndexMap...>>;
} } }

#endif
