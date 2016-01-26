//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISVECTOR_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISVECTOR_HPP_INCLUDED

/*!
  @file
  @brief Defines the isvector function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for isvector functor
    **/
    struct isvector_ : ext::abstract_<isvector_>
    {
      typedef ext::abstract_<isvector_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_isvector_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::isvector_, Site> dispatching_isvector_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::isvector_, Site>();
    }
    template<class... Args>
    struct impl_isvector_;
  }

  /*!
    @brief Is an expression vector shaped ?

    Checks if an expression has a size of the shape [N ... 1]  or [1 N ... 1].

    @param a0 Expression to inspect

    @return Boolean value evaluating to the result of the test

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isvector_, isvector, 1)
}

#endif

