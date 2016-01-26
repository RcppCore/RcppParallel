//==============================================================================
//          Copyright 2015 - J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIGNIFICANTS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIGNIFICANTS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief significants generic tag

     Represents the significants function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct significants_ : ext::elementwise_<significants_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<significants_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_significants_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::significants_, Site> dispatching_significants_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::significants_, Site>();
   }
   template<class... Args>
   struct impl_significants_;
  }
  /*!
    Compute the rounding to n significants digits

    @par Semantic:

    For every parameter of floating type T0 and strictly positive integer n

    @code
    T0 r = significants(x, n);
    @endcode

    is equivalent to round(x, m) where m is n-iceil(log10(abs(a0)))

    @see @funcref{pow}, @funcref{boost::simd::sqrt}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::significants_, significants, 2)
}

#endif

