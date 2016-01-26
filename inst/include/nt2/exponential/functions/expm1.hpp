//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXPM1_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief expm1 generic tag

     Represents the expm1 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct expm1_ : ext::elementwise_<expm1_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<expm1_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_expm1_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::expm1_, Site> dispatching_expm1_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::expm1_, Site>();
   }
   template<class... Args>
   struct impl_expm1_;
  }
  /*!
    exponential function minus one:\f$e^{x}-1\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = expm1(a0);
    @endcode

    is similar to:

    @code
    T0 r = exp(x)-one;
    @endcode

    \par Note:
    result is accurate even for small a0

    @see @funcref{exp}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expm1_, expm1, 1)
}

#endif

