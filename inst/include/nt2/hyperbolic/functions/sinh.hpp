//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SINH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief sinh generic tag

     Represents the sinh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sinh_ : ext::elementwise_<sinh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sinh_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sinh_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::sinh_, Site> dispatching_sinh_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::sinh_, Site>();
   }
   template<class... Args>
   struct impl_sinh_;
  }
  /*!
    Returns the hyperbolic sine: \f$\frac{e^{a_0}-e^{-a_0}}2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = sinh(a0);
    @endcode

    is similar to:

    @code
    T0 r = Half<T0>()*(exp(x)-exp(-x));;
    @endcode

    @see @funcref{exp}, @funcref{cosh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinh_, sinh, 1)
}

#endif

