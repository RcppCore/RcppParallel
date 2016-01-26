//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_ACSCH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_ACSCH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief acsch generic tag

     Represents the acsch function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acsch_ : ext::elementwise_<acsch_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acsch_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_acsch_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::acsch_, Site> dispatching_acsch_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::acsch_, Site>();
   }
   template<class... Args>
   struct impl_acsch_;
  }
  /*!
    Returns the hyperbolic cosecant argument \f$\mathop{\textrm{asinh}}(1/a_0)\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acsch(x);
    @endcode

    is similar to:

    @code
    T0 r = asinh(rec(x));
    @endcode

    @see @funcref{asinh}, @funcref{sinh}, @funcref{rec}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acsch_, acsch, 1)
}

#endif

