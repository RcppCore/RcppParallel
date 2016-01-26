  //==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISINSIDE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISINSIDE_HPP_INCLUDED

#include <nt2/predicates/functions/isinside.hpp>
#include <boost/fusion/adapted/mpl.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( isinside_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::strip<A1>::type                          base_t;
    typedef typename base_t::extent_type                            ext_t;
    typedef typename  meta::call
                      < nt2::tag::isinside_(A0&,ext_t)>::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0,const A1& a1) const
    {
      return isinside(a0,a1.extent());
    }
  };

} }

#endif
