//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_EPS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief eps generic tag

     Represents the eps function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct eps_ : ext::elementwise_<eps_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<eps_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_eps_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::eps_, Site> dispatching_eps_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::eps_, Site>();
   }
   template<class... Args>
   struct impl_eps_;
  }
  /*!
    Except for numbers whose absolute value is smaller than Smallestpositivevalue,
    @c eps(x) returns 2^(exponent(x))*Eps


    @par Semantic:

    @code
    T r = eps(a0);
    @endcode

    is similar to:

    @code

    if T is floating
      r = 2^(exponent(x))*Eps<T>
    else if T is integral
      r = 1;
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::eps_, eps, 1)
} }

#endif
