//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief logical_not generic tag

     Represents the logical_not function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_not_ : ext::elementwise_<logical_not_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_not_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logical_not_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::logical_not_, Site> dispatching_logical_not_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::logical_not_, Site>();
   }
   template<class... Args>
   struct impl_logical_not_;
  }
  /*!
    return the logical negation of the parameter,
    i.e. True or False of the entry type according that
    the input is zero or non zero

    @par Semantic:

    For every parameter of type T0

    @code
    as_logical<T0> r = logical_not(a0);
    @endcode

    is similar to:

    @code
    T0 r =!a0;
    @endcode

    @par Alias:
    @c l_not

    @see  @funcref{logical_or}, @funcref{logical_xor}, @funcref{logical_notand},
    @funcref{logical_andnot}, @funcref{logical_notor}, @funcref{logical_ornot}
    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , logical_not  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , l_not        , 1 )
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
