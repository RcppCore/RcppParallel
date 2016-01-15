//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_SCHEDULE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_SCHEDULE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct schedule_;
    struct schedule_assign_;
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::schedule_, Site> dispatching_schedule_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::schedule_, Site>();
    }
    template<class... Args>
    struct impl_schedule_;

    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::schedule_assign_, Site> dispatching_schedule_assign_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::schedule_assign_, Site>();
    }
    template<class... Args>
    struct impl_schedule_assign_;
  }
  namespace tag
  {
    struct schedule_ : ext::abstract_<schedule_>
    {
      typedef ext::abstract_<schedule_> parent;

      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_schedule_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    struct schedule_assign_ : ext::abstract_<schedule_assign_>
    {
      typedef ext::abstract_<schedule_assign_> parent;

      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_schedule_assign_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  // Tree + function + top mark
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_, schedule, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_, schedule, (A0 const&)(A1 const&), 2)

  // Special case assign node
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0 const&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0 const&)(A1 const&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0&)(A1 const&)(A2 const&), 3)
} }

#endif
