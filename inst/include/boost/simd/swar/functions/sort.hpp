//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SORT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SORT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/tieable.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief sort generic tag

     Represents the sort function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sort_ : ext::tieable_<sort_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<sort_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sort_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::sort_, Site> dispatching_sort_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::sort_, Site>();
   }
   template<class... Args>
   struct impl_sort_;
  }
  /*!
    returns the sorted a0 vector in ascending order

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = sort(a0);
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 3)

} }

#endif
