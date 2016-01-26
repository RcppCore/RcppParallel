//==============================================================================
//         Copyright 2015 J.T. Laopreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_LYAPUNOV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_LYAPUNOV_HPP_INCLUDED

#include <nt2/linalg/functions/lyapunov.hpp>
#include <nt2/include/functions/sylvester.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2
{
  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( lyapunov_, tag::cpu_
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

    // lyapunov tag only used for matrix
    template<class Domain, int N, class Expr>
    struct size_of<tag::lyapunov_,Domain,N,Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
      typedef _2D                                                      result_type;
      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                         "lyapunov needs a square matrix or a scalar");
        return nt2::extent(boost::proto::child_c<0>(e));
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::lyapunov_, N, nt2::container::domain>))
                              )
    {
      typedef void                                                    result_type;

      BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
      {
        a0 = sylvester( ctrans(boost::proto::child_c<0>(a1))
                      , boost::proto::child_c<0>(a1)
                      , boost::proto::child_c<1>(a1));
      }
    };
  }
}

#endif
