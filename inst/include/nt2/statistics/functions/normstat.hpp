//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_NORMSTAT_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_NORMSTAT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for normstat function
    struct normstat_ : ext::elementwise_<normstat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<normstat_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_normstat_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::normstat_, Site> dispatching_normstat_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::normstat_, Site>();
    }
    template<class... Args>
    struct impl_normstat_;
  }
  /*!
    Computes mean and variance of the normal distribution from mean and standard deviation

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 m, v;
    tie(m, v) = normstat(mu, sigma);
    @endcode

    is similar to:

    @code
    T0 m =  mu;
    T0 v =  sqr(sigma);
    @endcode

    @see @funcref{normpdf}, @funcref{normcdf}, @funcref{norminv}, @funcref{normrnd}
    @param mu mean
    @param sigma standard deviation

    @return A Fusion Sequence containing m and v
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::normstat_, normstat, 2)

  /*!
    Computes mean and variance of the normal distribution from mean and standard deviation

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 m, v;
    m = normstat(mu, sigma, v);
    @endcode

    is similar to:

    @code
    T0 m =  mu;
    T0 v =  sqr(sigma);
    @endcode

    @see @funcref{normpdf}, @funcref{normcdf}, @funcref{norminv}, @funcref{normrnd}
    @param mu mean
    @param sigma standard deviation
    @param v L-Value that will receive the variance

    @return  m

  **/


    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::normstat_, normstat,(A0 const&)(A1 const&)(A2&),3)

  /*!
    Computes mean and variance of the normal distribution from mean and standard deviation

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 m, v;
    normstat(mu, sigma, m, v);
    @endcode

    is similar to:

    @code
    T0 m =  mu;
    T0 v =  sqr(sigma);
    @endcode

    @see @funcref{normpdf}, @funcref{normcdf}, @funcref{norminv}, @funcref{normrnd}
    @param mu mean
    @param sigma standard deviation

    @return  m and computes v

    @param a0 angle in radian
    @param a1 L-Value that will receive the mean value
    @param a2 L-Value that will receive the variance

  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::normstat_, normstat,(A0 const&)(A1 const&)(A2&)(A3&),4)

}


#endif

