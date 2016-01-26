//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_LOGNINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_LOGNINV_HPP_INCLUDED

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
     @brief logninv generic tag

     Represents the logninv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logninv_ : ext::tieable_<logninv_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<logninv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logninv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
    struct logninv0_ : ext::tieable_<logninv0_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<logninv0_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logninv0_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::logninv_, Site> dispatching_logninv_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::logninv_, Site>();
   }
   template<class... Args>
   struct impl_logninv_;
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::logninv0_, Site> dispatching_logninv0_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::logninv0_, Site>();
   }
   template<class... Args>
   struct impl_logninv0_;
  }
  /*!
    normal inverse cumulative distribution

    @par Semantic:

    For every table expression and optional mean and standard
    deviation of the associated normal distribution.


    @code
    auto r = logninv(a0, m, s);
    @endcode

    is similar to:

    @code
    auto r = exp(-Sqrt_2*erfcinv(2*a0)*s+m);
    @endcode

    @param a0
    @param m
    @param s

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::logninv0_, logninv, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::logninv0_, logninv, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::logninv0_, logninv, 1)
  /*!
    lognormal inverse cumulative distribution

    @par Semantic:

    @code
    tie(r, rlo, rup)= logninv(a0, m, s, cov, alpha);
    @endcode

    Returns r = loginv(a0, m, s), but also produces confidence bounds
    for r when the input parameters m and s are estimates.  cov is a
    2-by-2 matrix containing the covariance matrix of the estimated
    parameters.  alpha has a default value of 0.05, and specifies
    100*(1-alpha)% confidence bounds.  rlo and rup are arrays of the
    same size as a0 containing the lower and upper confidence bounds.

    @param a0
    @param m estimated  mean of the associated normal distribution
    @param s estimated standard deviation of the associated normal distribution
    @param cov covariance of the estimates
    @param alpha optional confidence bound (default to 0.05)


    @return r, rlo and rhi as described above
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::logninv_,  logninv, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::logninv_,  logninv, 4)
}
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::logninv_,Domain,N,Expr> // N =  4 or 5
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext2_t;
    typedef typename utility::result_of::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)),
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::logninv_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
