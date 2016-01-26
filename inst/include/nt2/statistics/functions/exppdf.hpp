//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EXPPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EXPPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief exppdf generic tag

     Represents the exppdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exppdf_ : ext::elementwise_<exppdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exppdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_exppdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::exppdf_, Site> dispatching_exppdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::exppdf_, Site>();
   }
   template<class... Args>
   struct impl_exppdf_;
  }
  /*!
    exponential  distribution

    @par Semantic:

    For every table expression

    @code
    auto r = exppdf(a0, lambda);
    @endcode

    is similar to:

    @code
    auto r = lambda*exp(-a0*lambda);
    @endcode

    @see @funcref{exp}
    @param a0
    @param a1 optional mean (default to 1)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exppdf_, exppdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::exppdf_, exppdf, 1)
}

#endif
