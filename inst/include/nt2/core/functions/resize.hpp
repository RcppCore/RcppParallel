//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RESIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RESIZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::resize function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct resize_ : ext::elementwise_<resize_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<resize_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_resize_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::resize_, Site> dispatching_resize_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::resize_, Site>();
    }
    template<class... Args>
    struct impl_resize_;
  }

  //============================================================================
  /*!
   * resize an expression
   *
   * \param xpr   Expression to resize
   * \param size  New size of the expression
   */
  //============================================================================
  #define M0(z,n,t)                                         \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::resize_, resize, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<nt2::tag::resize_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr,int N>
  struct  size_of<nt2::tag::resize_,Domain,N,Expr>
        : meta::boxed_size<Expr,1>
  {};
} }

#endif
