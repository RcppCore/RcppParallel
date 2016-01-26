//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_LOGNPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_LOGNPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief lognpdf generic tag

     Represents the lognpdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct lognpdf_ : ext::elementwise_<lognpdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<lognpdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lognpdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::lognpdf_, Site> dispatching_lognpdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::lognpdf_, Site>();
   }
   template<class... Args>
   struct impl_lognpdf_;
  }
  /*!
    lognormal distribution density

    @par Semantic:

    @code
    auto r = lognpdf(a0, m, s);
    @endcode

    is similar to:

    @code
    auto r = exp(sqr((a0-m)/s)/2)*Invsqrt_2pi;
    @endcode

    @see @funcref{exp}, @funcref{sqr}, @funcref{Invsqrt_2pi},
    @param a0
    @param m optional mean of the associated normal distribution, default to 0
    @param s optional standard deviation of the associated normal distribution, default to 1


    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::lognpdf_, lognpdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::lognpdf_, lognpdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::lognpdf_, lognpdf, 1)
}

#endif
