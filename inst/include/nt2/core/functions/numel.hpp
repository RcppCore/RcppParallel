//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NUMEL_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the numel function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tag for the numel functor
    **/
    struct numel_ : ext::abstract_<numel_>
    {
      typedef ext::abstract_<numel_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_numel_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::numel_, Site> dispatching_numel_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::numel_, Site>();
    }
    template<class... Args>
    struct impl_numel_;
  }

  /*!
    @brief Number of elements of an expression

    Compute the number of element stored in a given entity.

    @param  a0 Expression to inspect
    @return The number of elements stored in a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::numel_, numel, 1)

  /*!
    @brief

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::numel_, numel, 2)
}

#endif
