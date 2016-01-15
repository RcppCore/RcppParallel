//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_ULP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_ULP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief ulp generic tag

     Represents the ulp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ulp_ : ext::elementwise_<ulp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ulp_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ulp_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::ulp_, Site> dispatching_ulp_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::ulp_, Site>();
   }
   template<class... Args>
   struct impl_ulp_;
  }
  /*!
    Returns the distance to the nearest (distinct) element of the same type.

    @par Semantic:

    @code
    T r = ulp(x);
    @endcode

    is similar to:

    @code
    T r = min(x-pred(x), next(x)-x)/Eps<T>();
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ulp_, ulp, 1)
} }

#endif
