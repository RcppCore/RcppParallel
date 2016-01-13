//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_REM_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_REM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  rem generic tag

      Represents the rem function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct rem_ : ext::elementwise_<rem_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rem_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rem_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::rem_, Site> dispatching_rem_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::rem_, Site>();
   }
   template<class... Args>
   struct impl_rem_;
  }
  /*!
    Computes the remainder of division.
    The return value is a0-n*a1, where n is the value a0/a1,
    rounded toward zero.

    @par semantic:
    For any given value @c x, @c y of type @c T:

    @code
    T r = rem(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    T r = x-divfix(x, y)*y;
    @endcode

    @par Alias

    @c fmod,  @c remfix

    @see @funcref{remainder}, @funcref{mod}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rem_, rem, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rem_, fmod, 2)
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rem_, remfix, 2)
} }

#endif


