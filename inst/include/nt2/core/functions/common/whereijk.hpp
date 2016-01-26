//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_WHEREIJK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_WHEREIJK_HPP_INCLUDED

#include <nt2/core/functions/whereijk.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_ < A0, nt2::tag::whereijk_
                                      , N, nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_<unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                                   result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename result_of::as_subscript<_3D,i_t>::type           s_t;

      s_t pos  = as_subscript(_3D(a0.extent()),enumerate<i_t>(p));

      return if_else( boost::proto::value(boost::proto::child_c<0>(a0))(pos[0],pos[1],pos[2])
                    , nt2::run(boost::proto::child_c<1>(a0), p, t)
                    , nt2::run(boost::proto::child_c<2>(a0), p, t)
                    );
    }
  };
} }

#endif
