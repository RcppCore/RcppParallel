//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/sdk/memory/is_safe.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // table terminal with a position in scalar read mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(K0)(S0)(State)(Data)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (target_<scalar_<unspecified_<Data> > >)
                            )
  {

    typedef typename boost::dispatch::meta::
    scalar_of<A0&>::type                               result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const&) const
    {
      return boost::proto::value(a0)[state];
    }
  };

  //============================================================================
  // table terminal with a position in scalar write mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(S0)(K0)(State)(Data)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (scalar_<unspecified_<Data> >)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of<A0&>::type                                result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const& data) const
    {
      return boost::proto::value(a0)[state] = data;
    }
  };

  //============================================================================
  // table terminal with a position in SIMD read mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(S0)(K0)(State)(Data)(X)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((target_< simd_<unspecified_<Data>, X> >))
                            )
  {
    typedef typename Data::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, State const& state, Data const&) const
    {
      BOOST_ASSERT_MSG
      ( nt2::memory::is_safe<result_type>(boost::proto::value(a0),state)
      , "Out of range SIMD read"
      );

      return boost::simd::load<result_type>(a0.data(), state);
    }
  };

  //============================================================================
  // table terminal with a position in SIMD write mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(S0)(K0)(State)(Data)(X)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((simd_<unspecified_<Data>, X>))
                            )
  {
    typedef Data                                            result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, State const& state, Data const& data) const
    {
      BOOST_ASSERT_MSG
      ( nt2::memory::is_safe<result_type>(boost::proto::value(a0),state)
      , "Out of range SIMD read"
      );

      boost::simd::store(data, a0.data(), state);
      return data;
    }
  };

  //============================================================================
  // scalar terminal, return value in read mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(State)(Data)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (target_< scalar_< unspecified_<Data> > >)
                            )
  {
    typedef typename nt2::meta::call<T0(A0&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const&, Data const&) const
    {
      return boost::proto::value(a0);
    }
  };

  //============================================================================
  // scalar terminal, assign value in write mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(State)(Data)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (scalar_< unspecified_<Data> >)
                            )
  {
    typedef typename nt2::meta::call<T0(A0&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const&, Data const& data) const
    {
      return boost::proto::value(a0) = data;
    }
  };

  //============================================================================
  // scalar terminal return value after a cast in SIMD read mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(State)(Data)(X)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>,X > >))
                            )
  {
    typedef typename Data::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, State const&, Data const&) const
    {
      return boost::simd::splat<result_type>(boost::proto::value(a0));
    }
  };

  //============================================================================
  // scalar terminal, error in SIMD write mode
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( terminal_, tag::cpu_
                            , (A0)(T0)(State)(Data)(X)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T0
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((simd_< unspecified_<Data>,X >))
                            )
  {
    typedef Data const&      result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0&, State const&, Data const& data) const
    {
      BOOST_ASSERT_MSG(0, "Writing SIMD value to scalar not allowed");
      return data;
    }
  };
} }

#endif
