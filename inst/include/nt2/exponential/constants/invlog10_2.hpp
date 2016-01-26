//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_INVLOG10_2_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_INVLOG10_2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief invlog10_2 generic tag

      Represents the invlog10_2 constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Invlog10_2, double
                                , 0, 0x40549a78UL
                                , 0x400a934f0979a372ULL
                                )
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::Invlog10_2, Site> dispatching_Invlog10_2(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::Invlog10_2, Site>();
    }
    template<class... Args>
    struct impl_Invlog10_2;
  }
 /*!
    Generates constant  1/log10(2).

    @par Semantic:

    @code
    T r = invlog10_2<T>();
    @endcode


    is similar to:

    @code
    T r =  T(3.321928094887362e+00);
    @endcode
 **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invlog10_2, Invlog10_2);
}

#endif
