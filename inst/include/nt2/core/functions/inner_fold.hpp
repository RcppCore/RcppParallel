//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_INNER_FOLD_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the inner_fold functor
    **/
    struct inner_fold_ : ext::abstract_<inner_fold_>
    {
      typedef ext::abstract_<inner_fold_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_inner_fold_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::inner_fold_, Site> dispatching_inner_fold_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::inner_fold_, Site>();
    }
    template<class... Args>
    struct impl_inner_fold_;
  }

  /*!
    @brief Fold over inner dimension

    Folds elements of @c a1 along inner dimension, possibly in parallel, and
    store the result in @c a0.

    @param a0 Expression to store result in
    @param a1 Expression to reduce
    @param a2 Functor to initialize the accumulator with
    @param a3 Function to apply for binary reduction, first argument is accumulator
    @param a4 Function to apply for unary reduction (for SIMD usage)
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::inner_fold_, inner_fold, (A0 const&)(A1 const&)(A2 const&)(A3 const&)(A4 const&), 5)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::inner_fold_, inner_fold, (A0&)(A1 const&)(A2 const&)(A3 const&)(A4 const&), 5)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::inner_fold_, inner_fold, (A0 const&)(A1&)(A2 const&)(A3 const&)(A4 const&), 5)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::inner_fold_, inner_fold, (A0&)(A1&)(A2 const&)(A3 const&)(A4 const&), 5)
}

#endif
