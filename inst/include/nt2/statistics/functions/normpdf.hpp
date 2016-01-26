//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_NORMPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_NORMPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief normpdf generic tag

     Represents the normpdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct normpdf_ : ext::elementwise_<normpdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<normpdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_normpdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::normpdf_, Site> dispatching_normpdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::normpdf_, Site>();
   }
   template<class... Args>
   struct impl_normpdf_;
  }
  /*!
    normal distribution density of mean m and standard deviation s

    @par Semantic:

    For every table expression

    @code
    auto r = normpdf(a0, m, s);
    @endcode

    is similar to:

    @code
    auto r = exp(sqr((a0-m)/s)/2)*Invsqrt_2pi/s;
    @endcode

    @see @funcref{exp}, @funcref{sqr}, @funcref{Invsqrt_2pi},
    @param a0
    @param a1 optional mean default to 0
    @param a2 optional standard deviation default to 1


    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::normpdf_, normpdf, 1)
}

#endif
