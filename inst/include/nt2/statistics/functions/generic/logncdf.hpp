//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_LOGNCDF_HPP_INCLUDED
#include <nt2/statistics/functions/logncdf.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/simd/erfc.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_gez.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/norminv.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( logncdf0_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x = if_zero_else(is_lez(a0), a0);
      return Half<A0>()*nt2::erfc(-Sqrt_2o_2<A0>()*log(x));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( logncdf0_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A0 x = if_zero_else(is_lez(a0), a0);
      return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>()*(a1-log(x)));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( logncdf0_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(nt2::colvect(a2))), "sigma(s) must be positive");
      A0 x = if_zero_else(is_lez(a0), a0);
      return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>()*((a1-log(x))/a2));
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( logncdf_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::logncdf_, N0, nt2::container::domain>))
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
    // Not enough inputs to computes all ouputs
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
      boost::proto::child_c<0>(a1) =  nt2::logncdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0&,  A1&,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");

    }
    ////////////////////////////////////////////
    // Not enough output to computes all ouputs
    ////////////////////////////////////////////
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::logncdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<5> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::logncdf(boost::proto::child_c<0>(a0),
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
      const In0& x  = boost::proto::child_c<0>(a0);
      const In1& mu = boost::proto::child_c<1>(a0);
      const In2& sigma = boost::proto::child_c<2>(a0);
      auto z = (log(if_zero_else(is_lez(x), x))-mu)/sigma;
      // this is [1, x0]*pcov*[1; x0]
      auto zvar = fma(fma(pcov(2,2), z, Two<value_type>()*pcov(1,2)), z, pcov(1,1));
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(zvar)), "Covariance matrix must be positive");
      value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
      auto halfwidth =  normz*nt2::sqrt(zvar)/sigma;
      boost::proto::child_c<0>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*z);
      boost::proto::child_c<1>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z-halfwidth));
      boost::proto::child_c<2>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z+halfwidth));
    }

  };

} }

#endif
