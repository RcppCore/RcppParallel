//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief normrnd generic tag

     Represents the normrnd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct normrnd_ : ext::abstract_<normrnd_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<normrnd_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_normrnd_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::normrnd_, Site> dispatching_normrnd_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::normrnd_, Site>();
   }
   template<class... Args>
   struct impl_normrnd_;
  }

  /*!
    normal pseudo random numbers generator

    @par Semantic:

    For every table expressions and  scalars m and s of type T0

    @code
    auto r = normrnd(m, s, <sizing parameters>);
    @endcode

    generates a table expression of random numbers following the uniform distribution
    on interval [a, b[ and of size defined by the sizing parameters

    @code
    auto r = s*randn(<sizing parameters>, as_<T0>())+m;
    @endcode

      - if as_<T0>() is not present the type of the generated elements is defined as
        being the type of a,

      - unifrnd(as_<T0>()) by himself generates one value of type T0, assuming m = 0, s = 1,

      - unifrnd() assumes T0 is double.

    @see @funcref{as_},  @funcref{randn}
    @param a0 points of evaluation
    @param a1
    @param a2
    @param a3
    @param a4
    @param a5
    @param a6

    @return an expression which eventually will evaluate to the result
  **/
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 7)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 2)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 3)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 4)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 5)
  /// @overload
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 6)
  /// @overload
}

#endif
