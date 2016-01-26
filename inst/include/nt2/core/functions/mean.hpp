//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MEAN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the mean functor
    **/
    struct mean_ : ext::abstract_<mean_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<mean_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mean_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mean_, Site> dispatching_mean_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mean_, Site>();
    }
    template<class... Args>
    struct impl_mean_;
  }
  /*!
   @brief mean of a table along a given dimension

    Compute the mean of the  elements of a table expression
    along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = mean(t,n);
    @endcode

    is equivalent to:

    @code
    auto r = sum(t,n)/size(a, n);
    @endcode


    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{size},

    @param a0 Table to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::mean_       , mean, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::mean_       , mean, 1)
}

#endif
