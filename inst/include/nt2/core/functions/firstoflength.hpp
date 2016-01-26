//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIRSTOFLENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIRSTOFLENGTH_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the nt2::firstoflength function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for firstoflength functor
    **/
    struct firstoflength_ : ext::abstract_<firstoflength_>
    {
      typedef ext::abstract_<firstoflength_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_firstoflength_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::firstoflength_, Site> dispatching_firstoflength_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::firstoflength_, Site>();
    }
    template<class... Args>
    struct impl_firstoflength_;
  }

  /*!
    @brief First  dimension of given length

    For a given expression, returns the first dimension which is equal to a
    given value. If none exists, firstoflength returns 0.

    @param a0 Expression to inspect
    @param a1 length to match
    @return The value of the first dimension of length a1.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::firstoflength_,firstoflength,2)
}

#endif
