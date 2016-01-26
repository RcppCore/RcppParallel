//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXPRECNEG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXPRECNEG_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag {
    /*!
      @brief exprecneg generic tag

      Represents the exprecneg function in generic contexts.

      @par Models:
         Hierarchy
    **/
    struct exprecneg_ : ext::elementwise_<exprecneg_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exprecneg_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&& ... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_exprecneg_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::exprecneg_, Site>
    dispatching_exprecneg_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::exprecneg_, Site>();
    }
    template<class... Args>
    struct impl_exprecneg_;
  }
  /*!
    Computes the  function: \f$e^{-\frac1x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = exprecneg(a0);
    @endcode

    is similar to
    @code
    T0 r = exp(-rec((a0)));
    @endcode


    @see @funcref{exp}, @funcref{exprecnegc}
    @param a0

    @return a value of the same type as the (floating) input parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exprecneg_, exprecneg, 1)
}

#endif

