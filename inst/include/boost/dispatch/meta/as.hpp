//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_HPP_INCLUDED

#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
    Type wrapper hierarchy.

    @par Models:

    Hierarchy

    @tparam T Wrapped type hierarchy
  **/
  template<class T> struct target_ : target_< typename T::parent >
  {
    typedef target_< typename T::parent > parent;
  };

  /// INTERNAL ONLY
  template<class T> struct target_< unspecified_<T> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  /// INTERNAL ONLY
  template<class T> struct  target_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T> parent;
  };

  /*!
    @brief Lightweight type wrapper.

    Some implementation details of NT2 require types to be wrapped into an
    empty structure so the type can be passed as a "ghostly" instance.
    as_ performs such a wrapping.

    To discriminate as_ from the type @c T it wraps, its hierarcy is defined as
    @c target_<hierarchy_of<T>::type>

    @par Models:

    @metafunction
  **/
  template<class T> struct as_
  {
    typedef T type;
  };

  /*!
    @brief Extract a target type

    For any type @c T, if T is a Target, returns the target type.
    Otherwise, it behaves as the identity meta-function
  **/
  template<class T> struct target_value
  {
    typedef T type;
  };

  /// INTERNAL ONLY
  template<class T> struct target_value< as_<T> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY
  /// Register as_ hierarchy
  template<class T, class Origin>
  struct hierarchy_of< as_<T>, Origin>
  {
    typedef typename remove_const<Origin>::type               stripped;
    typedef typename mpl::if_ < is_same< stripped, as_<T> >
                              , stripped
                              , Origin
                              >::type                         origin_;
    typedef target_<typename hierarchy_of<T, origin_>::type>  type;
  };

  /// INTERNAL ONLY
  /// The value of as_<T> is T
  template<class T> struct value_of< as_<T> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY
  template<class T> struct model_of< as_<T> >
  {
    struct type
    {
      template<class X> struct apply { typedef as_<X> type; };
    };
  };
} } }

#endif
