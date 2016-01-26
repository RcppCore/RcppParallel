//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_RSF2CSF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_RSF2CSF_HPP_INCLUDED

#include <nt2/linalg/functions/rsf2csf.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/utility/assign_swap.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( rsf2csf_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<floating_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& ) const
    {
      BOOST_ASSERT_MSG(is_real(a0), "diagonal is not valid");
      return result_type(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( rsf2csf_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::rsf2csf_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type    child0;
    typedef typename child0::value_type                                     type_t;
    typedef typename nt2::meta::as_real<type_t>::type                      rtype_t;
    typedef typename nt2::meta::as_complex<rtype_t>::type                  ctype_t;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D> desired_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - [v, w] = rsf2csf(cv, cw)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
       auto& u = boost::proto::child_c<0>(a0);
       auto& t = boost::proto::child_c<1>(a0);
       container::table<ctype_t> cu = u;
       container::table<ctype_t> ct = t;

       std::size_t n = size(t, 2);
       for(std::size_t m = n; m >= 2; --m)
       {
         std::size_t dm = dec(m);
         if(t(m, dm))
         {
           auto k = _(dm, m);
           auto mu = nseig(t(k,k)) - t(m,m);
           rtype_t r = rec(hypot(mu(1), t(m,m-1)));
           ctype_t c = mu(1)*r;
           ctype_t s = ct(m,m-1)*r;
           container::table<ctype_t> g = cons<ctype_t>(of_size(2, 2), conj(c), -s, s, c);
           ct(k,_(m-1, n)) = mtimes(g, ct(k,_(m-1, n)));
           ct(_(1, m),k) = mtimes(ct(_(1, m),k), ctrans(g));
           cu(_,k) = mtimes(u(_,k), ctrans(g));
           ct(m,dm) = 0;
         }
       }
       assign_swap(boost::proto::child_c<0>(a1), cu);
       assign_swap(boost::proto::child_c<1>(a1), ct);
    }



  };
} }

#endif
