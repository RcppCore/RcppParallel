//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the find functor
    **/
    struct find_ : ext::tieable_<find_>
    {
      typedef ext::tieable_<find_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_find_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::find_, Site> dispatching_find_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::find_, Site>();
    }
    template<class... Args>
    struct impl_find_;
  }

  /*!
    @brief

    @param a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 1)

  /*!
    @brief

    @param a0
    @param a1
    @param a2
    @param a3
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 4)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 3)
}

#endif
