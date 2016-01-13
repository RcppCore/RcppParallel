//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief unary_minus generic tag

     Represents the unary_minus function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unary_minus_ : ext::elementwise_<unary_minus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unary_minus_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_unary_minus_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::unary_minus_, Site> dispatching_unary_minus_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::unary_minus_, Site>();
   }
   template<class... Args>
   struct impl_unary_minus_;
  }
  /*!
    return the elementwise unary minus of the parameter
    Infix notation can be used with operator '-'

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = unary_minus(a0);
    @endcode

    is similar to:

    @code
    T0 r = -a0;
    @endcode

    @par Alias:
    @c neg

    @see  @funcref{minus}, @funcref{unary_plus}
    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, unary_minus , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, neg         , 1 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
