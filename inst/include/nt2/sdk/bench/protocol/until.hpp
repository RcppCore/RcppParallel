//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_UNTIL_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_UNTIL_HPP_INCLUDED

#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol.hpp>

namespace nt2 { namespace bench
{
  template<typename Experiment, typename... Metrics>
  struct until_ : protocol<Metrics...>
  {
    typedef protocol<Metrics...>            parent;

    until_( double d, std::size_t i, Metrics const&... m )
          : parent(m...), duration_(d), iteration_(i)
    {}

    inline void run() { run(fixed(0)); }

    template<typename Workbench> inline void run(Workbench w)
    {
      time_quantum_t const total_duration( to_timequantums(duration_*1000000) );

      do
      {
        std::size_t         iter(0);
        time_quantum_t      duration(0);
        details::times_set  times_;
        details::cycles_set cycles_;

        Experiment e(w());

        do
        {
          duration += parent::run(e,times_,cycles_);
          iter++;
        } while( duration < total_duration && iter < iteration_ );

        parent::display(e,times_,cycles_);
        w.step();

      } while(!w.done());
    }

    private:
    double      duration_;
    std::size_t iteration_;
  };

  /*!

  **/
  template< typename Experiment, typename... Metrics>
  void run_until(double duration, std::size_t iteration, Metrics const&... m)
  {
    until_<Experiment,Metrics...> that(duration, iteration, m...);
    that.run();
  }

  /*!

  **/
  template< typename Experiment, typename Workbench, typename... Metrics>
  void run_until_with ( double duration, std::size_t iteration
                      , Workbench const& w, Metrics const&... m
                      )
  {
    until_<Experiment,Metrics...> that(duration, iteration, m...);
    that.run(w);
  }
} }

#endif
