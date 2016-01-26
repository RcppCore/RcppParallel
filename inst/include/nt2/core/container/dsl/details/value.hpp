//==============================================================================
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_VALUE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_VALUE_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace details
{
  template<typename T>
  BOOST_FORCEINLINE typename boost::disable_if< boost::proto::is_expr<T>
                                              , T const&
                                              >::type
  value(T const& t)
  {
    return t;
  }

  template<typename T>
  BOOST_FORCEINLINE
  typename boost::lazy_enable_if< boost::proto::is_expr<T>
                                , boost::proto::result_of::value<T const&>
                                >::type
  value(T const& t)
  {
    return boost::proto::value(t);
  }
} }

#endif
