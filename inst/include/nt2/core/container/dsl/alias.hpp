//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_ALIAS_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_ALIAS_HPP_INCLUDED

#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/container/dsl/details/value.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/data.hpp>

namespace nt2 { namespace container
{
  template<class T, class U> inline bool alias(T const& t, U const& u)
  {
    return nt2::memory::data(details::value(t)) < nt2::memory::data(details::value(u))+numel(u)
        && nt2::memory::data(details::value(t)) + nt2::numel(t) >= nt2::memory::data(details::value(u));
  }
} }

#endif
