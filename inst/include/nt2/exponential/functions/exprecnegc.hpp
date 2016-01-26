//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXPRECNEGC_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXPRECNEGC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag {
    /*!
      @brief exprecnegc generic tag

      Represents the exprecnegc function in generic contexts.

      @par Models:
         Hierarchy
    **/
    struct exprecnegc_ : ext::elementwise_<exprecnegc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exprecnegc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&& ... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_exprecnegc_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::exprecnegc_, Site>
    dispatching_exprecnegc_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::exprecnegc_, Site>();
    }
    template<class... Args>
    struct impl_exprecnegc_;
  }
  /*!
    Computes the  function: \f$1-e^{-\frac1x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = exprecnegc(a0);
    @endcode

    is similar to
    @code
    T0 r = 1-exp(-rec((a0)));
    @endcode


    @see @funcref{exp}, @funcref{exprecneg}
    @param a0

    @return a value of the same type as the (floating) input parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exprecnegc_, exprecnegc, 1)
}

#endif

