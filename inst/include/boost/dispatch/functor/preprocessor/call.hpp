//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

//==============================================================================
/*!
 * Generates a implement \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1.
 *
 * \param N Number of parameters for the current implement
 *
 *
 * \code
 * BOOST_DISPATCH_CALL(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_CALL(N)                                                 \
result_type operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A,const& a) ) const      \
/**/

//==============================================================================
/*!
 * Generates a implement specialization \c operator() prototype
 * along with a result_type typedef.
 *
 * \param N Number of parameters for the current implement
 * \param Args Arguments to the function, with type and name
 * \param Body Function body, must be a single expression
 *
 *
 * \code
 * BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
 *   a0 + a1/a2
 * )
 * \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_RETURNS(N, Args, Body)                                  \
BOOST_DISPATCH_RETURNS_ARGS(N,Args,Args, Body)                                 \
/**/

#define BOOST_DISPATCH_RETURNS_ARGS(N, Args, Call, Body)                       \
struct dispatch_returns_impl                                                   \
{                                                                              \
  BOOST_PP_REPEAT(N, BOOST_DISPATCH_RETURNS_, (N, Args))                       \
  typedef decltype(Body) result_type;                                          \
};                                                                             \
typedef typename dispatch_returns_impl::result_type result_type;               \
BOOST_FORCEINLINE result_type operator()Call const { return Body; }            \
/**/

#define BOOST_DISPATCH_RETURNS_(z, n, Args)                                    \
static BOOST_PP_ARRAY_ELEM(n, Args);                                           \
/**/

//==============================================================================
/*!
 * Generates a implement \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1 of the same type
 * \c A0.
 *
 * \param N Number of parameters for the current implement
 *
 * \code
 * BOOST_DISPATCH_CALL_REPEAT(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_CALL_REPEAT(N)                                          \
result_type operator()( BOOST_PP_ENUM_PARAMS(N,A0 const& a) ) const            \
/**/

//==============================================================================
// Variants that dispatch to implement_Tag<Sig, Site>
//==============================================================================

#define BOOST_DISPATCH_IMPLEMENT_BODY(Tag, Site, Types, Seq, M)                \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types), M, Types ) >                \
struct BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq)                           \
/**/

#define BOOST_DISPATCH_IMPLEMENT(Tag, Site, Types, Seq)                        \
BOOST_DISPATCH_REGISTER(Tag, Site, Types, Seq)                                 \
BOOST_DISPATCH_IMPLEMENT_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE)      \
/**/

#define BOOST_DISPATCH_IMPLEMENT_TPL(Tag, Site, Types, Seq)                    \
BOOST_DISPATCH_REGISTER_TPL(Tag, Site, Types, Seq)                             \
BOOST_DISPATCH_IMPLEMENT_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE_TPL)  \
/**/

#define BOOST_DISPATCH_IMPLEMENT_IF(Tag, Site, Types, Cond, Seq)               \
BOOST_DISPATCH_REGISTER_IF(Tag, Site, Types, Cond, Seq)                        \
BOOST_DISPATCH_IMPLEMENT_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE)      \
/**/

#define BOOST_DISPATCH_IMPLEMENT_TPL_IF(Tag, Site, Types, Cond, Seq)           \
BOOST_DISPATCH_REGISTER_TPL_IF(Tag, Site, Types, Cond, Seq)                    \
BOOST_DISPATCH_IMPLEMENT_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE_TPL)  \
/**/

//==============================================================================
// Variants that dispatch to implement<Sig, Site>
//==============================================================================

#define BOOST_DISPATCH_IMPLEMENT_G_BODY(Tag, Site, Types, Seq, M)              \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types), M, Types ) >                \
struct BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq)                         \
/**/

#define BOOST_DISPATCH_IMPLEMENT_G(Tag, Site, Types, Seq)                      \
BOOST_DISPATCH_REGISTER_G(Tag, Site, Types, Seq)                               \
BOOST_DISPATCH_IMPLEMENT_G_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE)    \
/**/

#define BOOST_DISPATCH_IMPLEMENT_G_TPL(Tag, Site, Types, Seq)                  \
BOOST_DISPATCH_REGISTER_G_TPL(Tag, Site, Types, Seq)                           \
BOOST_DISPATCH_IMPLEMENT_G_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE_TPL)\
/**/

#define BOOST_DISPATCH_IMPLEMENT_G_IF(Tag, Site, Types, Cond, Seq)             \
BOOST_DISPATCH_REGISTER_G_IF(Tag, Site, Types, Cond, Seq)                      \
BOOST_DISPATCH_IMPLEMENT_G_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE)    \
/**/

#define BOOST_DISPATCH_IMPLEMENT_G_TPL_IF(Tag, Site, Types, Cond, Seq)         \
BOOST_DISPATCH_REGISTER_G_TPL_IF(Tag, Site, Types, Cond, Seq)                  \
BOOST_DISPATCH_IMPLEMENT_G_BODY(Tag, Site, Types, Seq, BOOST_DISPATCH_TYPE_TPL)\
/**/

#endif
