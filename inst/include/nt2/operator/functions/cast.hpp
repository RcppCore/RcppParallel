//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_CAST_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_CAST_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the cast functor
    **/
    struct cast_ : ext::abstract_<cast_>
    {
      typedef ext::abstract_<cast_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cast_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::cast_, Site> dispatching_cast_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::cast_, Site>();
    }
    template<class... Args>
    struct impl_cast_;
  }

  /*!
    @brief Expression level type casting

    cast convert the value of an expression into values of a different type.

    @tparam T  Type to convert a0 to.
    @param  a0 Expression to typecast
  **/
  template<class T, class A0> BOOST_FORCEINLINE
  typename meta::call<tag::cast_(A0 const&, meta::as_<T> const&)>::type
  cast(A0 const& a0)
  {
    return typename make_functor<tag::cast_, A0>::type()(a0, meta::as_<T>());
  }

  /*!
    @brief Expression level type casting

    cast convert the value of an expression into values of a different type.

    @param a0 Expression to typecast
    @param c  Typeclass to convert a0 to
  **/
  template<class T, class A0> BOOST_FORCEINLINE
  typename meta::call<tag::cast_(A0 const&, meta::as_<T> const&)>::type
  cast(A0 const& a0, meta::as_<T> const& c)
  {
    return typename make_functor<tag::cast_, A0>::type()(a0, c);
  }
}

#endif
