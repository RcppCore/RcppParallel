//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>
#include <nt2/include/functions/arecatcompatible.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates cat from 2 expressions
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cat_, tag::cpu_,
                              (Dimension)(A1)(A2),
                              (scalar_<integer_<Dimension> >)
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cat_
                                          , container::domain
                                          , std::size_t
                                          , A1 const&
                                          , A2 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(Dimension const& dim,A1 const& a1,A2 const& a2) const
    {
       BOOST_ASSERT_MSG ( arecatcompatible(a1, a2, dim)
                        , "cat arguments dimensions are not consistent."
                        );

      return  boost::proto::make_expr < nt2::tag::cat_
                                      , container::domain
                                      >
                                      ( std::size_t(dim)
                                      , boost::cref(a1)
                                      , boost::cref(a2)
                                      );
    }
  };

  //============================================================================
  // Generates cat from expression/scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cat_, tag::cpu_,
                              (Dimension)(A1)(A2),
                              (scalar_<integer_<Dimension> >)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cat_
                                          , container::domain
                                          , std::size_t
                                          , A1 const&
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(Dimension const& dim,A1 const& a1,A2 const& a2) const
    {
       BOOST_ASSERT_MSG ( arecatcompatible(a1, a2, dim)
                        , "cat arguments dimensions are not consistent."
                        );

      return  boost::proto::make_expr < nt2::tag::cat_
                                      , container::domain
                                      >
                                      ( std::size_t(dim)
                                      , boost::cref(a1)
                                      , a2
                                      );
    }
  };


  //============================================================================
  // Generates cat from expression/scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cat_, tag::cpu_,
                              (Dimension)(A1)(A2),
                              (scalar_<integer_<Dimension> >)
                              (scalar_< unspecified_<A1> >)
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cat_
                                          , container::domain
                                          , std::size_t
                                          , A1
                                          , A2 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(Dimension const& dim,A1 const& a1,A2 const& a2) const
    {
       BOOST_ASSERT_MSG ( arecatcompatible(a1, a2, dim)
                        , "cat arguments dimensions are not consistent."
                        );

      return  boost::proto::make_expr < nt2::tag::cat_
                                      , container::domain
                                      >
                                      ( std::size_t(dim)
                                      , a1
                                      , boost::cref(a2)
                                      );
    }
  };
} }

#endif
