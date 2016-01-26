//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_BETALN_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_BETALN_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief betaln generic tag

     Represents the betaln function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct betaln_ : ext::elementwise_<betaln_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<betaln_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_betaln_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::betaln_, Site> dispatching_betaln_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::betaln_, Site>();
   }
   template<class... Args>
   struct impl_betaln_;
  }
  /*!
    Computes Betaln function : logarithm of beta function,  without computing beta

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r = betaln(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = gammaln(a0)+gammaln(a1)-gammaln(a0+a1);
    @endcode

    @see @funcref{gamma}, @funcref{beta}
    @param a0
    @param a1

    @return a value of the same type as the parameters
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::betaln_, betaln, 2)
}

#endif
