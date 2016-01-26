//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_ASSIGN_SWAP_HPP_INCLUDED
#define NT2_CORE_UTILITY_ASSIGN_SWAP_HPP_INCLUDED

#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/copy.hpp>
#include <nt2/core/settings/locality.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace container
{
  template<class A0, class A1>
  typename boost::enable_if<
    boost::mpl::and_< meta::is_container_terminal<A0>
                    , meta::is_container_terminal<A1>
                    , boost::is_same<typename A0::value_type, typename A1::value_type>
                    >
  >::type
  assign_swap(A0& a0, A1& a1)
  {
    nt2::swap(a0,a1);
  }

  template<class A0, class A1>
  typename boost::disable_if<
  boost::mpl::or_<
    boost::mpl::and_< meta::is_container_terminal<A0>
                    , meta::is_container_terminal<A1>
                    , boost::is_same<typename A0::value_type, typename A1::value_type>
                    >
                  , meta::is_on_device<A0> , meta::is_on_device<A1>
                  >
  >::type
  assign_swap(A0& a0, A1& a1)
  {
    a0 = a1;
  }
} }

#endif
