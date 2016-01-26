//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::relative_index function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct relative_index_ : ext::abstract_<relative_index_>
    {
      typedef ext::abstract_<relative_index_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_relative_index_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::relative_index_, Site> dispatching_relative_index_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::relative_index_, Site>();
    }
    template<class... Args>
    struct impl_relative_index_;
  }

  //============================================================================
  /*!
   * Performs an index translation to be used in indexed access computation
   *
   * \param a0 xpr Indexing expression
   * \param a1 bi  Base indexes of indexed expression
   * \param a2 sz  Sizes of indexed expression
   * \param a3 idx Index being computed
   * \param a4 target Desired index type
   * \return The translated index to access current indexing expression
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::relative_index_, relative_index, 5)
}

#endif
