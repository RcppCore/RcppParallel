//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_POSITIVE_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_POSITIVE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_positive generic tag

     Represents the is_positive function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_positive_ : ext::elementwise_<is_positive_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_positive_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_is_positive_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };}
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::is_positive_, Site> dispatching_is_positive_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::is_positive_, Site>();
   }
   template<class... Args>
   struct impl_is_positive_;
  }
  /*!
    Returns True if a0 is positive else False.

    This function differs from is_gtz from floating point argument,
    because Zero is positive but not greater than zero, and Mzero is
    not positive and not greater than zero, It's probably is_gtz that
    you want.


    @par Semantic:

    @code
    logical<T> r = is_positive(a0);
    @endcode

    is similar to:

    @code
    if T is signed
      logical<T> r = bitofsign(a0) == 0;
    else
      logical<T> r = True;
    @endcode


    @par Note:

    Mzero is the floating point 'minus zero',
    i.e. all bits are zero but the sign bit.
    Such a value is treated as zero by ieee standards.

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_positive_, is_positive, 1)
} }

#endif

