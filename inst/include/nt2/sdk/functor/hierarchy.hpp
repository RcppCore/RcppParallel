//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/dispatch/dsl/category.hpp>

#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/meta/result_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/type_traits/common_type.hpp>

#include <boost/core/ignore_unused.hpp>

namespace nt2
{
  using boost::dispatch::functor;
  using boost::dispatch::make_functor;

  namespace tag
  {
    // Sites
    using boost::dispatch::tag::formal_;
    using boost::dispatch::tag::cpu_;
  }

namespace ext
{
  // Function object
  template<class Sig, class Site, class Enable = void>
  struct implement;
} }

#endif
