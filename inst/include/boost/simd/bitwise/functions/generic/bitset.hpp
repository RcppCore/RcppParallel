//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITSET_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITSET_HPP_INCLUDED

#include <boost/simd/bitwise/functions/bitset.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/dec.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT_IF( bitset_, tag::cpu_
                             , (A0)(A1)
                             , (boost::mpl::equal_to
                                < boost::simd::meta::cardinal_of<A0>
                               , boost::simd::meta::cardinal_of<A1>
                                >
                               )
                             , (generic_< arithmetic_<A0> >)
                               (generic_< integer_<A1> >)
                             )
  {
    typedef typename boost::dispatch::meta::as_integer<A0, unsigned>::type i_type;
    typedef typename boost::dispatch::meta::scalar_of<A0>::type               sA0;
    typedef A0                                                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(dec(a1)), "bitset :index is out of range");
      return bitwise_or(a0, shl(One<i_type>(), dec(a1)));
    }
  };

  BOOST_DISPATCH_IMPLEMENT( bitset_, tag::cpu_
                          , (A0)(A1)
                          , (generic_< arithmetic_<A0> >)
                            (scalar_< integer_<A1> >)
                          )
  {
    typedef typename boost::dispatch::meta::as_integer<A0, unsigned>::type i_type;
    typedef typename boost::dispatch::meta::scalar_of<A0>::type               sA0;
    typedef A0                                                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(dec(a1)), "bitset :index is out of range");
      return bitwise_or(a0, shl(One<i_type>(), dec(a1)));
    }

  };
} } }

#endif
