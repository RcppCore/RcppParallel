//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_IS_TARGET_HPP_INCLUDED
#define NT2_SDK_META_IS_TARGET_HPP_INCLUDED
#include <nt2/sdk/meta/as.hpp>

namespace nt2 { namespace meta
{
  template < class T > struct is_target : boost::mpl::false_{};
  template < class T > struct is_target < meta::as_<T> > :  boost::mpl::true_{};
} }

#endif

