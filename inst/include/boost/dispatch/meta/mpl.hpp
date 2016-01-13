//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_MPL_HPP_INCLUDED
#define BOOST_DISPATCH_META_MPL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various memory hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for mpl integral types
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct mpl_integral_ : mpl_integral_< typename T::parent >
  {
    typedef mpl_integral_< typename T::parent > parent;
  };
}

namespace details
{
  ////////////////////////////////////////////////////////////////////////////////
  // Some MPL introspection helpers
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, class Enable = boost::mpl::integral_c_tag>
  struct is_mpl_integral
       : boost::mpl::false_
  {
  };

  template<class T>
  struct is_mpl_integral<T, typename T::tag>
       : boost::mpl::true_
  {
  };

  template<class T,class Origin>
  struct hierarchy_of< T
                     , Origin
                     , typename boost::enable_if< details::is_mpl_integral<T> >::type
                     >
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< T, stripped >, stripped, Origin>::type origin_;

    typedef meta::
    mpl_integral_< typename meta::
                   hierarchy_of< typename T::value_type
                               , origin_
                               >::type
                 >                                                            type;
  };

  template<class T>
  struct value_of< T, typename boost::enable_if< details::is_mpl_integral<T> >::type >
  {
    typedef typename T::value_type type;
  };

  template<class T>
  struct model_of< T, typename boost::enable_if< details::is_mpl_integral<T> >::type >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef boost::mpl::integral_c<X, T::value> type;
      };
    };
  };

  template<class T, bool IsMPL = details::is_mpl_integral<T>::value>
  struct extract_mpl
       : extract_mpl<typename meta::value_of<T>::type>
  {
  };

  template<class T>
  struct extract_mpl<T, true>
  {
    typedef T type;
  };
}

namespace meta
{
  template<class T>
  struct  mpl_integral_< unspecified_<T> >
        : hierarchy_of<typename details::extract_mpl<T>::type::value_type,T>::type
  {
    typedef typename hierarchy_of<typename details::extract_mpl<T>::type::value_type,T>::type parent;
  };
} } }

#endif
