//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_LOG_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief log generic tag

     Represents the log function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct log_ : ext::elementwise_<log_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<log_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_log_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::log_, Site> dispatching_log_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::log_, Site>();
   }
   template<class... Args>
   struct impl_log_;
  }
  /*!
    Natural logarithm function.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = log(x);
    @endcode

    @see @funcref{log10}, @funcref{log2}, @funcref{log1p}

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log_, log, 1)
}

#endif

