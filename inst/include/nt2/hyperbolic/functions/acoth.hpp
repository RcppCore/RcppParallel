//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_ACOTH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_ACOTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief acoth generic tag

     Represents the acoth function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acoth_ : ext::elementwise_<acoth_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acoth_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_acoth_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::acoth_, Site> dispatching_acoth_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::acoth_, Site>();
   }
   template<class... Args>
   struct impl_acoth_;
  }
  /*!
    Returns the hyperbolic cotangent argument \f$\frac12\log\frac{a_0^2+1}{a_0^2-1}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acoth(x);
    @endcode

    is similar to:

    @code
    T0 r = Half<T0>()*log((x*x+one)/(x*x-one));
    @endcode

    @see @funcref{log}, @funcref{Half}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acoth_, acoth, 1)
}

#endif

