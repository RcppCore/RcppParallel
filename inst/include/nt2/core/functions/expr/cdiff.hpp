//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CDIFF_HPP_INCLUDED

#include <nt2/core/functions/cdiff.hpp>
#include <nt2/core/functions/common/cdiff.hpp>

#include <nt2/memory/functions/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( cdiff_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cdiff_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return boost::proto::make_expr< nt2::tag::cdiff_
                                    , container::domain
                                    >
                                    ( boost::cref(a0)
                                    , nt2::firstnonsingleton(a0)-1
                                    );
    }
  };

  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( cdiff_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cdiff_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1 ) const
    {
      return boost::proto::make_expr< nt2::tag::cdiff_
                                    , container::domain
                                    >
                                    ( boost::cref(a0)
                                    , std::size_t(a1-1)
                                    );
    }
  };
} }

#endif
