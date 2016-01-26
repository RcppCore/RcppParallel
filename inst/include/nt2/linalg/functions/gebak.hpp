//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GEBAK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GEBAK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements gebak function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines gebak function tag
    struct gebak_ : ext::abstract_<gebak_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<gebak_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_gebak_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::gebak_, Site> dispatching_gebak_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::gebak_, Site>();
    }
    template<class... Args>
    struct impl_gebak_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::gebak_, gebak
                                  , (A0&)(A1 const&)(A2 const&)(A3 const&)(A4 const&)(A5 const&)
                                  , 6
                                  );

}

#endif

