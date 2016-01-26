//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_DETAILS_TBB_FUTURE_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_DETAILS_TBB_FUTURE_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <vector>
#include <cstdio>
#include <memory>
#include <type_traits>

#include <nt2/sdk/tbb/future/details/tbb_task_wrapper.hpp>
#include <nt2/sdk/tbb/future/details/empty_body.hpp>

namespace nt2
{
  namespace tag
  {
    template<class T> struct tbb_;
  }

  namespace details
  {
    class tbb_future_base
    {
    protected:

      tbb_future_base () {}
      ~tbb_future_base () {}

    public:

      static tbb::flow::graph *
      getWork ()
      {
        if(NULL == nt2_graph_)
        {
          nt2_graph_ = new tbb::flow::graph;
        }
        return nt2_graph_;
      }

      static tbb::flow::continue_node<tbb::flow::continue_msg> *
      getStart ()
      {
        if (NULL == start_task_)
        {
          start_task_ =
          new tbb::flow::continue_node
          <tbb::flow::continue_msg>
          (*getWork(), details::empty_body());
        }
        return (start_task_);
      }

      static std::vector<
      tbb::flow::continue_node< tbb::flow::continue_msg> *
      > *
      getTaskQueue ()
      {
        if (NULL == task_queue_)
        {
          task_queue_ = new std::vector<
          tbb::flow::continue_node<tbb::flow::continue_msg> *
          >;

          task_queue_->reserve(1000);
        }
        return task_queue_;
      }

      static void kill_graph ()
      {
        if (NULL != nt2_graph_)
        {
          delete nt2_graph_;
          nt2_graph_ = NULL;
        }

        if (NULL != start_task_)
        {
          delete start_task_;
          start_task_ = NULL;
        }

        if (NULL != task_queue_)
        {
          for (std::size_t i =0; i<task_queue_->size(); i++)
          {
            delete( (*task_queue_)[i] );
          }

          delete task_queue_;
          task_queue_ = NULL;
        }
      }

    private:

// static members
      static tbb::flow::graph *
      nt2_graph_;

      static tbb::flow::continue_node<tbb::flow::continue_msg> *
      start_task_;

      static std::vector<
      tbb::flow::continue_node<tbb::flow::continue_msg> *
      > *
      task_queue_;
    };

    tbb::flow::graph *
    tbb_future_base::nt2_graph_ = NULL;

    tbb::flow::continue_node<tbb::flow::continue_msg> *
    tbb_future_base::start_task_ = NULL;

    std::vector<
    tbb::flow::continue_node<tbb::flow::continue_msg> *
    > *
    tbb_future_base::task_queue_ = NULL;

    template<typename result_type>
    struct tbb_future : public tbb_future_base
    {
      typedef typename tbb::flow::continue_node<
      tbb::flow::continue_msg> node_type;

      tbb_future()
      : node_(NULL),res_(new result_type),ready_(new bool(false))
      {}

      bool is_ready()
      {
        return *ready_;
      }

      void wait()
      {
        getStart()->try_put(tbb::flow::continue_msg());
        getWork()->wait_for_all();
        kill_graph();
      }

      result_type get()
      {
        if(!is_ready())
        {
          wait();
        }
        return *res_;
      }

      template<typename F>
      details::tbb_future<
      typename std::result_of<F(tbb_future)>::type
      >
      then(F&& f)
      {
        typedef typename std::result_of<F(tbb_future)>::type
        then_result_type;

        typedef typename details::tbb_future<then_result_type>
        then_future_type;

        then_future_type then_future;

        then_future.attach_previous_future(*this);

        node_type * c
        = new node_type
        ( *getWork(),
          details::tbb_task_wrapper<
          F,
          then_future_type,
          tbb_future
          >
          (std::forward<F>(f)
            ,then_future_type(then_future)
            ,tbb_future(*this) )
          );

        tbb::flow::make_edge(*node_,*c);

        getTaskQueue()->push_back(c);
        then_future.attach_task(c);

        return then_future;
      }

      template< typename previous_future>
      void attach_previous_future(previous_future const & pfuture)
      {
        pfutures_.push_back(
          std::shared_ptr<previous_future>(
            new previous_future(pfuture)
            )
          );
      }


      void attach_task(node_type * node)
      {
        node_ = node;
      }

// own members
      node_type * node_;
      std::vector< std::shared_ptr<void> > pfutures_;
      std::shared_ptr<result_type> res_;
      std::shared_ptr<bool> ready_;
    };
  }
}

#endif
#endif
