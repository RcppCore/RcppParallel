//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_IS_INCLUDED_C_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_included_c generic tag

     Represents the is_included_c function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_included_c_ : ext::unspecified_<is_included_c_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<is_included_c_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_is_included_c_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::is_included_c_, Site> dispatching_is_included_c_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::is_included_c_, Site>();
   }
   template<class... Args>
   struct impl_is_included_c_;
  }
  /*!
    Returns True is only if all bits set in a0 are not set in a1

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    logical<scalar_of<T0>> r = is_included_c(a0,a1);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = all(a0&a1 == zero);
    @endcode

    @par Alias:
    @c testz, @c are_disjoint

    @param a0

    @param a1

    @return a value of the scalar logical type associated to the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, is_included_c, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, testz, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, are_disjoint, 2)
} }
#endif
