//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for registering a functor overload
 */

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>

// Helpers that strips each element of a sequence
#define BOOST_DISPATCH_TYPE_TPL(z,n,t) BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_TYPE(z,n,t) class BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_ELEM(n,t))

// XXXMathias: 'const' prevents using TPPs
#define BOOST_DISPATCH_ARG(z,n,t) , BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_ELEM(n,t)) /*const*/
#define BOOST_DISPATCH_TAG(z,n,t) BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_ELEM(n,t))

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq).
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TO(Tag, Site, Types, Seq, Ret)                 \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE                                   \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
BOOST_PP_REMOVE_PARENS(Ret)                                                   \
BOOST_PP_CAT(dispatching_, Tag)( adl_helper                                    \
           , BOOST_PP_REMOVE_PARENS(Site)                                     \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                          )                                                    \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TPL_TO(Tag, Site, Types, Seq, Ret)             \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE_TPL                               \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
BOOST_PP_REMOVE_PARENS(Ret)                                                   \
BOOST_PP_CAT(dispatching_, Tag)( adl_helper                                    \
           , BOOST_PP_REMOVE_PARENS(Site)                                     \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq) and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TO_IF(Tag, Site, Types, Cond, Seq, Ret)        \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE                                   \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
typename boost::enable_if< BOOST_PP_REMOVE_PARENS(Cond)                       \
                         , BOOST_PP_REMOVE_PARENS(Ret)                        \
                         >::type                                               \
BOOST_PP_CAT(dispatching_, Tag)( adl_helper                                    \
           , BOOST_PP_REMOVE_PARENS(Site)                                     \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TPL_TO_IF(Tag, Site, Types, Cond, Seq, Ret)    \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE_TPL                               \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
typename boost::enable_if< BOOST_PP_REMOVE_PARENS(Cond)                       \
                         , BOOST_PP_REMOVE_PARENS(Ret)                        \
                         >::type                                               \
BOOST_PP_CAT(dispatching_, Tag)( adl_helper                                    \
           , BOOST_PP_REMOVE_PARENS(Site)                                     \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
// Variants that dispatch to implement_Tag<Sig, Site>
//==============================================================================

#define BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq)                          \
BOOST_PP_CAT(impl_, Tag)                                                       \
         < void                                                                \
           ( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Seq)                             \
                          , BOOST_DISPATCH_TAG                                 \
                          , Seq                                                \
                          )                                                    \
           )                                                                   \
         , BOOST_PP_REMOVE_PARENS(Site)                                       \
         >                                                                     \
/**/

#define BOOST_DISPATCH_REGISTER(Tag, Site, Types, Seq)                         \
BOOST_DISPATCH_REGISTER_TO( Tag, Site, Types, Seq                              \
                          , ( BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq)    \
                            )                                                  \
                          )                                                    \
/**/

#define BOOST_DISPATCH_REGISTER_TPL(Tag, Site, Types, Seq)                     \
BOOST_DISPATCH_REGISTER_TPL_TO( Tag, Site, Types, Seq                          \
                              , ( BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq) \
                                )                                              \
                              )                                                \
/**/

#define BOOST_DISPATCH_REGISTER_IF(Tag, Site, Types, Cond, Seq)                \
BOOST_DISPATCH_REGISTER_TO_IF( Tag, Site, Types, Cond, Seq                     \
                             , ( BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq) \
                               )                                               \
                             )                                                 \
/**/

#define BOOST_DISPATCH_REGISTER_TPL_IF(Tag, Site, Types, Cond, Seq)            \
BOOST_DISPATCH_REGISTER_TPL_TO_IF( Tag, Site, Types, Cond, Seq                 \
                                 , ( BOOST_DISPATCH_IMPLEMENT_IMPL(Tag, Site, Seq) \
                                   )                                           \
                                 )                                             \
/**/


