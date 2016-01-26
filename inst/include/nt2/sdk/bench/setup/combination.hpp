//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_COMBINATION_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_COMBINATION_HPP_INCLUDED

#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace bench
{
  /*!
    @brief Setup combinator

    Gather a variable amount of Setup into a single conglomerate that returns
    a Fusion Sequence of each of its components step when required, update
    their state synchronously and is defined as done as soon as one of its
    component is done.

    @tparam Data Types of Setup used in the combination
  **/
  template<typename... Data>
  struct combination_
  {
    typedef boost::fusion::vector<Data...>  data_type;

    struct do_value
    {
      template<typename Sig> struct result;

      template<typename This, typename T>
      struct result<This(T)>
      {
        typedef typename boost::dispatch::meta
                                        ::strip<T>::type::result_type type;
      };

      template<typename T>
      BOOST_FORCEINLINE
      typename result<do_value(T&)>::type operator()(T& t) const
      {
        return t();
      }
    };

    typedef decltype ( boost::fusion::
                       transform(std::declval<data_type>(),do_value())
                     )                                     result_type;

    BOOST_FORCEINLINE combination_ ( Data const&... d) : steps_(d...) {}

    BOOST_FORCEINLINE result_type  operator()() const
    {
      return boost::fusion::transform(steps_,do_value());
    }

    struct do_step
    {
      template<typename T>
      BOOST_FORCEINLINE void operator()(T& t) const { t.step(); }
    };

    BOOST_FORCEINLINE void step()
    {
      boost::fusion::for_each(steps_, do_step());
    }

    struct do_done
    {
      typedef bool result_type;

      template<typename T>
      BOOST_FORCEINLINE bool operator()(bool s, const T& t) const
      {
        return s || t.done();
      }
    };

    BOOST_FORCEINLINE bool done() const
    {
      return boost::fusion::fold(steps_,false, do_done());
    }

    data_type steps_;
  };

  /*!
    @brief Combination setup generator

    Generate a combination setup object from a set of other Setups.

    @param d Setups to agglomerate

    @return a combination_ object containing copies of d
  **/
  template<typename... Data>
  BOOST_FORCEINLINE combination_<Data...> and_(Data const&... a)
  {
    return combination_<Data...>(a...);
  }
} }

#endif
