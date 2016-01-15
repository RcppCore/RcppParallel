//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_NEXTPOW2_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief nextpow2 generic tag

     Represents the nextpow2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct nextpow2_ : ext::elementwise_<nextpow2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<nextpow2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_nextpow2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::nextpow2_, Site> dispatching_nextpow2_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::nextpow2_, Site>();
   }
   template<class... Args>
   struct impl_nextpow2_;
  }
  /*!
    Returns the least n such that abs(x) is less or equal to \f$2^n\f$

    @par Semantic:

    @code
    T r = nextpow2(a0);
    @endcode

    is similar to:

    @code
    T n = ceil(log2(abs(x)x));
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::nextpow2_, nextpow2, 1)
} }

#endif
