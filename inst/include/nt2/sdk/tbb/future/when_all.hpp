//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_WHEN_ALL_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_WHEN_ALL_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <nt2/sdk/shared_memory/future.hpp>

#include <nt2/sdk/tbb/future/details/tbb_future.hpp>
#include <nt2/sdk/tbb/future/details/empty_body.hpp>

#include <cstdio>
#include <initializer_list>

namespace nt2
{

  namespace details
  {
    struct empty_functor
    {
      typedef int result_type;

      int operator()() const
      {
        return 0;
      }
    };


    template <class Future, typename Node_raw, typename A>
    static void link_node(Future & f, Node_raw & c, A & a)
    {
      tbb::flow::make_edge( *(a.node_)
                          , *c
                          );
      f.attach_previous_future( a );
    }
  }

  template<class Site>
  struct when_all_impl< tag::tbb_<Site> >
  {
    typedef typename tbb::flow::continue_node<
    tbb::flow::continue_msg> node_type;

    typedef typename details::tbb_future<int>
    whenall_future;

    template <typename Future>
    whenall_future static call( std::vector<Future> & lazy_values )
    {
      whenall_future future_res;

      node_type * c = new node_type( *(future_res.getWork()),
        details::tbb_task_wrapper<details::empty_functor,whenall_future>
        (details::empty_functor()
        ,whenall_future(future_res)
        )
        );

      future_res.getTaskQueue()->push_back(c);

      for (std::size_t i=0; i<lazy_values.size(); i++)
      {
        future_res.attach_previous_future(lazy_values[i]);
        tbb::flow::make_edge(*(lazy_values[i].node_),*c);
      }

      future_res.attach_task(c);
      return future_res;
    }

    template< typename ... A >
    whenall_future static call( details::tbb_future<A> & ...a )
    {
      whenall_future future_res;

      node_type * c = new node_type( *future_res.getWork(),
        details::tbb_task_wrapper<details::empty_functor,whenall_future>
        ( details::empty_functor()
        , whenall_future(future_res)
        )
        );

      future_res.getTaskQueue()->push_back(c);
      future_res.attach_task(c);

      // Some trick to call link_node multiple times
      return (void)std::initializer_list<int>
      { ( static_cast<void>( details::link_node(future_res, c, a) )
        , 0
        )...
      }
      , future_res;
    }
  };
}

#endif
#endif
