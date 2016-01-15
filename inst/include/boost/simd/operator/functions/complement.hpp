//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief complement generic tag

     Represents the complement function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct complement_ : ext::elementwise_<complement_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<complement_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_complement_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::complement_, Site> dispatching_complement_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::complement_, Site>();
   }
   template<class... Args>
   struct impl_complement_;
  }
  /*!
    return the bitwise complement of the entry
    Infix notation can be used with operator '~'

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = complement(a0);
    @endcode

    is similar to:

    @code
    T0 r = ~a0;
    @endcode

    @par Alias:
    @c b_not, @c bitwise_not

    @see  @funcref{bitwise_and}, @funcref{bitwise_or}, @funcref{bitwise_xor}, @funcref{bitwise_notand},
    @funcref{bitwise_andnot}, @funcref{bitwise_notor}, @funcref{bitwise_ornot}
    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , complement  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , bitwise_not , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , b_not       , 1 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
