//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_GROUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_GROUP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief group generic tag

     Represents the group function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct group_ : ext::elementwise_<group_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<group_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_group_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::group_, Site> dispatching_group_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::group_, Site>();
   }
   template<class... Args>
   struct impl_group_;
  }

  /*!
    take two SIMD vectors of same type and elements of size n
    and return a vector collecting the two in a vector in which
    the elements have size n/2

    Of course the applicability is conditioned by the existence of compatible
    SIMD vector types

    @par Semantic:

    For every parameters of type T0

    @code
    downgrade<T0> r = group(a0, a1);
    @endcode

    is similar to:

    @code
    downgrade<T0> r;
    for(int i=0;i < T0::static_size; ++i)
      r[i] = a0[i];
      r[i+T0::static_size] = a1[i];
    @endcode

    @par Alias:
    @c demote, @c narrow

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, group, 2)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, group, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, demote, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::group_, narrow, 1)
} }

#endif
