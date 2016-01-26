//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NORMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NORMP_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the normp functor
    **/
    struct normp_ : ext::abstract_<normp_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<normp_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_normp_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::normp_, Site> dispatching_normp_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::normp_, Site>();
    }
    template<class... Args>
    struct impl_normp_;
  }
  /*!
    @brief Sum of the p power of absolute values of table to 1/p


    Computes the 1/p power of the sum of the pth power of the absolute
    value of all the elements of a table expression along its first
    non-singleton dimension : the \f$l_p\f$ norm

    @par Semantic

    For any table expression @c t and any arithmetic value @c
    p and integer n :

    @code
    auto r = normp(t,p,n);
    @endcode

    is equivalent to:

    @code
    auto r = pow_abs(asump(t),1/p),n);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{pow_abs}
    @param a0 Table expression to process
    @param a1 Power at which absolute values are raised
    @param a2 Dimension along which to process a0

    @return An expression eventually evaluated to the result

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normp_       , normp, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normp_       , normp, 2)
}

#endif
