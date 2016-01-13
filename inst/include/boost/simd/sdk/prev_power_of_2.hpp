//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_PREV_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_PREV_POWER_OF_2_HPP_INCLUDED

#include "next_power_of_2.hpp"

namespace boost { namespace simd
{
  /*!
    @brief Evaluates previous power of 2

    Computes the power of two lesser or equal to any given integral value @c n.

    @par Semantic:
    For any given integral value @c n:

    @code
    auto r = prev_power_of_2(n);
    @endcode

    where @c r verifies:

    @code
    is_power_of_2(r) == true && r <= n
    @endcode

    @param n Integral value.

    @return Integral value of same type as n.
  **/
  template < typename Int >
  inline BOOST_CONSTEXPR Int prev_power_of_2( Int n )
  {
    static_assert( std::is_integral<Int>::value , "Int must be an integral type." );
    using impl = detail::next_power_of_2_impl< Int, sizeof(Int)*8 >;
    return  (n == 0) ? Int{0} : (impl::apply(n) >> 1) + Int{1};
  }
} }

#endif
