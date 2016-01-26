//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_POWLARGELIM_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_POWLARGELIM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief powlargelim generic tag

      Represents the powlargelim constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Powlargelim, double
                                , 0, 0x44ffe000 //2047
                                , 0x40cfff8000000000ULL //16383
                                )
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::Powlargelim, Site> dispatching_Powlargelim(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::Powlargelim, Site>();
    }
    template<class... Args>
    struct impl_Powlargelim;
  }
 /*!
    Generates constant powlargelim

    @par Semantic:

    @code
    T r = powlargelim<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Powlargelim, Powlargelim);
}

#endif
