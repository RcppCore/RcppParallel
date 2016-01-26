//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_SYLVESTER_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_SYLVESTER_HPP_INCLUDED

#include <nt2/linalg/functions/sylvester.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2
{
  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( sylvester_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (scalar_< unspecified_<A0> >)
                                (scalar_< unspecified_<A1> >)
                                (scalar_< unspecified_<A2> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(3)
      {
        return a2/(a0+a1);
      }
    };
    BOOST_DISPATCH_IMPLEMENT  ( sylvester_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< unspecified_<A0> >)
                                (scalar_< unspecified_<A1> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(2)
      {
        return Half<A0>()*a1/a0;
      }
    };

    // sylvester tag only used for matrix
    template<class Domain, int N, class Expr>
    struct size_of<tag::sylvester_,Domain,N,Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
      typedef _2D                                                      result_type;
      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                         "sylvester needs a square matrix or a scalar");
        return nt2::extent(boost::proto::child_c<0>(e));
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::sylvester_, N, nt2::container::domain>))
                                )
    {
    typedef void                                                    result_type;
    typedef typename A1::value_type                                  value_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename meta::as_real<value_type>::type                     r_type;
    typedef typename meta::as_complex<r_type>::type                   cplx_type;
    typedef table<cplx_type>                                             ctab_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
    {
      compute_sylvester(a1, a0, N());
    }

    private:
      template < class T >
      BOOST_FORCEINLINE static void compute_sylvester(const T& a1
                                                     , A0& res
                                                     , boost::mpl::long_<3> const&)
      {
        // ua, ta, ub, tb and r are complex arrays to achieve
        // triangular schur decomposition
        res.resize(extent(a1));
        ctab_t ua, ta, ub, tb;
        ctab_t r;
        nt2::tie(ua, ta) = schur(boost::proto::child_c<0>(a1), nt2::cmplx_);
        nt2::tie(ub, tb) = schur(boost::proto::child_c<1>(a1), nt2::cmplx_);
        ctab_t c = boost::proto::child_c<2>(a1);
        auto z1 = mtimes(mtimes(ctrans(ua), c), ub);
        ctab_t z2;
        if (isdiagonal(ta)&&isdiagonal(tb))
        {
          z2 =  sylv_diag(ta,tb,z1);
        }
        else
        {
          z2 = sylv_tri(ta,tb,z1);
        }
        r = mtimes(mtimes(ua, z2), ctrans(ub));
        transtype(res, r, typename nt2::meta::is_complex<value_type>::type());
      }

      template < class T >
      BOOST_FORCEINLINE static void compute_sylvester(const T& a1
                                                     , A0& res
                                                     , boost::mpl::long_<2> const&)
        // this is sylvester  a*x+x*a = c
      {
        //ua, ta and r are complex arrays to achieve triangular schur decomposition
        res.resize(extent(a1));
        ctab_t ua, ta;
        ctab_t r;
        nt2::tie(ua, ta) = schur(boost::proto::child_c<0>(a1), nt2::cmplx_);
        ctab_t c = boost::proto::child_c<1>(a1);
        auto z1 = mtimes(mtimes(ctrans(ua), c), ua);
        ctab_t z2;
        if (isdiagonal(ta))
        {
          z2 =  sylv_diag(ta,ta,z1);
        }
        else
        {
          z2 = sylv_tri(ta,ta,z1);
        }
        r = mtimes(mtimes(ua, z2), ctrans(ua));
        transtype(res, r, typename nt2::meta::is_complex<value_type>::type());
      }

      template < class T, class U, class B >
      static inline ctab_t sylv_tri(const T& t,const U& u, const B& b)
      {
        // sylv_tri    solve triangular sylvester equation.
        //    x = sylv_tri(t,u,b) solves the sylvester equation
        //  t*x + x*u = b, where t and u are square upper triangular matrices.

        uint32_t m = length(t);
        uint32_t n = length(u);
        ctab_t x = zeros(m,n, nt2::meta::as_<cplx_type>());
        for(uint32_t i = 1;  i <= n; ++i)
        {
          ctab_t bb = b(nt2::_,i);
          auto ii =  nt2::_(1u, i-1);
          if(!isempty(ii)) bb -= mtimes(x(nt2::_,ii),u(ii,i));
          x(nt2::_,i) = linsolve(t + u(i,i)*eye(m, meta::as_<cplx_type>()), bb);
        }
        return x;
      }

      template < class T, class U, class B >
      static inline ctab_t sylv_diag(const T& t, const U& u, const B & b)
      {
        // sylv_diag    solve diagonal sylvester equation.
        //    x = sylv_tri(t,u,b) solves the sylvester equation
        //  t*x + x*u = b, where t and u are diagonal matrices.
        return b/sx(nt2::tag::plus_(), rowvect(diag_of(u)), diag_of(t));
      }

      template < class T1, class T2 >
      BOOST_FORCEINLINE static void transtype(T1& r, T2& z
                                             , boost::mpl::false_ const &)
      {
        r =  real(z);
      }

      template < class T1, class T2 >
      BOOST_FORCEINLINE static void transtype(T1& r, T2& z
                                             , boost::mpl::true_ const &)
      {
        r =  z;
      }
    };
  }
}

#endif
