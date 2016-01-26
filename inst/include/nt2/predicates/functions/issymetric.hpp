//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISSYMETRIC_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISSYMETRIC_HPP_INCLUDED

/*!
  @file
  @brief Defines the issymetric function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for issymetric functor
    **/
    struct issymetric_ : ext::abstract_<issymetric_>
    {
      typedef ext::abstract_<issymetric_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_issymetric_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::issymetric_, Site> dispatching_issymetric_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::issymetric_, Site>();
    }
    template<class... Args>
    struct impl_issymetric_;
  }

  /*!
    @brief Is an expression symmetric ?

    Checks if an expression is a symmetric matrix.

    @param a0 Expression to inspect

    @return Boolean value evaluating to the result of the test
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::issymetric_, issymetric, 1)
}

#endif

