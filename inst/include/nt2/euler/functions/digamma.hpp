//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief digamma generic tag

     Represents the digamma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct digamma_ : ext::elementwise_<digamma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<digamma_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_digamma_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::digamma_, Site> dispatching_digamma_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::digamma_, Site>();
   }
   template<class... Args>
   struct impl_digamma_;
  }
  /*!
    Computes digamma function,  i.e. the logarithmic derivative of the \f$\Gamma\f$ function

    Note that the accuracy is not uniformly good for negative entries
    The algorithm used is currently an adapted vesion of the cephes one.
    For better accuracy in the negative entry case one can use the extern boost_math digamma
    functor, but at a loss of speed.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = digamma(x);
    @endcode

    Computes:  \f$\Digamma(a_0) = \frac{\Gamma^\prime(x)}{\Gamma(x}\f$

    Note: The function is reliable for positive values, but can be inaccurate
    at negative inputs around its poles that are the non-positives integers.

    float version is as good as boost/math one, but the double version
    is computed using double (!) and can be not so accurate than boost/math
    which uses long double in these circumstances.

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::digamma_, digamma, 1)
}

#endif

