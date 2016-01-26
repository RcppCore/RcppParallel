//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_TRSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_TRSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/trsolve.hpp>
#include <nt2/core/functions/transpose.hpp>
#include <nt2/core/functions/ctranspose.hpp>
#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/alias.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/settings/locality.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <boost/proto/traits.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace tag
{
  struct side
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'L';
    }
  };

  struct diag
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'N';
    }
  };

} }

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::trsolve_,Domain,N,Expr>
        : meta::size_as<Expr,1>
  {};


  template<class Domain, int N, class Expr>
  struct  value_type<tag::trsolve_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

} }

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      trsolve(a0, a1, One<T>(), tag::blas_normal_(), shape::id_value , tag::side(), tag::diag() )
    )
  };


  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&,0>::type    child0;
    typedef typename boost::dispatch::meta::terminal_of<typename boost::dispatch::meta::
                     semantic_of<child0>::type>::type                in0_t;
    typedef typename meta::option<typename in0_t::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      trsolve(boost::proto::child_c<0>(a0), a1, One<T>(), tag::blas_transpose_(), shape::id_value, tag::side(), tag::diag() )
    )
  };


  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&,0>::type    child0;
    typedef typename boost::dispatch::meta::terminal_of<typename boost::dispatch::meta::
                     semantic_of<child0>::type>::type                in0_t;
    typedef typename meta::option<typename in0_t::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      trsolve(boost::proto::child_c<0>(a0), a1, One<T>(), tag::blas_ctranspose_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(a0, a1, a2, tag::blas_normal_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&,0>::type    child0;
    typedef typename boost::dispatch::meta::terminal_of<typename boost::dispatch::meta::
                     semantic_of<child0>::type>::type                in0_t;
    typedef typename meta::option<typename in0_t::settings_type,nt2::tag::shape_>::type shape;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(boost::proto::child_c<0>(a0), a1, a2, tag::blas_transpose_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&,0>::type    child0;
    typedef typename boost::dispatch::meta::terminal_of<typename boost::dispatch::meta::
                     semantic_of<child0>::type>::type                in0_t;
    typedef typename meta::option<typename in0_t::settings_type,nt2::tag::shape_>::type shape;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(boost::proto::child_c<0>(a0), a1, a2, tag::blas_ctranspose_(), shape::id_value, tag::side(), tag::diag() )
    )
  };

  // no shape for input matrix so add it as a parameter

    BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< ints8_<A2> >)
                            )
  {
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(a0, a1, One<T>(), tag::blas_normal_(), a2 , tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< ints8_<A2> >)
                            )
  {
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(boost::proto::child_c<0>(a0), a1, One<T>(), tag::blas_transpose_(), a2 , tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< ints8_<A2> >)
                            )
  {
    typedef typename A0::value_type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      trsolve(boost::proto::child_c<0>(a0), a1, One<T>(), tag::blas_ctranspose_(), a2 , tag::side(), tag::diag() )
    )
  };

  BOOST_DISPATCH_IMPLEMENT  ( trsolve_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)(A6)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                              (unspecified_<A6>)
                            )
  {
    BOOST_DISPATCH_RETURNS(7, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4,A5 const& a5,A6 const& a6),
                                 (boost::proto:: make_expr<nt2::tag::trsolve_, container::domain>
                                    (boost::cref(a0), boost::cref(a1), boost::cref(a2), boost::cref(a3), boost::cref(a4), boost::cref(a5), boost::cref(a6))
                                 )
    )
  };

  // run_assign
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::trsolve_, boost::mpl::long_<7> , nt2::container::domain>))
                            )
  {
    typedef A0& result_type;
    typedef typename A1::proto_child1::proto_child0::value_type T;
    typedef typename meta::option<typename A1::proto_child1::proto_child0::settings_type
                                 ,nt2::tag::shape_
                                 >::type shape;

    typedef typename meta::option<typename A1::proto_child1::proto_child0::settings_type
                                 ,tag::locality_
                                 ,typename  A1::proto_child1::proto_child0::kind_type
                                  >::type  locality_in;

    typedef typename meta::option<typename A0::settings_type
                                 ,tag::locality_
                                 ,typename A0::kind_type
                                  >::type  locality_out;

    typedef nt2::memory::container<tag::table_, T, nt2::settings(nt2::_2D,locality_in )> desired_semantic;
    typedef nt2::memory::container<tag::table_, T, nt2::settings(nt2::_2D,shape,locality_out)> desired_semantic1;

    result_type operator()(A0& a0, A1& a1) const
    {
      char side  =  boost::proto::value(boost::proto::child_c<5>(a1)).call();
      char diag  =  boost::proto::value(boost::proto::child_c<6>(a1)).call();
      char trans =  boost::proto::value(boost::proto::child_c<3>(a1)).call();
      char uplo  = boost::proto::value(boost::proto::child_c<4>(a1));
      T alpha    = boost::proto::value(boost::proto::child_c<2>(a1));

      NT2_AS_TERMINAL_INOUT(desired_semantic1,result,boost::proto::child_c<1>(a1),a0);
      NT2_AS_TERMINAL_IN(desired_semantic,in,boost::proto::child_c<0>(a1));

      nt2::trsm(side, uplo, trans, diag, boost::proto::value(in)
                                       , boost::proto::value(result) , alpha );

      assign_swap(a0, result);

      return a0;
    }
  };
}
}

#endif
