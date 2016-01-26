//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GESVX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GESVX_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements lapack gesvx function that computes the solution
  of real system of linear equations a*x = b with an lu decomposition done with
  the lapack function dgetrf. Iterative refinement is applied to increase the
  precision.
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines gesvx function tag
    struct gesvx_ : ext::abstract_<gesvx_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<gesvx_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_gesvx_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::gesvx_, Site> dispatching_gesvx_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::gesvx_, Site>();
    }
    template<class... Args>
    struct impl_gesvx_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::gesvx_, gesvx
                                  , (A0 const&)(A1 const&)(A2&)(A3&)
                                  , 4
                                  );




}

#endif
