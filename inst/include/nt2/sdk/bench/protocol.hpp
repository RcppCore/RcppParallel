//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_HPP_INCLUDED

#include <nt2/sdk/bench/details/display_metric.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/vector.hpp>

namespace nt2 { namespace details
{
  template<class Experiment, class Enable = void>
  struct experiment_copy
  {
    typedef Experiment type;
  };

  template<class Experiment>
  struct experiment_copy<Experiment, typename Experiment::experiment_is_immutable>
  {
    typedef Experiment& type;
  };
} }

namespace nt2 { namespace bench
{
  /*!

  **/
  template<typename... Metrics>
  struct protocol
  {
    typedef boost::fusion::vector<Metrics...> metrics_type;

    protocol() {}
    protocol(Metrics const&... m) : metrics_(m...) {}

    template<typename Experiment>
    inline time_quantum_t run ( Experiment& e
                              , details::times_set&  t
                              , details::cycles_set& c
                              ) const
    {
      // We copy reference experiment depending on whether they have
      // experiment_is_immutable or not
      typename details::experiment_copy<Experiment>::type local(e);

      time_quantum_t const time_start  ( time_quantum() );
      cycles_t       const cycles_start( read_cycles() );

      local();

      cycles_t       const cycles_end( read_cycles() );
      time_quantum_t const time_end  ( time_quantum() );

      cycles_t       const burned_cycles( cycles_end - cycles_start );
      time_quantum_t const elapsed_time ( time_end   - time_start   );

      t(to_microseconds(elapsed_time));
      c(burned_cycles);

      return elapsed_time;
    }

    template<typename Experiment>
    inline void display ( Experiment& e
                        , details::times_set&  t, details::cycles_set& c
                        ) const
    {
      boost::fusion::for_each ( metrics_
                              , details::display_metric<Experiment>(e,t,c)
                              );
    }

    protected:
    metrics_type  metrics_;
  };
} }

#endif
