//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief safe_min generic tag

     Represents the safe_min function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct safe_min_ : ext::elementwise_<safe_min_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<safe_min_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_safe_min_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::safe_min_, Site> dispatching_safe_min_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::safe_min_, Site>();
   }
   template<class... Args>
   struct impl_safe_min_;
  }
  /*!
    Returns a safe mininimal value relative to the input, i.e. a
    value which will not underflow when divided by the input.

    @par Semantic:

    @code
    T r = safe_min(x);
    @endcode

    is similar to:

    @code
    T r =  x ? Sqrtsmallestposval<T>()*abs(x);
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::safe_min_, safe_min, 1)
} }

#endif
