//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISVECTORALONG_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISVECTORALONG_HPP_INCLUDED

/*!
  @file
  @brief Defines the isvectoralong function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for isvectoralong functor
    **/
    struct isvectoralong_ : ext::abstract_<isvectoralong_>
    {
      typedef ext::abstract_<isvectoralong_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_isvectoralong_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::isvectoralong_, Site> dispatching_isvectoralong_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::isvectoralong_, Site>();
    }
    template<class... Args>
    struct impl_isvectoralong_;
  }

  // TODO merge as isvector(x,d) ?
  /*!
    @brief Is an expression vector shaped along a dimension ?

    Checks if an expression has a size of the shape [1 1 .. N... 1 1] where the
    only non-singleton dimension is the kth dimension.

    @param a0 Expression to inspect
    @param a1 Dimension along which to check for vector shape

    @return Boolean value evaluatign to the result of the test
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isvectoralong_, isvectoralong, 2)
}

#endif
