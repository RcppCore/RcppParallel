//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GEQRF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GEQRF_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements qrf function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines qrf function tag
    struct geqrf_ : ext::abstract_<geqrf_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<geqrf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_geqrf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::geqrf_, Site> dispatching_geqrf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::geqrf_, Site>();
    }
    template<class... Args>
    struct impl_geqrf_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::geqrf_, geqrf
                                  , (A0&)(A1&)
                                  , 2
                                  );
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::geqrf_, geqrf
                                  , (A0&)(A1&)(A2&)
                                  , 3
                                  );
}

#endif
