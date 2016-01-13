//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_OPTIMIZE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_OPTIMIZE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag { struct optimize_; } namespace ext { template<class Site, class... Ts> BOOST_FORCEINLINE generic_dispatcher<tag::optimize_, Site> dispatching_optimize_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...) {   return generic_dispatcher<tag::optimize_, Site>(); } template<class... Args> struct impl_optimize_; } namespace tag { struct optimize_ : ext::abstract_<optimize_> { typedef ext::abstract_<optimize_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_optimize_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) }; }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::optimize_, optimize, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::optimize_, optimize, (A0&), 1)
} }

#endif
