#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/include/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/meta/identity.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/selection/min.hpp>

#include <boost/utility/declval.hpp>
#include <boost/config.hpp>

namespace nt2 { namespace ext
{
  /* Adapt Data with Expr whenever it is a target */
  template<class Expr, class Data>
  struct adapt_data
  {
    typedef Data const& type;
    BOOST_FORCEINLINE static type call(Data const& data)
    {
      return data;
    }
  };

  template<class Expr, class Data>
  struct adapt_data< Expr, boost::dispatch::meta::as_<Data> >
  {
    typedef boost::dispatch::meta::as_<typename Expr::value_type> type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_<Data> const&)
    {
      return type();
    }
  };

  template<class Expr, class T, class X>
  struct adapt_data< Expr, boost::dispatch::meta::as_< boost::simd::native<T, X> > >
  {
    typedef boost::dispatch::meta::as_<
      typename boost::simd::meta::vector_of<
        typename Expr::value_type
      , boost::simd::meta::cardinal_of< boost::simd::native<T, X> >::value
      >::type
    > type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_< boost::simd::native<T, X> > const&)
    {
      return type();
    }
  };

  //============================================================================
  // Run an expression without state nor data
  //============================================================================
  #define M0(z,n,t)                                                                                                    \
  t( dispatching_run_( ext::adl_helper(), boost::dispatch::default_site_t<T>()                                         \
                     , boost::dispatch::meta::                                                                         \
                       hierarchy_of_t<typename boost::proto::result_of::child_c<Expr&, n>::type>()                     \
                     )                                                                                                 \
                     ( boost::proto::child_c<n>(expr) )                                                                \
   )                                                                                                                   \
  /**/

  //============================================================================
  // Run an expression with a state and a data
  //============================================================================
  #define M0d(z,n,t)                                                                                                   \
  t( dispatching_run_( ext::adl_helper(), boost::dispatch::default_site_t<T>()                                         \
                     , boost::dispatch::meta::                                                                         \
                       hierarchy_of_t<typename boost::proto::result_of::child_c<Expr&, n>::type>()                     \
                     , boost::dispatch::meta::                                                                         \
                       hierarchy_of_t<State const&>()                                                                  \
                     , boost::dispatch::meta::                                                                         \
                       hierarchy_of_t<typename adapt_data< typename boost::proto::result_of::                          \
                                                           child_c<Expr&, n>::value_type                               \
                                                         , Data                                                        \
                                                         >::type>()                                                    \
                     )                                                                                                 \
                     ( boost::proto::child_c<n>(expr)                                                                  \
                     , state                                                                                           \
                     , adapt_data< typename boost::proto::result_of::                                                  \
                                   child_c<Expr&, n>::value_type                                                       \
                                 , Data                                                                                \
                                 >::call(data)                                                                         \
                     )                                                                                                 \
    )                                                                                                                  \
  /**/

  #define MHIERARCHY(e) boost::dispatch::meta::hierarchy_of_t<decltype(e)>()
  #define MIDENTITY(e) e

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PP_MIN( BOOST_DISPATCH_MAX_ARITY              \
                                                           , BOOST_PROTO_MAX_ARITY                 \
                                                           )                                       \
                                          , "nt2/dsl/functions/generic/run.hpp"                    \
                                          )                                                        \
                                      )
  #include BOOST_PP_ITERATE()

  #undef M0
  #undef M1
  #undef MHIERARCHY
  #undef MIDENTITY

  //============================================================================
  // Run an expression with a state and data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT          ( run_, tag::cpu_
                                    , (A0)(T)(D)
                                    , ((node_<A0, unspecified_<T>, boost::mpl::long_<0>, D>))
                                    )
  {
    BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE operator()(A0& a0) const
    BOOST_AUTO_DECLTYPE_BODY
    (
      T::dispatch( boost::dispatch::default_site_t<T>()
                 , boost::dispatch::meta::hierarchy_of_t<A0&>()
                 )
                 ( a0 )
    )

    #ifdef BOOST_MSVC
    typedef decltype( boost::declval<impl_run_ const&>()(boost::declval<A0&>()) ) result_type;
    #else
    typedef decltype( (((impl_run_ const*)0)->*&impl_run_::operator())(*(A0*)0) ) result_type;
    #endif
  };

  BOOST_DISPATCH_IMPLEMENT          ( run_, tag::cpu_
                                    , (A0)(T)(D)(State)(Data)
                                    , ((node_<A0, unspecified_<T>, boost::mpl::long_<0>, D>))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE operator()(A0& a0, State const& state, Data const& data) const
    BOOST_AUTO_DECLTYPE_BODY
    (
      T::dispatch( boost::dispatch::default_site_t<T>()
                 , boost::dispatch::meta::hierarchy_of_t<A0&>()
                 , boost::dispatch::meta::hierarchy_of_t<State const&>()
                 , boost::dispatch::meta::hierarchy_of_t<Data const&>()
                 )
                 ( a0, state, data )
    )

    #ifdef BOOST_MSVC
    typedef decltype( boost::declval<impl_run_ const&>()(boost::declval<A0&>(), boost::declval<State const&>(), boost::declval<Data const&>()) ) result_type;
    #else
    //typedef decltype( (((impl_run_ const*)0)->*&impl_run_::operator())(*(A0*)0, *(State const*)0, *(Data const*)0) ) result_type;
    #endif
  };
} }

#endif
#else /* BOOST_PP_IS_ITERATING */

#define n BOOST_PP_ITERATION()

  BOOST_DISPATCH_IMPLEMENT          ( run_, tag::formal_
                                    , (Expr)(T)(D)
                                    , ((node_<Expr, unspecified_<T>, boost::mpl::long_<n>, D>))
                                    )
  {
    BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE operator()(Expr& expr) const
    BOOST_AUTO_DECLTYPE_BODY
    (
      T::dispatch( boost::dispatch::default_site_t<T>()
                 , BOOST_PP_ENUM(n, M0, MHIERARCHY)
                 )
                 ( BOOST_PP_ENUM(n, M0, MIDENTITY) )
    )

    #ifdef BOOST_MSVC
    typedef decltype( boost::declval<impl_run_ const&>()(boost::declval<Expr&>()) ) result_type;
    #else
    typedef decltype( (((impl_run_ const*)0)->*&impl_run_::operator())(*(Expr*)0) ) result_type;
    #endif
  };

  BOOST_DISPATCH_IMPLEMENT          ( run_, tag::cpu_
                                    , (Expr)(T)(D)(State)(Data)
                                    , ((node_<Expr, unspecified_<T>, boost::mpl::long_<n>, D>))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE operator()(Expr& expr, State const& state, Data const& data) const
    BOOST_AUTO_DECLTYPE_BODY
    (
      T::dispatch( boost::dispatch::default_site_t<T>()
                 , BOOST_PP_ENUM(n, M0d, MHIERARCHY)
                 )
                 ( BOOST_PP_ENUM(n, M0d, MIDENTITY) )
    )

    #ifdef BOOST_MSVC
    typedef decltype( boost::declval<impl_run_ const&>()(boost::declval<Expr&>(), boost::declval<State const&>(), boost::declval<Data const&>()) ) result_type;
    #else
    //typedef decltype( (((impl_run_ const*)0)->*&impl_run_::operator())(*(Expr*)0, *(State const*)0, *(Data const*)0) ) result_type;
    #endif
  };

#undef n

#endif
