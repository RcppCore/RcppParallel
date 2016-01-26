//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HEIGHT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HEIGHT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the height function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the height functor
    **/
    struct height_ : ext::abstract_<height_>
    {
      typedef ext::abstract_<height_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_height_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::height_, Site> dispatching_height_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::height_, Site>();
    }
    template<class... Args>
    struct impl_height_;
  }

  /*!
    @brief Height of an expression

    Return the number of element stored alogn the height of an expression.

    @param  a0 Expression to compute the size in number of elements
    @return The number of elements stored along the height of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::height_, height, 1)
}

#endif
