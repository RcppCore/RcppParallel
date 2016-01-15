//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_MINIMUM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief minimum generic tag

     Represents the minimum function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct min_;
    struct Valmax;

    struct minimum_ : ext::reduction_<minimum_, tag::min_, tag::Valmax>
    {
      /// @brief Parent hierarchy
      typedef ext::reduction_<minimum_, tag::min_, tag::Valmax> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_minimum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::minimum_, Site> dispatching_minimum_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::minimum_, Site>();
   }
   template<class... Args>
   struct impl_minimum_;
  }
  /*!
    Returns the least element of the SIMD vector

    @par Semantic:

    For every parameter of type T0

    @code
    scalar_of<T0> r = minimum(a0);
    @endcode

    is similar to:

    @code
      scalar_of<T0> r = Inf;
      for(std::size_t i=0;i<cardinal_of<T0>;++i)
        r =  r > a0[i] ? a0[i] : r;
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minimum_, minimum, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minimum_, minimum, 2)
} }
#endif

