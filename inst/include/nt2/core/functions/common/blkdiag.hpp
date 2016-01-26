//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/extremum/extremum.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::blkdiag_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&             result_type;

    result_type operator()(A0& out, const A1& in) const
    {
      container::table<typename A0::value_type> r;

      if(numel(boost::proto::child_c<0>(in)))
      {
        if(numel(boost::proto::child_c<1>(in)))
        {
          r = zeros( in.extent(), meta::as_<typename A0::value_type>() );
          std::size_t s1 = size(boost::proto::child_c<0>(in),1)
                    , s2 = size(boost::proto::child_c<0>(in),2);

          r(_(1u  , s1  ) , _(1u  , s2  ) ) = boost::proto::child_c<0>(in);
          r(_(s1+1, end_) , _(s2+1, end_) ) = boost::proto::child_c<1>(in);
        }
        else
        {
          r = boost::proto::child_c<0>(in);
        }
      }
      else
      {
        r = boost::proto::child_c<1>(in);
      }

      container::assign_swap(out, r);

      return out;
    }
  };
} }

#endif
