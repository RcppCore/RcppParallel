//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SBITS_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief sbits generic tag

     Represents the sbits function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sbits_ : ext::elementwise_<sbits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sbits_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sbits_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::sbits_, Site> dispatching_sbits_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::sbits_, Site>();
   }
   template<class... Args>
   struct impl_sbits_;
  }
  /*!
    Returns signed integer value which has the same bits of the input

    @par Semantic:

    @code
    T r = sbits(x);
    @endcode

    is similar to:

    @code
    T r = bitwise_cast<as_integer<T,signed>>(x);
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sbits_, sbits, 1)
} }

#endif
