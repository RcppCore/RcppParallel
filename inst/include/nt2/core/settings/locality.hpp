//==============================================================================
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_LOCALITY_HPP_INCLUDED
#define NT2_CORE_SETTINGS_LOCALITY_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/locality.hpp>
#include <boost/mpl/or.hpp>
#include <type_traits>

namespace nt2 { namespace tag
{
  struct locality_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::host_ default_type;
  };

  template<>
  struct locality_::apply<nt2::host_>
                        : boost::mpl::true_
  {};

  template<>
  struct locality_::apply<nt2::device_>
                        : boost::mpl::true_
  {};
} }

namespace nt2 { namespace meta
{

  template<typename A,typename B>
  struct is_same_locality : std::is_same<typename option<A,tag::locality_>::type
                                        ,typename option<B,tag::locality_>::type
                                        >
  {};

  template<typename X>
  struct is_on_device : std::is_same< typename option<X,tag::locality_>::type
                                    , nt2::device_
                                    >
  {};

  template<typename X>
  struct is_on_host : std::is_same< typename option<X,tag::locality_>::type
                                  , nt2::host_
                                  >
  {};

  template<typename A0, typename A1>
  struct is_device_assign : boost::mpl::or_< is_on_device<A0>
                                           , is_on_device<A1>
                                           >
  {};

} }

#include <nt2/core/settings/details/locality.hpp>

#endif
