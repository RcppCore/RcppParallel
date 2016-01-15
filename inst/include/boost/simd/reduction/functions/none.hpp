//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief none generic tag

     Represents the none function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct none_ : ext::abstract_<none_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<none_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_none_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::none_, Site> dispatching_none_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::none_, Site>();
   }
   template<class... Args>
   struct impl_none_;
  }
  /*!
    Returns True if all elements of the input vector are zero.

    @par Semantic:

    For every parameter of type T0

    @code
    as_logical<scalar_of<T0>> r = none(a0);
    @endcode

    is similar to:

    @code
    as_logical<scalar_of<T0>> r = !any(a0);
    @endcode

    @param a0

    @return a value of the scalar logical type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 2)
} }
#endif
