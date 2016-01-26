//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRI1U_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRI1U_HPP_INCLUDED

#include <nt2/core/functions/tri1u.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_< A0, nt2::tag::tri1u_
                                     , boost::mpl::long_<1>
                                     , nt2::container::domain
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type     result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type        i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type   s_t;

      // Retrieve 2D position from the linear index
      s_t pos = as_subscript(_2D(a0.extent()),nt2::enumerate<i_t>(p));

      // Return the upper triangular section with 1 on the diagonal
      return nt2::if_else ( nt2::eq(pos[0], pos[1])
                          , One<result_type>()
                          , nt2::if_else_zero ( nt2::lt(pos[0], pos[1])
                                              , nt2::run
                                                ( boost::proto::child_c<0>(a0)
                                                  , p
                                                  , t
                                                )
                                              )
                          );
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_< A0, nt2::tag::tri1u_
                                     , boost::mpl::long_<2>
                                     , nt2::container::domain
                                     >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type     result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type        i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type   s_t;
      typedef typename nt2::meta::as_signed<typename s_t::value_type>::type p_t;

      // Retrieve the diagonal offset
      std::ptrdiff_t o = boost::proto::value(boost::proto::child_c<1>(a0));

      // Retrieve 2D position from the linear index
      s_t pos = as_subscript(_2D(a0.extent()),nt2::enumerate<i_t>(p));

      p_t const is  = bitwise_cast<p_t>(pos[0]);
      p_t const js  = bitwise_cast<p_t>(pos[1]) - splat<p_t>(o);

      // Return the shifted upper triangular section with 1 on the diagonal
      return nt2::if_else ( nt2::eq(is, js)
                          , One<result_type>()
                          , nt2::if_else_zero ( nt2::lt(is, js)
                                              , nt2::run
                                                ( boost::proto::child_c<0>(a0)
                                                  , p
                                                  , t
                                                )
                                              )
                          );
    }
  };
} }

#endif
