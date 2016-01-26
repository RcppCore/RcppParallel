//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED


#include <nt2/statistics/functions/caurnd.hpp>
#include <nt2/include/functions/cauinv.hpp>
#include <nt2/include/functions/rand.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates caurnd from expression (support size(a) + type calls)
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                              , (A0)
                              , (scalar_<floating_<A0> > )
                               (scalar_<floating_<A0> > )
                            )
  {
    typedef meta::as_<A0>                                                           TGT;
    typedef typename meta::call<tag::rand_(TGT)>::type                              T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type    result_type;
    //    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale) const
    {
      return cauinv(nt2::rand(meta::as_<A0>()), median, scale);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<floating_<A0> > )
                              (scalar_<floating_<A0> > )
                              (unspecified_<A1>)
                            )
  {
    typedef meta::as_<A0>                                                           TGT;
    typedef typename meta::call<tag::rand_(const A1&, TGT)>::type                   T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type    result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale, A1 const& a1) const
    {
      return cauinv(nt2::rand(a1, meta::as_<A0>()), median, scale);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<floating_<A0> > )
                              (scalar_<floating_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef meta::as_<A0>                                                            TGT;
    typedef typename meta::call<tag::rand_(const A1&, const A2&, TGT)>::type         T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale,
                                             A1 const& a1, A2 const& a2) const
    {
      return cauinv(nt2::rand(a1, a2, meta::as_<A0>()), median, scale);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<floating_<A0> > )
                              (scalar_<floating_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef meta::as_<A0>                                                           TGT;
    typedef typename meta::call<tag::rand_(const A1&, const A2&,  const A3&, TGT)>::type T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale,
                                             A1 const& a1, A2 const& a2,
                                             A3 const& a3) const
    {
      return cauinv(nt2::rand(a1, a2, a3, meta::as_<A0>()), median, scale);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (scalar_<floating_<A0> > )
                              (scalar_<floating_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef meta::as_<A0>                                                           TGT;
    typedef typename meta::call<tag::rand_(const A1&, const A2&,  const A3&, const A4,TGT)>::type                               T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale,
                                             A1 const& a1, A2 const& a2,
                                             A3 const& a3, A4 const& a4) const
    {
      return cauinv(nt2::rand(a1, a2, a3, a4, meta::as_<A0>()), median, scale);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( caurnd_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , (scalar_<floating_<A0> > )
                              (scalar_<floating_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    typedef meta::as_<A0>                                                           TGT;
    typedef typename meta::call<tag::rand_(const A1&, const A2&,
                                           const A3&, const A4&,
                                           const A5&, TGT)>::type                    T1;
    typedef typename meta::call<tag::cauinv_(T1,A0 const&,A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& median, A0 const& scale,
                                             A1 const& a1, A2 const& a2,
                                             A3 const& a3, A4 const& a4,
                                             A5 const& a5) const
    {
      return cauinv(nt2::rand(a1, a2, a3, a4, a5, meta::as_<A0>()), median, scale);
    }
  };


} }

#endif
