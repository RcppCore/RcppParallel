//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPAND_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief expand generic tag

      Represents the expand function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct expand_ : ext::elementwise_<expand_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<expand_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_expand_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::expand_, Site> dispatching_expand_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::expand_, Site>();
    }
    template<class... Args>
    struct impl_expand_;
  }

  /*!
    Expands expression to a given size cropping or adding zeros if needed,
    but preserving the position of elements inside the old remaining parts.

    @par semantic:

    expand(a,siz) is the upper left corner of a of size siz, assuming that
    @c a is is infinetely extended with zeros in every dimensions.

    @param a0 expression to process
    @param a1 size to expand to
    @return an expression which eventually will evaluate to the result
  **/

  #define M0(z,n,t)                                         \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::expand_, expand, n) \
  /**/
  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)
  #undef M0
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::expand_,Domain,N,Expr>
        : meta::boxed_size<Expr,1>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<nt2::tag::expand_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
