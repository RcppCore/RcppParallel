//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_DEC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_DEC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  dec generic tag

      Represents the dec function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct dec_ : ext::elementwise_<dec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<dec_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_dec_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::dec_, Site> dispatching_dec_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::dec_, Site>();
    }
    template<class... Args>
    struct impl_dec_;
  }
  /*!
    Decrements a value by 1.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = dec(x);
    @endcode

    is equivalent to:

    @code
    T r =  x-T(1);
    @endcode

    @see  @funcref{minusone}, @funcref{minus}
    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dec_, dec, 1)
} }

#endif
