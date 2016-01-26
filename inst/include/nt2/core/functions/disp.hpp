//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the disp function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the disp functor
    **/
    struct disp_ : ext::abstract_<disp_>
    {
      typedef ext::abstract_<disp_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_disp_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::disp_, Site> dispatching_disp_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::disp_, Site>();
    }
    template<class... Args>
    struct impl_disp_;
  }

  /*!
    @brief Display text or expressions

    @c disp(a0) displays the content of @c a0 in a way similar to MATLAB.

    @param a0 Value to display
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::disp_,disp,1)
}

#endif
