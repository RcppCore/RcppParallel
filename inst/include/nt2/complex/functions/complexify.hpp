//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_COMPLEXIFY_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_COMPLEXIFY_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the complexify function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the complexify functor
    **/
    struct complexify_ : ext::elementwise_<complexify_>
    {
      typedef ext::elementwise_<complexify_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_complexify_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::complexify_, Site> dispatching_complexify_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::complexify_, Site>();
    }
    template<class... Args>
    struct impl_complexify_;
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::complexify_, complexify, 1)

}

#endif
