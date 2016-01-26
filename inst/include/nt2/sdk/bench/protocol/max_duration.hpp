//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_MAX_DURATION_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_MAX_DURATION_HPP_INCLUDED

#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol.hpp>

namespace nt2 { namespace bench
{
  /*!

  **/
  template< typename Experiment, typename... Metrics>
  struct max_duration : protocol<Metrics...>
  {
    typedef protocol<Metrics...> parent;

    max_duration( double d, Metrics const&... m )
                : parent(m...), duration_(d)
    {}

    inline void run() { run(fixed(0)); }

    template<typename Workbench> inline void run(Workbench w)
    {
      time_quantum_t const total_duration( to_timequantums(duration_*1000000) );

      do
      {
        time_quantum_t       duration(0);
        details::times_set  times_;
        details::cycles_set cycles_;

        Experiment e(w());

        do
        {
          duration += parent::run(e,times_,cycles_);
        } while( duration < total_duration );

        parent::display(e,times_,cycles_);
        w.step();

      } while(!w.done());
    }

    private:
    double  duration_;
  };

  /*!

  **/
  template< typename Experiment, typename... Metrics>
  void run_during ( double duration, Metrics const&... m)
  {
    max_duration<Experiment,Metrics...> that(duration,m...);
    that.run();
  }

  /*!

  **/
  template< typename Experiment, typename Workbench, typename... Metrics>
  void run_during_with(double duration, Workbench const& w, Metrics const&... m)
  {
    max_duration<Experiment,Metrics...> that(duration,m...);
    that.run(w);
  }
} }

#endif
