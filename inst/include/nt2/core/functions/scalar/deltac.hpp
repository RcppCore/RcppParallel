//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_DELTAC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_DELTAC_HPP_INCLUDED

#include <nt2/core/functions/deltac.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/functions/details/delta.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( deltac_, tag::cpu_
                            , (A0)(A1)(D1)(D2)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<D1> >)
                              (scalar_<integer_<D2> >)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 5
                                , ( A0 i, A1 j, D1 d1, D2 d2, T const& t)
                                , ( A0 i, A1 j, D1 d1, D2 d2, T const&)
                                , (nt2::deltac(i, j, nt2::as_size(d1,d2), T()))
                                )
  };

  BOOST_DISPATCH_IMPLEMENT  ( deltac_, tag::cpu_
                            , (A0)(A1)(D1)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<D1> >)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 i, A1 j, D1 d1, T const& t)
                                , ( A0 i, A1 j, D1 d1, T const&)
                                , (nt2::deltac(i, j, nt2::as_size(d1), T()))
                                )
  };

  BOOST_DISPATCH_IMPLEMENT  ( deltac_, tag::cpu_
                            , (A0)(A1)(FS)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (fusion_sequence_<FS>)
                              (target_<scalar_< unspecified_<T> > > )
                            )
  {
    typedef meta::constant_<nt2::meta::delta_<0>,typename T::type>  constant_t;
    typedef meta::as_<typename constant_t::base_type>               target_t;

    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 i, A1 j, FS const& sz, T const& t)
                                , ( A0 i, A1 j, FS const& sz, T const& )
                                , ( boost::proto
                                         ::make_expr< nt2::tag::deltac_
                                                    , container::domain
                                                    > ( sz
                                                      , constant_t(i, j)
                                                      , target_t()
                                                      )
                                  )
                                )
  };
} }

#endif
