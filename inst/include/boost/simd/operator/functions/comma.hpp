//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief comma generic tag

     Represents the comma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct comma_ : ext::elementwise_<comma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<comma_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_comma_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::comma_, Site> dispatching_comma_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::comma_, Site>();
   }
   template<class... Args>
   struct impl_comma_;
  }
  /*!
    TODO Put description here

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = comma(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = (a0, a1);
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , comma  , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , then   , 2 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
