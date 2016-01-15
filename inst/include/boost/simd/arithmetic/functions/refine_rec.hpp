//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_REFINE_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_REFINE_REC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  refine_rec generic tag

      Represents the refine_rec function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct refine_rec_ : ext::elementwise_<refine_rec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<refine_rec_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_refine_rec_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::refine_rec_, Site> dispatching_refine_rec_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::refine_rec_, Site>();
    }
    template<class... Args>
    struct impl_refine_rec_;
  }

  /*!
    Performs a Newton-Raphson step to improve precision of reciprocate estimate.
    This function can be used in conjunction with funcref{raw_rec} or
    funcref{fast_rec} to add more precision to the estimate if their default
    precision is not enough.

    @param  a0 Value for which rec is to be computed
    @param  a1 Current estimate of rec(a0)

    @see funcref{rec}

    @return  A value estimating rec(a0) with twice as much precision

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::refine_rec_, refine_rec, 2)

} }

#endif
