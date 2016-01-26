//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_IS_BUFFER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_IS_BUFFER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

namespace nt2 { namespace details
{
  /// Check if a type support the allocator_type interface, thus qualifying
  /// as an Container for us
  template<class T, class Enable=void>
  struct  is_buffer
        : boost::mpl::false_
  {};

  template<class T>
  struct  is_buffer < T
                    , typename  boost::dispatch::meta::
                                enable_if_type<typename T::allocator_type>::type
                    >
        : boost::mpl::true_
  {};
} }

#endif
