//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_CDF2RDF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_CDF2RDF_HPP_INCLUDED

#include <nt2/linalg/functions/cdf2rdf.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/of_size.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( cdf2rdf_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& ) const
    {
      BOOST_ASSERT_MSG(is_real(a0), "diagonal is not valid");
      return real(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cdf2rdf_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::cdf2rdf_
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
    /// INTERNAL ONLY - [v, w] = cdf2rdf(cv, cw)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
       auto& cv = boost::proto::child_c<0>(a0);
       auto& cw = boost::proto::child_c<1>(a0);
       auto i = find(imag(diag_of(cw)));
       container::table<std::size_t> index =
         cast<std::size_t>(i(_(std::size_t(1), std::size_t(2), length(i))));
       if (isempty(index))
       {
         boost::proto::child_c<0>(a1) = real(cv);
         boost::proto::child_c<1>(a1) = real(cw);
         return;
       }
       container::table<ctype_t> ct = eye(length(cw), meta::as_<ctype_t>());
       container::table<ctype_t> twobytwo = cons<ctype_t>(of_size(2, 2), One<ctype_t>()
                                                         , I<ctype_t>(), One<ctype_t>()
                                                         , -I<ctype_t>());
       auto i2 = _(std::size_t(0), std::size_t(1));
       for(auto j : index)
       {
         ct(i2+j, i2+j) = twobytwo;
       }
       boost::proto::child_c<0>(a1) = trans(real(linsolve(ctrans(ct), ctrans(cv))));
       boost::proto::child_c<1>(a1) = real(mtimes(ct, ctrans(linsolve(ctrans(ct), ctrans(cw)))));
    }



  };
} }

#endif


