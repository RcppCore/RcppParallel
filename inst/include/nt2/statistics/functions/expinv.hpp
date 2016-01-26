//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief expinv generic tag

     Represents the expinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct expinv_ : ext::tieable_<expinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<expinv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_expinv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
    struct expinv0_ : ext::elementwise_<expinv0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<expinv0_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_expinv0_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::expinv_, Site> dispatching_expinv_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::expinv_, Site>();
   }
   template<class... Args>
   struct impl_expinv_;
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::expinv0_, Site> dispatching_expinv0_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::expinv0_, Site>();
   }
   template<class... Args>
   struct impl_expinv0_;
  }
  /*!
    exponential inverse cumulative distribution

    @par Semantic:

    For every table expression

    @code
    auto r = expinv(a0, lambda);
    @endcode

    is similar to:

    @code
    auto r = -log1p(-a0)*lambda;
    @endcode

    @see @funcref{log1p}
    @param a0
    @param a1 optional mean default to 1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv0_, expinv, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv0_, expinv, 1)
  /*!
    exponential inverse cumulative distribution

    @par Semantic:

    For every table expression,  mean lambda

    @code
    tie(r, rlo, rup)= expinv(a0, lambda, cov, alpha);
    @endcode

    Returns r = expinv(a0, lambda), but also produces confidence
    bounds for r when the input parameter lambda is an estimate.  cov
    is the variance of the estimated lambda.  alpha has a default
    value of 0.05, and specifies 100*(1-alpha)% confidence bounds.
    rlo and rup are tables of the same size as a0 containing the lower
    and upper confidence bounds.  the bounds are based on a normal
    approximation for the distribution of the log of the estimate of
    lambda.

    @param a0
    @param a1 optional mean default to 1
    @param a2 variance of the estimated a1
    @param a3 optional confidence bound (default to 0.05)

    @return an expression which eventually will evaluate to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_,  expinv, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_,  expinv, 3)
}


namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr> // N =  3 or 4
  struct  size_of<tag::expinv_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;

    typedef typename utility::result_of::max_extent< ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                        nt2::extent(boost::proto::child_c<1>(e)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::expinv_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::expinv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
