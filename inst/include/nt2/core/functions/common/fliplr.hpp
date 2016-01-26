//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FLIPLR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FLIPLR_HPP_INCLUDED

#include <nt2/core/functions/fliplr.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_ < A0, nt2::tag::fliplr_
                                      , N, nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                     result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type         sub_t;

      // Retrieve 2D position from the linear index
      _2D ex = a0.extent();
      sub_t pos = as_subscript(ex, nt2::enumerate<i_t>(p));

      // Compute the flipped start of the enumeration
      pos[1] = dec(width(a0)-pos[1]);

      return nt2::run(boost::proto::child_c<0>(a0),as_index(ex,pos),t);
    }
  };
} }

#endif
