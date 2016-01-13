//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SHUFFLE_HPP_INCLUDED

#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/swar/functions/details/shuffler.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( shuffle_, tag::cpu_
                          , (A0)(P)
                          , ((ast_<A0, boost::simd::domain>))
                            (target_< unspecified_<P> >)
                          )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,P const&) const
    {
      return ::boost::simd::shuffle<typename P::type>(evaluate(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT( shuffle_, tag::cpu_
                          , (A0)(A1)(P)
                          , ((ast_<A0, boost::simd::domain>))
                            ((ast_<A1, boost::simd::domain>))
                            (target_< unspecified_<P> >)
                          )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1,P const&) const
    {
      return ::boost::simd::shuffle<typename P::type>(evaluate(a0),evaluate(a1));
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( shuffle_
                                    , boost::simd::tag::cpu_
                                    , (A0)(X)(P)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,P const&) const
    {
      typename P::type p;
      return details::shuffler< details::default_matcher
                              , details::default_permutation
                                                <meta::cardinal_of<A0>::value>
                              , meta::cardinal_of<A0>::value
                              , 4
                              >::process(a0,p);
    }
  };

  BOOST_DISPATCH_IMPLEMENT_IF         ( shuffle_, tag::cpu_
                                      , (A0)(X)(P)
                                      , ( mpl::equal_to < mpl::sizeof_<A0>
                                                        , mpl::sizeof_<typename A0::type>
                                                        >
                                        )
                                      , ((simd_< logical_<A0>, X>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, P const&) const
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return  bitwise_cast <result_type>
              ( shuffle<typename P::type>( bitwise_cast<type>(a0) ));
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( shuffle_
                                    , boost::simd::tag::cpu_
                                    , (A0)(X)(P)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>,X>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0  result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A0 const& a1,P const&) const
    {
      typename P::type p;
      return details::shuffler< details::default_matcher
                              , details::default_permutation
                                                <meta::cardinal_of<A0>::value>
                              , meta::cardinal_of<A0>::value
                              , 4
                              >::process(a0,a1,p);
    }
  };

  BOOST_DISPATCH_IMPLEMENT_IF         ( shuffle_, tag::cpu_
                                      , (A0)(X)(P)
                                      , ( mpl::equal_to < mpl::sizeof_<A0>
                                                        , mpl::sizeof_<typename A0::type>
                                                        >
                                        )
                                      , ((simd_< logical_<A0>, X>))
                                        ((simd_< logical_<A0>, X>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                        result_type;
    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return bitwise_cast <result_type>
                          ( shuffle<typename P::type> ( bitwise_cast<type>(a0)
                                                      , bitwise_cast<type>(a1)
                                                      )
                          );
    }
  };
} } }

#endif
