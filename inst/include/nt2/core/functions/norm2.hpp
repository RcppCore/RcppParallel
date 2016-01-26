//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NORM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NORM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the norm2 functor
    **/
    struct norm2_ : ext::abstract_<norm2_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<norm2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_norm2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::norm2_, Site> dispatching_norm2_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::norm2_, Site>();
    }
    template<class... Args>
    struct impl_norm2_;
  }
  /*!
    @brief euclidian norm of a table expression along a given dimension

    Returns the euclidian norm of a table along a given dimension

    @par Semantic

    For any table expression of T @c t integer or weights w   and any integer @c n:

    @code
    auto r = norm2(t, w, n);
    @endcode

    is equivalent to:

    if w is an integer

    @code
    auto r = sqrt(asum2(t, n));
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @par alias:
    norm_eucl

    @see @funcref{firstnonsingleton}, @funcref{asum2}, @funcref{sqrt}
    @param a0 Table expression to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm2, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm2, 1)

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm_eucl, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm_eucl, 2)
}

#endif
