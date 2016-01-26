//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/simd/memory/allocator.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template< typename T
          , typename Allocator = boost::simd::allocator<T>
          > class buffer;

  //============================================================================
  // External append
  //============================================================================
    template<typename T, typename A, typename Iterator>
    BOOST_FORCEINLINE void append( buffer<T,A>& c, Iterator b, Iterator e )
    {
      c.append(b,e);
    }
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename Allocator>
  struct value_of< nt2::memory::buffer<T,Allocator> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename Allocator>
  struct model_of< nt2::memory::buffer<T,Allocator> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef typename Allocator::template rebind<X>::other  alloc_t;
        typedef nt2::memory::buffer<X,alloc_t>                 type;
      };
    };
  };
} } }

#endif
