//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ITERATOR_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/pointee.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some hierarchies
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct iterator_ : iterator_< typename T::parent >
  {
    typedef iterator_< typename T::parent > parent;
  };

  /// INTERNAL ONLY
  template<class T> struct iterator_< unspecified_<T> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  /// INTERNAL ONLY
  template<class T> struct iterator_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T> parent;
  };
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::iterator_;
} } }

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for all iterator types
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace details
{
  template<class T>
  struct  value_of< T
                  , typename
                    boost::enable_if_c< meta::is_iterator<T>::value>::type
                  >
        : boost::pointee<T>
  {};

  template<>
  struct  value_of<void*>
  {
    typedef void type;
  };

  template<class T, class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename
                        boost::enable_if_c< meta::is_iterator<T>::value>::type
                      >
  {
    typedef typename boost::pointee<T>::type pointee_type;
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same<T, stripped>, stripped, Origin>::type origin_;
    typedef meta::iterator_ < typename
                              meta::hierarchy_of<pointee_type,origin_>::type > type;
  };
}

namespace meta
{
  template<class Origin>
  struct  hierarchy_of<void*, Origin>
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same<void*, stripped>, stripped, Origin>::type origin_;
    typedef meta::iterator_<meta::generic_<meta::void_<origin_> > >  type;
  };
} } }

#endif
