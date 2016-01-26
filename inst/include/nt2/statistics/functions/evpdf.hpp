//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EVPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EVPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief evpdf generic tag

     Represents the evpdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct evpdf_ : ext::elementwise_<evpdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<evpdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evpdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::evpdf_, Site> dispatching_evpdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::evpdf_, Site>();
   }
   template<class... Args>
   struct impl_evpdf_;
  }
  /*!
    Extreme value distribution with location parameter mu and scale parameter sigma

    returns the pdf of the type 1 extreme value

    Default values for mu and sigma are 0 and 1, respectively.

    The type 1 extreme value distribution is also known as the Gumbel
    distribution.  The version used here is suitable for modeling minima; the
    mirror image of this distribution can be used to model maxima by negating
    x.  if y has a Weibull distribution, then x=log(y) has the type 1 extreme
    value distribution.

    @par Semantic:

    For every table expression

    @code
    auto r = evpdf(x{, mu, sigma});
    @endcode

    computes

    \f$ r = \f$ (\exp((\mu-x)/\sigma)\exp(-\exp((\mu-x)/\sigma)))/sigma \f$

    @see @funcref{weibullpdf}, @funcref{exppdf}
    @param x
    @param mu first distribution parameter
    @param sigma second  distribution parameter

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::evpdf_, evpdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evpdf_, evpdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evpdf_, evpdf, 1)

}

#endif
