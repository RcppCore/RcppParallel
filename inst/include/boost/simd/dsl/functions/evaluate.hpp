//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_EVALUATE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_EVALUATE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag { struct evaluate_; } namespace ext { template<class Site, class... Ts> BOOST_FORCEINLINE generic_dispatcher<tag::evaluate_, Site> dispatching_evaluate_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...) {   return generic_dispatcher<tag::evaluate_, Site>(); } template<class... Args> struct impl_evaluate_; } namespace tag { struct evaluate_ : ext::abstract_<evaluate_> { typedef ext::abstract_<evaluate_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_evaluate_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) }; }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::evaluate_, evaluate, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::evaluate_, evaluate, (A0&), 1)
} }

#endif