//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq).
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_G_TO(Tag, Site, Types, Seq, Ret)               \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE                                   \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
BOOST_PP_REMOVE_PARENS(Ret)                                                   \
dispatching( adl_helper                                                        \
           , BOOST_PP_REMOVE_PARENS(Tag), BOOST_PP_REMOVE_PARENS(Site)       \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                          )                                                    \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_G_TPL_TO(Tag, Site, Types, Seq, Ret)           \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE_TPL                               \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
BOOST_PP_REMOVE_PARENS(Ret)                                                   \
dispatching( adl_helper                                                        \
           , BOOST_PP_REMOVE_PARENS(Tag), BOOST_PP_REMOVE_PARENS(Site)       \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq) and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_G_TO_IF(Tag, Site, Types, Cond, Seq, Ret)      \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE                                   \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
typename boost::enable_if< BOOST_PP_REMOVE_PARENS(Cond)                       \
                         , BOOST_PP_REMOVE_PARENS(Ret)                        \
                         >::type                                               \
dispatching( adl_helper                                                        \
           , BOOST_PP_REMOVE_PARENS(Tag), BOOST_PP_REMOVE_PARENS(Site)       \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_G_TPL_TO_IF(Tag, Site, Types, Cond, Seq, Ret)  \
template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                              \
                       , BOOST_DISPATCH_TYPE_TPL                               \
                       , Types                                                 \
                       )                                                       \
        >                                                                      \
BOOST_FORCEINLINE                                                    \
typename boost::enable_if< BOOST_PP_REMOVE_PARENS(Cond)                       \
                         , BOOST_PP_REMOVE_PARENS(Ret)                        \
                         >::type                                               \
dispatching( adl_helper                                                        \
           , BOOST_PP_REMOVE_PARENS(Tag), BOOST_PP_REMOVE_PARENS(Site)       \
             BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                           \
                            , BOOST_DISPATCH_ARG                               \
                            , Seq                                              \
                            )                                                  \
          )                                                                    \
{                                                                              \
  return BOOST_PP_REMOVE_PARENS(Ret)();                                       \
}                                                                              \
/**/

//==============================================================================
// Variants that dispatch to implement<Sig, Site>
//==============================================================================

#define BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq)                        \
implement< BOOST_PP_REMOVE_PARENS(Tag)                                        \
           ( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Seq)                             \
                          , BOOST_DISPATCH_TAG                                 \
                          , Seq                                                \
                          )                                                    \
           )                                                                   \
         , BOOST_PP_REMOVE_PARENS(Site)                                       \
         >                                                                     \
/**/

#define BOOST_DISPATCH_REGISTER_G(Tag, Site, Types, Seq)                       \
BOOST_DISPATCH_REGISTER_G_TO( Tag, Site, Types, Seq                            \
                          , ( BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq)  \
                            )                                                  \
                          )                                                    \
/**/

#define BOOST_DISPATCH_REGISTER_G_TPL(Tag, Site, Types, Seq)                   \
BOOST_DISPATCH_REGISTER_G_TPL_TO( Tag, Site, Types, Seq                        \
                              , ( BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq) \
                                )                                              \
                              )                                                \
/**/

#define BOOST_DISPATCH_REGISTER_G_IF(Tag, Site, Types, Cond, Seq)              \
BOOST_DISPATCH_REGISTER_G_TO_IF( Tag, Site, Types, Cond, Seq                   \
                             , ( BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq) \
                               )                                               \
                             )                                                 \
/**/

#define BOOST_DISPATCH_REGISTER_G_TPL_IF(Tag, Site, Types, Cond, Seq)          \
BOOST_DISPATCH_REGISTER_G_TPL_TO_IF( Tag, Site, Types, Cond, Seq               \
                                 , ( BOOST_DISPATCH_IMPLEMENT_IMPL_G(Tag, Site, Seq) \
                                   )                                           \
                                 )                                             \
/**/

#endif
