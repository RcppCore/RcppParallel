//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief unary_plus generic tag

     Represents the unary_plus function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unary_plus_ : ext::elementwise_<unary_plus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unary_plus_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_unary_plus_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::unary_plus_, Site> dispatching_unary_plus_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::unary_plus_, Site>();
   }
   template<class... Args>
   struct impl_unary_plus_;
  }
  /*!
    return the elementwise unary plus of the parameter
    Infix notation can be used with operator '+'
    This is in fact identity.

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = unary_plus(a0);
    @endcode

    is similar to:

    @code
    T0 r = +a0;
    @endcode

    @par Alias:
    @c identity,  @c id

    @see  @funcref{plus}, @funcref{unary_minus}
    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , unary_plus  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , identity    , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , id          , 1 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
