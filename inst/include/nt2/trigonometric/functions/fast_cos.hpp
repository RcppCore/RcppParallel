//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_cos generic tag

     Represents the fast_cos function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_cos_ : ext::elementwise_<fast_cos_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_cos_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fast_cos_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::fast_cos_, Site> dispatching_fast_cos_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::fast_cos_, Site>();
   }
   template<class... Args>
   struct impl_fast_cos_;
  }
  /*!
    cosine in the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_cos(x);
    @endcode

    is similar to:

    @code
    T0 r = cos(x) ;
    @endcode

    provided that x belongs to \f$[-\pi/4, \pi/4]\f$

    @see @funcref{cosine}, @funcref{cos}, @funcref{sincos}, @funcref{cosd}, @funcref{cospi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cos_, fast_cos, 1)
}

#endif


