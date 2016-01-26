//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_STDEV_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_STDEV_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    struct stdev_ : ext::abstract_<stdev_>
    {
      /// @brief Parent hierarchy
       typedef ext::abstract_<stdev_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_stdev_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::stdev_, Site> dispatching_stdev_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::stdev_, Site>();
    }
    template<class... Args>
    struct impl_stdev_;
  }
  /*!
    @brief standard deviation of a table expression along a given dimension

    Returns the variance of a table expression along a given dimension

    @par Semantic

    For any table expression of T @c t integer or weights w and any
    integer @c n:

    @code
    auto r = stddev(t, w, n);
    @endcode

    is equivalent to:

    @code
    auto r = sqrt(var(t, w, n));
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{var}, @funcref{sqrt}
    @param a0 Table expression to process
    @param a1 normalization hint or table expression of weights
    @param a2 Dimension along which to process a0

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::stdev_       , stdev, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::stdev_       , stdev, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::stdev_       , stdev, 1)

}

#endif
