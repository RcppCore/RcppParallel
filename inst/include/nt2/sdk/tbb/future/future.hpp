//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_FUTURE_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_FUTURE_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <vector>
#include <cstdio>
#include <memory>
#include <type_traits>
#include <utility>

#include <nt2/sdk/shared_memory/future.hpp>
#include <nt2/sdk/tbb/future/details/tbb_future.hpp>
#include <nt2/sdk/tbb/future/details/tbb_task_wrapper.hpp>

namespace nt2
{
  namespace tag
  {
    template<class T> struct tbb_;
  }

  template<class Site, class result_type>
  struct make_future<tag::tbb_<Site> , result_type>
  {
    typedef details::tbb_future<result_type> type;
  };

  template< class Site, class result_type>
  struct make_ready_future_impl< tag::tbb_<Site>, result_type>
  {
    inline details::tbb_future<result_type>
    call(result_type && value)
    {
      details::tbb_future<result_type> future_res;
      future_res.res_ =
      std::make_shared<result_type>
      ( std::forward<result_type>(value) );

      *(future_res.ready_) = true;

      future_res.attach_task(future_res.getStart());

      return future_res;
    }
  };

  template<class Site>
  struct async_impl< tag::tbb_<Site> >
  {
    typedef typename
    tbb::flow::continue_node<tbb::flow::continue_msg> node_type;

    template< typename F , typename ... A>
    inline typename make_future< tag::tbb_<Site>
                               , typename std::result_of< F(A...)>::type
                               >::type
    call(F&& f, A&& ... a)
    {
      typedef typename std::result_of< F(A...)>::type result_type;
      typedef typename details::tbb_future<result_type> async_future;

      async_future future_res;

      node_type * node =
      new node_type( *future_res.getWork()
        , details::tbb_task_wrapper< F, async_future, A ... >
          ( std::forward<F>(f)
          , async_future(future_res)
          , std::forward<A>(a)...
          )
        );

      tbb::flow::make_edge( *(future_res.getStart()), *(node) );

      future_res.getTaskQueue()->push_back(node);
      future_res.attach_task(node);

      return future_res;
    }

  };

}

#endif
#endif
