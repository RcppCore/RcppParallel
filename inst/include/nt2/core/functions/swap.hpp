//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SWAP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SWAP_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines swap function tag
    struct swap_ : ext::abstract_<swap_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<swap_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_swap_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::swap_, Site> dispatching_swap_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::swap_, Site>();
    }
    template<class... Args>
    struct impl_swap_;
  }

  /*!
    @brief Swap values

    Swap values between expression of same number of element.

    @param First expression to swap
    @param Second expression to swap
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::swap_, swap, (A0&)(A1&)            , 2);
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::swap_, swap, (A0 const&)(A1&)      , 2);
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::swap_, swap, (A0 &)(A1 const&)     , 2);
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::swap_, swap, (A0 const&)(A1 const&), 2);
}

#endif
