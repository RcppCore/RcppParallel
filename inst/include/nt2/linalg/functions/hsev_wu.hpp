//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_HSEV_WU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_HSEV_WU_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements hsev_wu function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines hsev_wu function tag
    struct hsev_wu_ : ext::abstract_<hsev_wu_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<hsev_wu_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_hsev_wu_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::hsev_wu_, Site> dispatching_hsev_wu_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::hsev_wu_, Site>();
    }
    template<class... Args>
    struct impl_hsev_wu_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::hsev_wu_, hsev_wu
                                  , (A0&)(A1&)(A2 const&)
                                  , 3
                                  );

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::hsev_wu_, hsev_wu
                                  , (A0&)(A1&)(A2 const&)(A3&)
                                  , 4
                                  );
}

#endif

