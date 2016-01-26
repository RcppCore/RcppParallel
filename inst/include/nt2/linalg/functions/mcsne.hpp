//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MCSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MCSNE_HPP_INCLUDED

/*!
  @file
  @brief Defines Semi-Normal Equations that solve R'(Rx) = A'b in mixed-precision
  with iterative refinement
  (based on Qr factorization)
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines sne function tag
    struct mcsne_ : ext::abstract_<mcsne_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<mcsne_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mcsne_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mcsne_, Site> dispatching_mcsne_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mcsne_, Site>();
    }
    template<class... Args>
    struct impl_mcsne_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
//
  // NT2_FUNCTION_IMPLEMENTATION(tag::mcsne_, mcsne, 2)
  // NT2_FUNCTION_IMPLEMENTATION(tag::mcsne_, mcsne, 3)
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mcsne_, mcsne, 3);
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mcsne_, mcsne, 2);

}

#endif
