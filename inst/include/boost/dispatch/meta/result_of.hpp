//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED

#include <boost/dispatch/details/parameters.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/utility/enable_if.hpp>
#if !defined(BOOST_NO_SFINAE_EXPR)
#include <boost/utility/declval.hpp>
#endif

namespace boost { namespace dispatch
{
  namespace meta
  {
    #if !defined(BOOST_NO_SFINAE_EXPR)
    template<class Sig, class Enable = void>
    struct result_of_decltype {};
    #endif

    template<class Sig, class Enable = void>
    struct result_of
    #if !defined(BOOST_NO_SFINAE_EXPR)
         : result_of_decltype<Sig>
    #endif
    {};

    template<class T>
    struct is_function
      : boost::is_function<typename boost::remove_pointer<typename meta::strip<T>::type>::type>
    {
    };
  }
} }

namespace boost { namespace dispatch { namespace meta
{
#if !defined(BOOST_NO_SFINAE_EXPR)
  template<class F, class... Args>
  struct result_of_decltype<F(Args...), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<Args>()...) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<Args>()...) ) type;
  };
#endif

  template<class F, class... Args>
  struct result_of<F(Args...), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::template result<F(Args...)>::type >::type>
  {
    typedef typename F::template result<F(Args...)>::type type;
  };

} } }

#endif
