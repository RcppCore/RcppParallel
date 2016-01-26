//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_ERF_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_ERF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief erf generic tag

     Represents the erf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct erf_ : ext::elementwise_<erf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<erf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_erf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::erf_, Site> dispatching_erf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::erf_, Site>();
   }
   template<class... Args>
   struct impl_erf_;
  }
  /*!
    Computes the error function


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = erf(x);
    @endcode

    Computes: \f$\displaystyle \frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$

    @see @funcref{erfc}, @funcref{erfinv}, @funcref{erfcinv}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::erf_, erf, 1)
}

#endif

