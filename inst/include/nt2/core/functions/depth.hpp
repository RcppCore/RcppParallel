//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DEPTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DEPTH_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the depth function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for depth function
    **/
    struct depth_ : ext::abstract_<depth_>
    {
      typedef ext::abstract_<depth_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_depth_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::depth_, Site> dispatching_depth_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::depth_, Site>();
    }
    template<class... Args>
    struct impl_depth_;
  }

  /*!
    @brief Size along the 3rd dimension of expressions

    Compute the number of element along the third dimension in a given entity.

    @param a0 Expression to compute the size in number of elements

    @return The number of elements stored in \c xpr along its third dimension
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::depth_, depth, 1)
}

#endif
