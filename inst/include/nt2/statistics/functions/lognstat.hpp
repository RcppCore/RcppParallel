//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_LOGNSTAT_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_LOGNSTAT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for lognstat function
    struct lognstat_ : ext::elementwise_<lognstat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<lognstat_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lognstat_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lognstat_, Site> dispatching_lognstat_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lognstat_, Site>();
    }
    template<class... Args>
    struct impl_lognstat_;
  }
  /*!
    Computes mean and variance of the lognormal distribution from mean and standard deviation
    of the associated normal distribution

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 m, v;
    tie(m, v) = lognstat(mu, sigma);
    @endcode

    @see @funcref{lognpdf}, @funcref{logncdf}, @funcref{logninv}, @funcref{lognrnd}
    @param mu mean of the associated normal distribution
    @param sigma standard deviation of the associated normal distribution

    @return A Fusion Sequence containing m and v
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::lognstat_, lognstat, 2)

  /*!
    Computes mean and variance of the lognormal distribution from mean and standard deviation
    of the associated normal distribution

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 m, v;
    m = lognstat(mu, sigma, v);
    @endcode

    @see @funcref{lognpdf}, @funcref{logncdf}, @funcref{logninv}, @funcref{lognrnd}
    @param mu mean of the associated normal distribution
    @param sigma standard deviation of the associated normal distribution
    @param v L-Value that will receive the variance

    @return  m and computes v

  **/


    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::lognstat_, lognstat,(A0 const&)(A1 const&)(A2&),3)

  /*!
    Computes mean and variance of the lognormal distribution from mean and standard deviation
    of the associated normal distribution

    @par Semantic:

    For every parameters of floating type T0:

    @see @funcref{normpdf}, @funcref{normcdf}, @funcref{norminv}, @funcref{normrnd}
    @param mu mean of the associated normal distribution
    @param sigma standard deviation of the associated normal distribution

    @code
    T0 m, v;
    lognstat(mu, sigma, m, v);
    @endcode

    @return void, computes m and v

    @param mu mean of the associated normal distribution
    @param sigma standard deviation of the associated normal distribution
    @param m L-Value that will receive the mean
    @param v L-Value that will receive the variance

  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::lognstat_, lognstat,(A0 const&)(A1 const&)(A2&)(A3&),4)

}


#endif

