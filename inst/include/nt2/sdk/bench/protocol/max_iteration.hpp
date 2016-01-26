//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_MAX_ITERATION_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_MAX_ITERATION_HPP_INCLUDED

#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol.hpp>

namespace nt2 { namespace bench
{
  /*!

  **/
  template< typename Experiment, typename... Metrics>
  struct max_iteration : protocol<Metrics...>
  {
    typedef protocol<Metrics...> parent;

    max_iteration( std::size_t i, Metrics const&... m )
                : parent(m...), iteration_(i)
    {}

    inline void run() { run(fixed(0)); }

    template<typename Workbench> inline void run(Workbench w)
    {
      do
      {
        details::times_set  times_;
        details::cycles_set cycles_;

        Experiment e(w());

        for(std::size_t i=0;i<iteration_;++i)
        {
          parent::run(e,times_,cycles_);
        }

        parent::display(e,times_,cycles_);
        w.step();

      } while(!w.done());
    }

    private:
    std::size_t iteration_;
  };

  /*!

  **/
  template< typename Experiment, typename... Metrics>
  void run_over( std::size_t iteration, Metrics const&... m)
  {
    max_iteration<Experiment,Metrics...> that(iteration,m...);
    that.run();
  }

  /*!

  **/
  template< typename Experiment, typename Workbench, typename... Metrics>
  void run_over_with(std::size_t iteration, Workbench const& w, Metrics const&... m)
  {
    max_iteration<Experiment,Metrics...> that(iteration,m...);
    that.run(w);
  }
} }

#endif
