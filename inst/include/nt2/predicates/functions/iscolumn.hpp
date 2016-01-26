//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISCOLUMN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISCOLUMN_HPP_INCLUDED

/*!
  @file
  @brief Defines the iscolumn function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for iscolumn functor
    **/
    struct iscolumn_ : ext::abstract_<iscolumn_>
    {
      typedef ext::abstract_<iscolumn_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_iscolumn_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::iscolumn_, Site> dispatching_iscolumn_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::iscolumn_, Site>();
    }
    template<class... Args>
    struct impl_iscolumn_;
  }

  /*!
    @brief Test for "column-like" status

    Returns @c true iff the size of a0 is of the form [N 1]

    @param  a0 the first parameter of iscolumn
    @return a boolean value indicating the "column-like" status of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::iscolumn_, iscolumn, 1)
}

#endif
