//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_META_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_META_CALL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::dispatch::meta::call \metafunction
 */

#include <boost/config.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ref call is a \metafunction that, for a given \c Tag, \c EvalContext and
   * argument lists \c ...Args, computes the return type of
   * functor<Tag,EvalContext>::operator()(Args...).
   *
   * \param Sig         function type build from Tag(Args...)
   * \param EvalContext evaluation context to use for type deduction
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantics:
   * For a given \c Tag, \c EvalContext and argument lists \c ...Args,
   *
   * \code
   * typedef call<Tag(Args...),EvalContext>::type type;
   * \endcode
   *
   * is equivalent to:
   * \code
   * typedef decltype(functor<Tag,EvalContext>(declval<Args...>())) type;
   * \endcode
   */
  //============================================================================
  template< class Sig
          , class EvalContext = void
          > struct call {};

  template<class Tag, class... Args, class Site>
  struct  call<Tag(Args...),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<Args>::type...), Site>::type(Args...)>
  {
  };
} } }

#endif
