//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_NEXT_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_NEXT_POWER_OF_2_HPP_INCLUDED

#include <boost/config.hpp>
#include <type_traits>

namespace boost { namespace simd
{
  /*!
    @brief Evaluates next power of 2

    Computes the power of two greater or equal to any given integral value @c n.

    @par Semantic:
    For any given integral value @c n:

    @code
    auto r = next_power_of_2(n);
    @endcode

    where @c r verifies:

    @code
    is_power_of_2(r) == true && r >= n
    @endcode

    @param n Integral value.

    @return Integral value of same type as n.
  **/

  namespace detail
  {

    template < typename Int , int s >
    struct next_power_of_2_impl
    {
      static BOOST_CXX14_CONSTEXPR BOOST_FORCEINLINE
      Int apply( Int n )
      {
        n = next_power_of_2_impl<Int,s/2>::apply(n);
        return n | (n >> s/2);
      }
    };

    template < typename Int >
    struct next_power_of_2_impl<Int,1>
    {
      static BOOST_CXX14_CONSTEXPR BOOST_FORCEINLINE
      Int apply( Int n )
      {
        return n;
      }
    };

  }


  template < typename Int >
  BOOST_CXX14_CONSTEXPR inline Int next_power_of_2( Int n )
  {
    static_assert( std::is_integral<Int>::value , "Int must be an integral type." );
    using impl = detail::next_power_of_2_impl< Int, sizeof(Int)*8 >;
    return  impl::apply(--n) + Int{1};
  }
} }

#endif
