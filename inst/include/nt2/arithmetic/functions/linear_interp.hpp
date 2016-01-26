//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the linear_interp function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for liner_interp functor
    **/
    struct linear_interp_ : ext::abstract_<linear_interp_>
    {
      typedef ext::abstract_<linear_interp_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_linear_interp_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::linear_interp_, Site> dispatching_linear_interp_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::linear_interp_, Site>();
    }
    template<class... Args>
    struct impl_linear_interp_;
  }

  /*!
    Returns sx-expansion of (1-dx)*a+dx*b
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::linear_interp_, linear_interp, 3)
}

#endif
