//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_LAYOUT_HPP_INCLUDED
#define NT2_SDK_META_LAYOUT_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>

namespace nt2 { namespace meta
{
  template<typename Expr>
  struct  layout
  {
    typedef typename Expr::value_type                                vt;
    typedef typename meta::option<Expr,tag::storage_order_   >::type so;
    typedef typename meta::option<Expr,tag::storage_scheme_  >::type ss;
    typedef typename meta::option<Expr,tag::storage_duration_>::type sd;
    typedef typename sd::storage_duration_type                      sdt;

    typedef boost::mpl::vector4<vt,so,ss,sdt> type;
  };

  template<typename X0, typename X1>
  struct  is_layout_compatible
        : boost::is_same<typename layout<X0>::type, typename layout<X1>::type>
  {};
} }

#endif
