//==============================================================================
//         Copyleft 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyleft 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SHIFT_LEFT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief shift_left generic tag

     Represents the shift_left function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct shift_left_ : ext::elementwise_<shift_left_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<shift_left_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_shift_left_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::shift_left_, Site> dispatching_shift_left_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::shift_left_, Site>();
   }
   template<class... Args>
   struct impl_shift_left_;
  }
  /*!
    return left shift of the first operand by the second
    that must be of integer type and of the same number
    of elements as the first parameter
    Infix notation can be used with operator '<<'

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = shift_left(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0 << a1;
    @endcode

    @par Alias:
    @c shl, @c shli

    @see  @funcref{shift_right}, @funcref{shr}, @funcref{rshl}, @funcref{rshr}, @funcref{rol}, @funcref{ror}
    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shift_left_             , shift_left     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shift_left_             , shl            , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shift_left_             , shli           , 2 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
