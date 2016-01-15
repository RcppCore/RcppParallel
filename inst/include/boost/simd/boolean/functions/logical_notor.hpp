//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_LOGICAL_NOTOR_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_LOGICAL_NOTOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief logical_notor generic tag

     Represents the logical_notor function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_notor_ : ext::elementwise_<logical_notor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_notor_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logical_notor_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::logical_notor_, Site> dispatching_logical_notor_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::logical_notor_, Site>();
   }
   template<class... Args>
   struct impl_logical_notor_;
  }
  /*!
    return the logical or of the negation of the first parameter and the second parameter
    the result type is logical type associated to the first parameter

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = logical_notor(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = !a0 || a1;
    @endcode

    @par Alias:
    @c l_notor

    @param a0

    @param a1

    @return a value of the logical type asssociated to the first parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_notor_      , logical_notor     , 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_notor_      , l_notor           , 2)
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
