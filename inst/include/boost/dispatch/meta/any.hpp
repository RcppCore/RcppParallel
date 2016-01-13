//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ANY_HPP_INCLUDED
#define BOOST_DISPATCH_META_ANY_HPP_INCLUDED

#include <boost/mpl/not.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace dispatch
{
  namespace details
  {
    template<bool Check, typename Predicate, typename ...Args>
    struct any_impl;

    template<typename Predicate, typename ...Args>
    struct  any_impl<true,Predicate,Args...>
          : boost::mpl::true_
    {};

    template<typename Predicate, typename Head, typename ...Tail>
    struct  any_impl<false,Predicate,Head,Tail...>
          : any_impl< boost::mpl::apply1<Predicate,Head>::type::value
                    , Predicate
                    , Tail...
                    >
    {};

    template<typename Predicate, typename Head>
    struct  any_impl<false,Predicate,Head>
          : boost::mpl::apply1<Predicate,Head>::type
    {};
  }

  namespace meta
  {
    /*!
      @brief any combinator for types list

      Evaluates if a given unary Boolean @metafunction evaluates to @true_
      for any types in a list of types.

      @tparam Pred Boolean @metafunction
      @tparam Args Types to check

      @par Models:

      @metafunction

      @par Semantic:

      For any unary Boolean @metafunction @c Pred and any types
      <tt>T0,...,Tn</tt>:

      @code
      typedef any<Pred,T0,...,Tn>::type type;
      @endcode

      is equivalent to

      @code
      typedef mpl::bool_<  apply<Pred,T0>::type::value
                        || apply<Pred,T1>::type::value
                        ...
                        || apply<Pred,Tn>::type::value
                        >::type type;
      @endcode

      @par Usage:

      @include any.cpp
    **/
    template<typename Predicate, typename ...Args>
    struct any;

    /// INTERNAL ONLY
    template<typename Predicate, typename Head, typename ...Tail>
    struct  any<Predicate,Head,Tail...>
          : details::any_impl < boost::mpl::apply1<Predicate,Head>::type::value
                              , Predicate
                              , Tail...
                              >
    {};

    /// INTERNAL ONLY
    template<typename Predicate, typename Head>
    struct  any<Predicate,Head>
          : boost::mpl::apply1<Predicate,Head>::type
    {};

    template<typename Predicate, typename T>
    struct  any_seq
          : boost::mpl
                 ::not_ < boost::is_same< typename boost::mpl
                                                        ::find_if<T,Predicate>::type
                                        , typename boost::mpl::end<T>::type
                                        >
                        >
    {};
  }
} }

#endif
