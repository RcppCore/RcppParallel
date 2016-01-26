//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_POSVX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_POSVX_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements lapack posvx function that computes the solution
  of real system of linear equations a*x = b with a positive definite matrix.
  Iterative refinement is applied to increase the precision.
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines gesvx function tag
    struct posvx_ : ext::abstract_<posvx_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<posvx_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_posvx_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::posvx_, Site> dispatching_posvx_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::posvx_, Site>();
    }
    template<class... Args>
    struct impl_posvx_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::posvx_, posvx
                                  , (A0 const&)(A1 const&)(A2&)(A3&)
                                  , 4
                                  );

}

#endif
