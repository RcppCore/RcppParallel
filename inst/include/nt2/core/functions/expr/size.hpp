//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SIZE_HPP_INCLUDED

#include <nt2/core/functions/size.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( size_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::call<tag::extent_(A0)>::type base;
    typedef typename meta::strip<base>::type            ext_t;

    static const std::size_t len = ext_t::static_size;
    static const std::size_t olen = len > 2 ? len : 2;

    typedef container::table< typename ext_t::value_type
                            , settings(automatic_, of_size_<1, olen>)
                            >                           result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      result_type that;
      typename ext_t::value_type i=1;

      for(; i<len+1; ++i)
        that(i) = nt2::extent(a0)[i-1];

      for(; i<olen+1; ++i)
        that(i) = typename ext_t::value_type(1);

      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( size_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0,const A1& a1) const
    {
      std::size_t nb_dims   = nt2::extent(a0).size();
      return  std::size_t(a1-1) < nb_dims
            ? std::size_t(nt2::extent(a0)[a1-1])
            : std::size_t(1);
    }
  };
} }

#endif
