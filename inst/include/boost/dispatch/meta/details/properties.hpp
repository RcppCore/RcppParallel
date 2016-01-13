//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_PROPERTIES_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_PROPERTIES_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/details/hierarchy_base.hpp>

namespace boost { namespace dispatch
{

namespace meta
{
  //============================================================================
  /*!
   * The fundamental_ hierarchy gather all usual C++ base types.
   */
  //============================================================================
  template<class T> struct fundamental_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  //============================================================================
  /*!
   * The bool_ hierarchy represents the \c bool C++ type.
   */
  //============================================================================
  template<class T> struct bool_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };

  //============================================================================
  /*!
   * The void_ hierarchy represents the \c void C++ type.
   */
  //============================================================================
  template<class T> struct void_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };

  //============================================================================
  /*!
   * The arithmetic_ hierarchy gather all usual C++ base types except \c bool.
   */
  //============================================================================
  template<class T> struct arithmetic_ : fundamental_<T>
  {
    typedef fundamental_<T>  parent;
  };

  //============================================================================
  /*!
   * The integer_ hierarchy gather all usual C++ integral types except \c bool.
   */
  //============================================================================
  template<class T> struct integer_ : arithmetic_<T>
  {
    typedef arithmetic_<T>  parent;
  };

  //============================================================================
  /*!
   * The unsigned_ hierarchy gather all native unsigned types of C++
   */
  //============================================================================
  template<class T> struct unsigned_ : integer_<T>
  {
    typedef integer_<T> parent;
  };

  //============================================================================
  /*!
   * The signed_ hierarchy gather all native signed types of C++ including
   * floating-points type.
   */
  //============================================================================
  template<class T>
  struct  signed_ : boost::mpl::if_ < meta::is_integral<T>
                                    , integer_<T>
                                    , arithmetic_<T>
                                    >::type
  {
    typedef typename boost::mpl::if_< meta::is_integral<T>
                                    , integer_<T>
                                    , arithmetic_<T>
                                    >::type                 parent;
  };

  //============================================================================
  /*!
   * The floating_ hierarchy gathers all C++ floating-point types
   */
  //============================================================================
  template<class T> struct floating_ : signed_<T>
  {
    typedef signed_<T>  parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Sign based hierarchy - gather integral types of a given signedness
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct int_  : signed_<T>
  {
    typedef signed_<T>  parent;
  };

  template<class T> struct uint_ : unsigned_<T>
  {
    typedef unsigned_<T>  parent;
  };
}

namespace details
{
  struct lsigned_
  {
    template<class T> struct apply : boost::is_signed<T> {};
  };

  template<typename T>
  struct  signed_or_not
        : boost::mpl::if_ < meta::is_floating_point<T>
                                    , meta::floating_<T>
                                    , typename  boost::mpl::if_
                                        < meta::behave_as<details::lsigned_,T>
                                        , meta::int_<T>
                                        , meta::uint_<T>
                                        >::type
                                    >
  {};
}

namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy - gather type which sizeof is equal to a given value
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct type8_ : details::signed_or_not<T>::type
  {
    typedef typename details::signed_or_not<T>::type  parent;
  };

  template<class T>
  struct type16_ : details::signed_or_not<T>::type
  {
    typedef typename details::signed_or_not<T>::type  parent;
  };

  template<class T>   struct floating_sized_
                    : boost::mpl::if_ < meta::is_floating_point<T>
                                      , floating_<T>
                                      , typename details::signed_or_not<T>::type
                                      >::type
  {
    typedef typename boost::mpl::if_< meta::is_floating_point<T>
                                    , floating_<T>
                                    , typename details::signed_or_not<T>::type
                                    >::type  parent;
  };

  template<class T> struct type32_ : floating_sized_<T>
  {
    typedef floating_sized_<T> parent;
  };

  template<class T> struct type64_ : floating_sized_<T>
  {
    typedef floating_sized_<T> parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of integers
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct ints8_  : type8_<T>
  {
    typedef type8_<T> parent;
  };

  template<class T> struct ints16_ : type16_<T>
  {
    typedef type16_<T> parent;
  };

  template<class T> struct ints32_ : type32_<T>
  {
    typedef type32_<T> parent;
  };

  template<class T> struct ints64_ : type64_<T>
  {
    typedef type64_<T> parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of signed integers
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct int8_   : ints8_<T>
  {
    typedef ints8_<T> parent;
  };

  template<class T> struct int16_  : ints16_<T>
  {
    typedef ints16_<T> parent;
  };

  template<class T> struct int32_  : ints32_<T>
  {
    typedef ints32_<T> parent;
  };

  template<class T> struct int64_  : ints64_<T>
  {
    typedef ints64_<T> parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of unsigned integers
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct uint8_   : ints8_<T>
  {
    typedef ints8_<T> parent;
  };

  template<class T> struct uint16_  : ints16_<T>
  {
    typedef ints16_<T> parent;
  };

  template<class T> struct uint32_  : ints32_<T>
  {
    typedef ints32_<T> parent;
  };

  template<class T> struct uint64_  : ints64_<T>
  {
    typedef ints64_<T> parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Native real types hierarchy
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct double_ : type64_<T>
  {
    typedef type64_<T> parent;
  };

  template<class T> struct single_ : type32_<T>
  {
    typedef type32_<T> parent;
  };

  template<class T> struct long_double_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };

} } }

#endif
