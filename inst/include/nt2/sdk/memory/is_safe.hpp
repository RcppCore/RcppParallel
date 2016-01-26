//==============================================================================
//         Copyright 2009 - 2014 LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_IS_SAFE_HPP_INCLUDED
#define NT2_SDK_MEMORY_IS_SAFE_HPP_INCLUDED

#include <boost/simd/include/functions/maximum.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <cstddef>

namespace nt2
{
  namespace details
  {
    // Retrieve the biggest valid index when reading a SIMD vector
    template<typename T, typename A0> std::size_t maxpos(A0 const& a0)
    {
      return a0 + boost::simd::meta::cardinal_of<T>::value - 1;
    }

    // Retrieve the biggest valid index when gathering/scattering a SIMD vector
    template<typename T, typename A0, typename X>
    std::size_t maxpos(boost::simd::native<A0, X> const& a0)
    {
      return boost::simd::maximum(a0);
    }
  }

  namespace memory
  {
    /*!
      @brief Enforce safe container access

      For any given Container, checks if accessing a value of type Type
      at index p is correct.

      @tparam Type  Type to be read from Container
      @param  c     Container to use as reference
      @param  p     Index to check
    **/
    template<typename Type, typename Container, typename Position>
    bool is_safe(Container const& c, Position const& p)
    {
      std::size_t pos = details::maxpos<Type>(p);
      return pos < c.size();
    }

    /// @overload
    template<typename Container, typename Position>
    bool is_safe(Container const& c, Position const& p)
    {
      return p < c.size();
    }
  }
}

#endif
