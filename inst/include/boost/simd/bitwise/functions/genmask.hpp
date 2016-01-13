//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENMASK_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  genmask generic tag

      Represents the genmask function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct genmask_ : ext::elementwise_<genmask_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<genmask_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_genmask_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::genmask_, Site> dispatching_genmask_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::genmask_, Site>();
    }
    template<class... Args>
    struct impl_genmask_;
  }
  /*!
    Returns a mask of bits. All ones if the
    input element is non zero else all zeros.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = genmask(x);
    @endcode

    is similar to

    @code
    T r = x ? Allbits : Zero;
    @endcode

    @par Alias:
    @c typed_mask, @c logical2mask, @c l2m, @c typed_mask, @c if_allbits_else_zero

    @see @funcref{if_allbits_else}
    @param  a0

    @return      a value of the type of the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, genmask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, typed_mask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, logical2mask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, l2m, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, if_allbits_else_zero, 1)
} }

#endif
