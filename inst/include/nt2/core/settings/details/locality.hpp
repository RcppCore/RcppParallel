//==============================================================================
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_LOCALITY_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_LOCALITY_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

namespace nt2
{
  /// INTERNAL ONLY
  struct host_
  {
    template<typename Container> struct traits
    {
      using k_t  = typename Container::kind_type;
      using s_t  = typename Container::settings_type;
      using ss_t = typename Container::scheme_t;
      using buffer_type = typename ss_t::template apply<Container>::type;
    };
  };

  /// INTERNAL ONLY
  struct device_
  {
    template<typename X>
    using arch_t = typename boost::dispatch::default_site<X>::type;

    template<typename Container, typename Enable=void>
    struct traits_impl : host_::template traits<Container>
    {};

    template<typename Container>
    struct  traits_impl < Container
                        , typename  boost::dispatch::meta::
                                    enable_if_type<typename arch_t<Container>::device_tag>::type
                        >
                : arch_t<Container>::template device_traits<Container>
    {};

    template<typename Container>
    using traits = traits_impl<Container>;
  };
}

#endif
