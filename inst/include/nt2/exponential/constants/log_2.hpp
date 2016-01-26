//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_LOG_2_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_LOG_2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Log_2 generic tag

      Represents the Log_2 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log_2, double
                                , 0, 0x3f317218UL
                                , 0x3fe62e42fefa39efULL
                                )
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::Log_2, Site> dispatching_Log_2(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::Log_2, Site>();
    }
    template<class... Args>
    struct impl_Log_2;
  }
 /*!
    Generates constant Log_2. (\f$\log(2)\f$)

    @par Semantic:

    @code
    T r = Log_2<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.6931471805599453094172321214581765680755001343602553);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2, Log_2);
}

#endif
