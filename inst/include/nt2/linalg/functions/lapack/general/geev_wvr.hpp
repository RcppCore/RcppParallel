//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEEV_WVR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEEV_WVR_HPP_INCLUDED

#include <nt2/linalg/functions/geev_wvr.hpp>
#include <nt2/linalg/details/lapack/declare/geev.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/envblocksize.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/functions/details/combine.hpp>
#include <nt2/core/container/table/table.hpp>


namespace nt2 { namespace ext
{

  // the routines here compute only the eigenvalues and always in a complex colon vector
  //---------------------------------------------Real-double-w vr------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //vr
                             )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A2&w , A2& vr) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldvr = n;
      nt2_la_int ldvl = 1;
      NT2_F77NAME(dgeev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0/*wr*/, 0/*wi*/
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), details::query()
                         , &info);
      info = nt2::geev_wvr(a, w, vr, wk);
      return info;
    }
  };

  //---------------------------------------------Real-single-w vr------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //vr
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldvr = n;
      nt2_la_int ldvl = 1;
      NT2_F77NAME(sgeev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0/*wr*/, 0/*wi*/
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), details::query()
                         , &info);
      info = nt2::geev_wvr(a, w, vr, wk);
      return info;
     }
  };

//---------------------------------------------Complex-single-w vr------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //vr
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldvl = n;
      nt2_la_int ldvr = vr.leading_size();
      NT2_F77NAME(cgeev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0 /*w*/
                         , 0 /*vl*/, &ldvl
                         , 0 /*vr*/, &ldvr
                         , wk.main(), details::query()
                         , wk.reals()
                         , &info);
     info = nt2::geev_wvr(a, w, vr, wk);
      return info;
     }
  };

  //---------------------------------------------Complex-double-w vr------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //vr
                           )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = vr.leading_size();
      NT2_F77NAME(zgeev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0 /*w*/
                         , 0 /*vl*/, &ldvl
                         , 0 /*vr*/, &ldvr
                         , wk.main(), details::query()
                         , wk.reals()
                         , &info);
      info = nt2::geev_wvr(a, w, vr, wk);
      return info;
     }
  };

  //---------------------------------------------Real-double-w vr------------------------------------------------//
  /// INTERNAL ONLY - Workspace is ready
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //vr
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr, WK& wk) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2::container::table<double> wr(of_size(n, 1)),  wi(of_size(n, 1)), rvr(of_size(n, n));
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = rvr.leading_size();
      NT2_F77NAME(dgeev) ( &jobvl, &jobvr
                         , &n
                         , a.data() , &lda
                         , wr.data(), wi.data()
                         , 0, &ldvl
                         , rvr.data(), &ldvr
                         , wk.main(), &wn
                         , &info);
      details::combine_eigens(wr, wi, w);
      details::combine_vects(rvr, wi, vr);
      return info;
    }
  };

  //---------------------------------------------Real-single-w vr------------------------------------------------//
  /// INTERNAL ONLY - Workspace is ready
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //vr
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr, WK& wk) const
    {
      char jobvl = 'N';
      char jobvr = 'V';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2::container::table<float> wr(of_size(n, 1)),  wi(of_size(n, 1)), rvr(of_size(n, n));
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = rvr.leading_size();
      NT2_F77NAME(sgeev) ( &jobvl, &jobvr
                         , &n
                         , a.data() , &lda
                         , wr.data(), wi.data()
                         , 0, &ldvl
                         , rvr.data(), &ldvr
                         , wk.main(), &wn
                         , &info);
      details::combine_eigens(wr, wi, w);
      details::combine_vects(rvr, wi, vr);
      return info;
    }
  };



  //---------------------------------------------Complex-single-w vr------------------------------------------------//
  /// INTERNAL ONLY - Workspace is ready
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //vr
                              (unspecified_<WK>)                                              //workspace
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr, WK& wk) const
     {
       char jobvl = 'N';
       char jobvr = 'V';
       result_type info;
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
       nt2_la_int ldvl = 1;
       nt2_la_int ldvr = n;
       nt2_la_int wn = wk.main_need();
       wk.resize_main(wn);
       wk.resize_reals(2*n);
       w.resize(of_size(n, 1));
       NT2_F77NAME(cgeev) ( &jobvl, &jobvr
                          , &n
                          , a.data() , &lda
                          , w.data()
                          , 0, &ldvl
                          , vr.data(), &ldvr
                          , wk.main(), &wn
                          , wk.reals()
                          , &info);
        return info;
     }
  };

  //---------------------------------------------Complex-double-w vr------------------------------------------------//
  /// INTERNAL ONLY - Workspace is ready
  BOOST_DISPATCH_IMPLEMENT  ( geev_wvr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //vr
                              (unspecified_<WK>)                                              //workspace
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& vr, WK& wk) const
     {
       char jobvl = 'N';
       char jobvr = 'V';
       result_type info;
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
       nt2_la_int ldvl = 1;
       nt2_la_int ldvr = n;
       nt2_la_int wn = wk.main_need();
       wk.resize_main(wn);
       wk.resize_reals(2*n);
       w.resize(of_size(n, 1));
       NT2_F77NAME(zgeev) ( &jobvl, &jobvr
                          , &n
                          , a.data() , &lda
                          , w.data()
                          , 0, &ldvl
                          , vr.data(), &ldvr
                          , wk.main(), &wn
                          , wk.reals()
                          , &info);
        return info;
     }
  };
} }

#endif
