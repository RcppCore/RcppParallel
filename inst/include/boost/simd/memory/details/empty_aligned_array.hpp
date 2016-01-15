//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_EMPTY_ALIGNED_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_EMPTY_ALIGNED_ARRAY_HPP_INCLUDED

#include <boost/simd/forward/aligned_array.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /// INTERNAL ONLY
  template<class T, std::size_t Align>
  struct aligned_array<T,0,Align>
  {
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    iterator        begin()       { return       iterator(reinterpret_cast<      T*>(this)); }
    const_iterator  begin() const { return const_iterator(reinterpret_cast<const T*>(this)); }
    const_iterator cbegin() const { return const_iterator(reinterpret_cast<const T*>(this)); }

    iterator        end()       { return  begin(); }
    const_iterator  end() const { return  begin(); }
    const_iterator cend() const { return cbegin(); }

    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    reverse_iterator        rbegin()        { return reverse_iterator(end());         }
    const_reverse_iterator  rbegin()  const { return const_reverse_iterator(end());   }
    reverse_iterator        rend()          { return reverse_iterator(begin());       }
    const_reverse_iterator  rend()    const { return const_reverse_iterator(begin()); }
    const_reverse_iterator  crbegin() const { return const_reverse_iterator(end());   }
    const_reverse_iterator  crend()   const { return const_reverse_iterator(begin()); }

    reference operator[](size_type ) { return failed_rangecheck(); }
    const_reference operator[](size_type ) const { return failed_rangecheck(); }

    reference       at(size_type )        { return failed_rangecheck(); }
    const_reference at(size_type ) const  { return failed_rangecheck(); }

    reference       front()       { return failed_rangecheck(); }
    const_reference front() const { return failed_rangecheck(); }
    reference       back()        { return failed_rangecheck(); }
    const_reference back()  const { return failed_rangecheck(); }

    static size_type size()     { return 0;     }
    static bool      empty()    { return true;  }
    static size_type max_size() { return 0;     }

    static const std::size_t static_size = 0;

    template<std::size_t A2> void swap (aligned_array<T,0,A2>&) {}

    pointer       c_array()     { return 0; }
    pointer       data()        { return 0; }
    const_pointer data() const  { return 0; }

    template <typename T2, std::size_t A2>
    aligned_array<T,0,Align>& operator= (const aligned_array<T2,0,A2>&)
    {
      return *this;
    }

    void assign (const T&) {}
    void fill   (const T& ) {}

    static reference failed_rangecheck()
    {
      BOOST_ASSERT_MSG( 0, "Out of range access on aligned_array" );
      static T placeholder;
      return placeholder;
    }
  };
} }

#endif
