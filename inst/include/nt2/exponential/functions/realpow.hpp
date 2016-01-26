//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_REALPOW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_REALPOW_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief realpow generic tag

     Represents the realpow function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct realpow_ : ext::elementwise_<realpow_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<realpow_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_realpow_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::realpow_, Site> dispatching_realpow_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::realpow_, Site>();
   }
   template<class... Args>
   struct impl_realpow_;
  }
  /*!
    Returns power function,  but
    asserts if the result is to be complex

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = realpow(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = pow(a0, a1);
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::realpow_, realpow, 2)
}

#endif

