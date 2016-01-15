//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  oneminus generic tag

      Represents the oneminus function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct oneminus_ : ext::elementwise_<oneminus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<oneminus_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_oneminus_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::oneminus_, Site> dispatching_oneminus_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::oneminus_, Site>();
   }
   template<class... Args>
   struct impl_oneminus_;
  }
  /*!
    Returns the one minus the entry, saturated in the entry type.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = oneminus(x);
    @endcode

    For signed type is similar to:

    @code
    T r = 1-x
    @endcode

    For unsigned type it is equivalent (due to saturation) to:

    @code
    T r = x == 0 ? 1 : 0
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::oneminus_, oneminus, 1)
} }

#endif


