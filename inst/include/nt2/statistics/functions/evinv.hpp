//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EVINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EVINV_HPP_INCLUDED

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
     @brief evinv generic tag

     Represents the evinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct evinv_ : ext::tieable_<evinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<evinv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evinv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
    struct evinv0_ : ext::elementwise_<evinv0_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<evinv0_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evinv0_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::evinv_, Site> dispatching_evinv_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::evinv_, Site>();
   }
   template<class... Args>
   struct impl_evinv_;
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::evinv0_, Site> dispatching_evinv0_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::evinv0_, Site>();
   }
   template<class... Args>
   struct impl_evinv0_;
  }
  /*!
    extreme value inverse cumulative distribution of shape m and scale s

    @par Semantic:

    For every table expression

    @code
    auto r = evinv(a0, m, s);
    @endcode

    is similar to:

    @code
    auto r = log(-log(1-p))*s+m;
    @endcode

    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::evinv0_, evinv, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evinv0_, evinv, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evinv0_, evinv, 1)
  /*!
    extreme value inverse cumulative distribution of shape m and scale s

    @par Semantic:

    For every table expression

    @code
    tie(r, rlo, rup)= expinv(a0, m, s, cov, alpha);
    @endcode

    Returns r = expinv(a0, m, s), but also produces confidence bounds
    for r when the input parameters m and s are estimates.  cov is a
    2-by-2 matrix containing the covariance matrix of the estimated
    parameters.  alpha has a default value of 0.05, and specifies
    100*(1-alpha)% confidence bounds.  rlo and rup are arrays of the
    same size as a0 containing the lower and upper confidence bounds.

    @param a0
    @param a1 estimated shape
    @param a2 estimated scale
    @param a3 covariance of the estimates
    @param a4 optional confidence bound (default to 0.05)


    @return an expression which eventually will evaluate to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::evinv_,  evinv, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evinv_,  evinv, 4)
}
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::evinv_,Domain,N,Expr> // N =  4 or 5
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
  struct  size_of<tag::evinv_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::evinv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

} }

#endif
