//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_MODEL_ALIGNED_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_MODEL_ALIGNED_ARRAY_HPP_INCLUDED

#include <boost/simd/forward/aligned_array.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY value_of for container const refere,ce
  template<class T, std::size_t N, std::size_t A>
  struct  value_of< boost::simd::aligned_array<T,N,A> >
        : value_of<T>
  {};

  /// INTERNAL ONLY model_of for container
  template<class T, std::size_t N, std::size_t A>
  struct model_of< boost::simd::aligned_array<T,N,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef boost::simd::aligned_array<X,N,A>              type;
      };
    };
  };
} } }

#endif
