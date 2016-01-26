//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_RUN_HPP_INCLUDED

#include <boost/simd/dsl/functions/run.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*! \brief Same as \classref{boost::simd::tag::run_} **/
    struct run_ : boost::simd::tag::run_
    {
      typedef boost::simd::tag::run_ parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_run_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /*! \brief Same as \classref{boost::simd::tag::run_assign_} **/
    struct run_assign_ : boost::simd::tag::run_assign_
    {
      typedef boost::simd::tag::run_ parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_run_assign_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::run_, Site> dispatching_run_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::run_, Site>();
    }
    template<class... Args>
    struct impl_run_;

    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::run_assign_, Site> dispatching_run_assign_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::run_assign_, Site>();
    }
    template<class... Args>
    struct impl_run_assign_;
  }

  /*! \brief Same as \funcref{boost::simd::run} **/
  template<class A0, class... Args>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE run(A0&& a0, Args&&... args)
  BOOST_AUTO_DECLTYPE_BODY( dispatching_run_( ext::adl_helper(), boost::dispatch::default_site_t<A0>(), boost::dispatch::meta::hierarchy_of_t<A0&&>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()... )(static_cast<A0&&>(a0), static_cast<Args&&>(args)...) )

  /*! \brief Same as \funcref{boost::simd::run} **/
  template<class A0, class... Args>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE run_assign(A0&& a0, Args&&... args)
  BOOST_AUTO_DECLTYPE_BODY( dispatching_run_assign_( ext::adl_helper(), boost::dispatch::default_site_t<A0>(), boost::dispatch::meta::hierarchy_of_t<A0&&>(), boost::dispatch::meta::hierarchy_of_t<Args&&>()... )(static_cast<A0&&>(a0), static_cast<Args&&>(args)...) )
}

#endif
