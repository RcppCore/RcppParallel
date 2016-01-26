//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::cat_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&             result_type;

    result_type operator()(A0& out, const A1& in) const
    {
      container::table<typename A0::value_type> r( in.extent() );

      if(numel(boost::proto::child_c<1>(in)))
      {
        if(numel(boost::proto::child_c<2>(in)))
        {
          std::size_t d = boost::proto::child_c<0>(in);
          std::size_t l = size(boost::proto::child_c<1>(in),d);
          std::size_t n = size(r,d);

          along(r,_(1,l) , d) = boost::proto::child_c<1>(in);
          along(r,_(l+1,n),d) = boost::proto::child_c<2>(in);
        }
        else
        {
          r = boost::proto::child_c<1>(in);
        }
      }
      else
      {
        r = boost::proto::child_c<2>(in);
      }

      container::assign_swap(out, r);

      return out;
    }
  };
} }

#endif
