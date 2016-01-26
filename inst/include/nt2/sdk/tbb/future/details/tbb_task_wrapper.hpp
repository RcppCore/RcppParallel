//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_DETAILS_TBB_TASK_WRAPPER_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_DETAILS_TBB_TASK_WRAPPER_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <tuple>

namespace nt2
{
  namespace details
  {

    template<int ... Indices>
    struct tbb_sequence{
      template<class F, typename ... A>
      typename std::result_of<F(A...)>::type
      apply(F& f, std::tuple<A...> & tuple)
      {
        return f( std::get<Indices>(tuple)... );
      }
    };

    template<int N, int ...S>
    struct generate_tbb_sequence
    : generate_tbb_sequence<N-1, N-1, S...> { };

    template<int ...S>
    struct generate_tbb_sequence<0, S...> {
      typedef tbb_sequence<S...> type;
    };

    template< class F, typename future_type, typename ... A>
    struct tbb_task_wrapper
    {
      typedef typename generate_tbb_sequence<sizeof...(A)>::type seq;

      tbb_task_wrapper( F && f, future_type && future_result, A&& ... a)
      : f_(std::forward<F>(f))
      , future_result_(std::forward<future_type>(future_result))
      , a_( std::make_tuple(std::forward<A>(a) ...) )
      {}

      void operator()(const tbb::flow::continue_msg )
      {
        *(future_result_.res_) = seq().apply(f_,a_);
        *(future_result_.ready_) = true;
      }

      F f_;
      future_type future_result_;
      std::tuple < A ... > a_;
    };
  }
}

#endif
#endif
