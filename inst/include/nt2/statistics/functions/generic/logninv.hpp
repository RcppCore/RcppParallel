//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNINV_HPP_INCLUDED
#include <nt2/statistics/functions/logninv.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/simd/erfcinv.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/sqrt.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( logninv0_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return  exp(-Sqrt_2<A0>()*erfcinv( nt2::Two<A0>()*a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( logninv0_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                             )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {

      return  exp(-Sqrt_2<A0>()*erfcinv( nt2::Two<A0>()*a0)+a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( logninv0_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "sigma(s) must be positive");
      return  exp(-Sqrt_2<A0>()*a2*erfcinv( nt2::Two<A0>()*a0)+a1);
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( logninv_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::logninv_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename boost::proto::result_of::child_c<A0&,2>::type          In2;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      doit(a0, a1, N0(), N1());
    }
    ////////////////////////////////////////////
    // No enough inputs to computes all ouputs
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0&, A1&,
                                       boost::mpl::long_<1> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<2> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
      boost::proto::child_c<0>(a1) =  nt2::logninv(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0&,  A1&,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");

    }
    ////////////////////////////////////////////
    // No enough output to computes all ouputs
    ////////////////////////////////////////////
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::logninv(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::logninv(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    ////////////////////////////////////////////
    // Regular cases
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1, value_type(0.05));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1,boost::proto::child_c<4>(a0));
    }


    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const value_type& alpha )
    {
      typedef nt2::memory::container<tag::table_, value_type, nt2::_2D>  semantic;
      NT2_AS_TERMINAL_IN(semantic, pcov, boost::proto::child_c<3>(a0));
      const In0& p  = boost::proto::child_c<0>(a0);
      const In1& mu = boost::proto::child_c<1>(a0);
      const In2& sigma = boost::proto::child_c<2>(a0);
      auto logx0 = -Sqrt_2<A0>()*erfcinv( nt2::Two<A0>()*p);
      auto xvar =   fma(fma(pcov(2,2), logx0, Two<value_type>()*pcov(1,2)), logx0, pcov(1,1));
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_nltz(xvar)), "Covariance matrix must be positive");
      value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
      auto halfwidth = normz*nt2::sqrt(xvar);
      boost::proto::child_c<0>(a1) = exp(fma(sigma, logx0, mu));
      auto coef = exp(-halfwidth);
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a1)*coef;
      boost::proto::child_c<2>(a1) = boost::proto::child_c<0>(a1)/coef;
    }

  };

} }

#endif
