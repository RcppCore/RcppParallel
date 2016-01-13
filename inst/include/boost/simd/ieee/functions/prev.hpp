//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_PREV_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_PREV_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief prev generic tag

     Represents the prev function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct prev_ : ext::elementwise_<prev_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<prev_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_prev_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::prev_, Site> dispatching_prev_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::prev_, Site>();
   }
   template<class... Args>
   struct impl_prev_;
  }
  /*!
    in the type A0 of a0, the greatest A0 strictly less than a0

    @par Semantic:

    @code
    T r = prev(a0);
    @endcode

    computes the greatest value strictly less than a0 in type T

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::prev_, prev, 1)
} }

#endif
