//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>

namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};

  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Sig, class Site = void>
  struct dispatch_call;

  template< class Tag, class Site_
          , class... A
          >
  struct dispatch_call<Tag(A...), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;

    typedef decltype
    ( Tag::dispatch ( hierarchy_of_t<Site>()
                    , hierarchy_of_t<A>()...
                    )
    ) type;
  };

} } }

#endif
