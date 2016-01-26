//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_cosd generic tag

     Represents the fast_cosd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_cosd_ : ext::elementwise_<fast_cosd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_cosd_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fast_cosd_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::fast_cosd_, Site> dispatching_fast_cosd_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::fast_cosd_, Site>();
   }
   template<class... Args>
   struct impl_fast_cosd_;
  }
  /*!
    cosine of the angle in degree, in the interval \f$[-45, 45]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_cosd(x);
    @endcode

    is similar to:

    @code
    T0 r = cosd(x);
    @endcode

    provided that x belongs to \f$[-45, 45]\f$

    @see @funcref{cosd}, @funcref{sincosd}, @funcref{cos}, @funcref{cospi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cosd_, fast_cosd, 1)
}

#endif


