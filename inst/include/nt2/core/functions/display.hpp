//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the display function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the display functor
    **/
    struct display_ : ext::abstract_<display_>
    {
      typedef ext::abstract_<display_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_display_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::display_, Site> dispatching_display_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::display_, Site>();
    }
    template<class... Args>
    struct impl_display_;
  }

  /*!
    @brief Display a value as unnamed

    @c disp(a0) displays the content of @c a0 in a way similar to MATLAB and
    prefixed by the 'ans=' delimiter.

    @param a0 Value to display
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::display_,display,1)


  /*!
    @brief Display a value as unnamed

    @c disp(a0) displays the content of @c a0 in a way similar to MATLAB and
    prefixed by an arbitrary string.

    @param a0 Name of the value to display
    @param a1 Value to display
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::display_,display,2)
}

/*!
  @brief Display a named value

  For any given @c X, display the contents of @c X prefixed by the name of @c X
  or its declaration in case of anonymous data.
**/
#define NT2_DISPLAY(X) ::nt2::display(BOOST_PP_STRINGIZE(X),X)

#endif
