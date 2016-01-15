//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_RUN_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_RUN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct run_;
    struct run_assign_;
  }
  namespace ext
  {
  template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::run_, Site> dispatching_run_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::run_, Site>();
    }
    template<class... Args>
    struct impl_run_;

    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::run_assign_, Site> dispatching_run_assign_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::run_assign_, Site>();
    }
    template<class... Args>
    struct impl_run_assign_;
  }
  namespace tag
  {
    struct run_ : ext::abstract_<run_>
    {
      typedef ext::abstract_<run_> parent;

      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_run_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    struct run_assign_ : ext::abstract_<run_assign_>
    {
      typedef ext::abstract_<run_assign_> parent;

      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_run_assign_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0 const&), 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0&), 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0 const&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0 const&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0 const&)(A1 const&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_, run, (A0&)(A1 const&)(A2 const&), 3)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1 const&)(A2&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1 const&)(A2&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1&)(A2&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1&)(A2&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1 const&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1 const&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1 const&)(A2&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1 const&)(A2&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1&)(A2&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1&)(A2&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1 const&)(A2 const&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1 const&)(A2 const&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0 const&)(A1&)(A2 const&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::run_assign_, run_assign, (A0&)(A1&)(A2 const&)(A3 const&), 4)
} }

#endif
