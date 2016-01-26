//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED

#include <nt2/core/functions/numel.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/advance.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/empty.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/simd/operator/functions/scalar/multiplies.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( numel_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  BOOST_DISPATCH_IMPLEMENT  ( numel_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (mpl_integral_< scalar_< unspecified_<A1> > >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&, const A1&) const { return result_type(); }
  };

  BOOST_DISPATCH_IMPLEMENT  ( numel_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    // multiplies functor
    typedef typename boost::dispatch::
            make_functor<boost::simd::tag::multiplies_, A0>::type     func_t;
    using seq_t = typename boost::dispatch::meta::strip<A0>::type;
    using result_type = decltype(boost::fusion::fold( std::declval<seq_t>()
                                , boost::mpl::integral_c<std::size_t,1>()
                                , func_t()
                                ));

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0) const
    {
      return boost::fusion::fold( a0
                                , boost::mpl::integral_c<std::size_t,1>()
                                , func_t()
                                );
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( numel_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (mpl_integral_< scalar_< unspecified_<A1> > >)
                            )
  {
    typedef typename boost::dispatch::
            make_functor<boost::simd::tag::multiplies_, A0>::type  func_t;

    typedef typename boost::fusion::result_of::begin<A0>::type  begin_t;
    typedef typename boost::fusion::result_of::end<A0>::type    end_t;
    typedef typename boost::fusion::result_of::
                            advance<begin_t, A1>::type          new_begin_t;
    typedef boost::fusion::iterator_range<new_begin_t, end_t>   it_t;

    typedef typename  boost::fusion::result_of::
                      value_at<A0, boost::mpl::int_<0> >::type  first_t;

    typedef typename  boost::fusion::result_of
                           ::fold< it_t const
                                 , boost::mpl::integral_c<std::size_t,1> const
                                 , func_t
                                 >::type                      result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, const A1&) const
    {
      return boost::fusion::fold( it_t(new_begin_t(a0), end_t(a0))
                                , boost::mpl::integral_c<std::size_t,1>()
                                , func_t()
                                );
    }
  };
} }

#endif

