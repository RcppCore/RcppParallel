//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_INV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_INV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Tag for inv function
    struct inv_ : ext::unspecified_<inv_>
    {
      typedef ext::unspecified_<inv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_inv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::inv_, Site> dispatching_inv_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::inv_, Site>();
    }
    template<class... Args>
    struct impl_inv_;
  }

  /*!
    @brief inv  inverse of square matrix.
    inv(x) is the inverse of the square matrix expression x.

    Avoid to use this function if you do not have a very good reason
    and whatsoever never use it to solve linear systems.
    99% of the time a solver is a better choice.

    @param a0   Matrix to invert
    @return     The inverse of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inv_, inv, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<typename Domain, typename Expr,  int N>
  struct size_of<tag::inv_, Domain, N, Expr> : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template <typename Domain, typename Expr,  int N>
  struct value_type<tag::inv_, Domain, N, Expr> : meta::value_as<Expr,0>
  {};
} }

#endif

