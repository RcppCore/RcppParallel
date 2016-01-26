//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_EVALUATE_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_EVALUATE_HPP_INCLUDED

#include <boost/simd/dsl/functions/evaluate.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*! \brief Same as \classref{boost::simd::tag::evaluate_} **/
    struct evaluate_ : boost::simd::tag::evaluate_
    {
      typedef boost::simd::tag::evaluate_ parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evaluate_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::evaluate_, Site> dispatching_evaluate_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::evaluate_, Site>();
    }
    template<class... Args>
    struct impl_evaluate_;
  }

  /*! \brief Same as \funcref{boost::simd::evaluate} **/
  template<class A0, class... Args>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE evaluate(A0&& a0, Args&&... args)
  BOOST_AUTO_DECLTYPE_BODY( dispatching_evaluate_( ext::adl_helper(), boost::dispatch::default_site_t<A0>(), boost::dispatch::meta::hierarchy_of_t<A0&&>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()... )(static_cast<A0&&>(a0), static_cast<Args&&>(args)...) )
}

#endif
