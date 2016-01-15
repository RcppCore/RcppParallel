//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SPLAT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief splat generic tag

     Represents the splat function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct splat_ : ext::elementwise_<splat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<splat_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_splat_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::splat_, Site> dispatching_splat_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::splat_, Site>();
   }
   template<class... Args>
   struct impl_splat_;
  }

  template<class T, class A0> BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::splat_(A0, boost::dispatch::meta::as_<T>)>::type
  splat(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::splat_, A0>::type callee;
    return callee(a0, boost::dispatch::meta::as_<T>() );
  }
} }

#endif
