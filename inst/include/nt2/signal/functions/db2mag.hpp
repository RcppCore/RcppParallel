//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_SIGNAL_FUNCTIONS_DB2MAG_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_DB2MAG_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the db2mag functor
    **/
    struct db2mag_ : ext::elementwise_<db2mag_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<db2mag_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_db2mag_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::db2mag_, Site> dispatching_db2mag_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::db2mag_, Site>();
    }
    template<class... Args>
    struct impl_db2mag_;
  }
  /*!
    @brief Convert decibels (dB) to magnitude

    Computes the decibels to magnitude.

    @par Semantic

    For any table expression:

    @code
    auto d = db2mag(d);
    @endcode

    is equivalent to:

    @code
    auto d = exp10(d/2);
    @endcode

    @see @funcref{exp10}, @funcref{db},
    @funcref{pow2db}, @funcref{db2pow}, @funcref{db2pow}
    @param a0 Table expression to process


    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::db2mag_, db2mag, 1)
}

#endif
