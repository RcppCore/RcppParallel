//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_LOGSPACE_ADD_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_LOGSPACE_ADD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief logspace_add generic tag

     Represents the logspace_add function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logspace_add_ : ext::elementwise_<logspace_add_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logspace_add_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logspace_add_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::logspace_add_, Site> dispatching_logspace_add_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::logspace_add_, Site>();
   }
   template<class... Args>
   struct impl_logspace_add_;
  }
  /*!
     Compute the log of a sum from logs of terms
     properly compute \f$\log (\exp (\log x) + \exp (\log y))\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = logspace_add(x, y);
    @endcode

    is similar to:

    @code
    T0 r = log(exp(log(x)) + exp(log(y)));
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::logspace_add_, logspace_add, 2)
}

#endif

