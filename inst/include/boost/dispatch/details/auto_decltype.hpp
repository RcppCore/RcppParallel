//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014  NUMSCALE SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DETAILS_AUTO_DECLTYPE_HPP_INCLUDED
#define BOOST_DISPATCH_DETAILS_AUTO_DECLTYPE_HPP_INCLUDED

#include <boost/config.hpp>

/*!
    Helpers to define functions using the auto/decltype syntax in C++11, without
    the trailing return type in C++14.
*/

#define BOOST_AUTO_DECLTYPE_BODY_SFINAE(body) -> decltype(body) { return body; }

#if 0 // useful for debugging with GCC 4.7+
#define BOOST_AUTO_DECLTYPE auto
#define BOOST_AUTO_DECLTYPE_HEADER(body)
#define BOOST_AUTO_DECLTYPE_BODY(body) { return body; }
#elif defined(BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION) || defined(BOOST_NO_CXX14_DECLTYPE_AUTO) || BOOST_VERSION < 105800
#define BOOST_AUTO_DECLTYPE auto
#define BOOST_AUTO_DECLTYPE_HEADER(body) -> decltype(body)
#define BOOST_AUTO_DECLTYPE_BODY(body) -> decltype(body) { return body; }
#else
#define BOOST_AUTO_DECLTYPE decltype(auto)
#define BOOST_AUTO_DECLTYPE_HEADER(body)
#define BOOST_AUTO_DECLTYPE_BODY(body) { return body; }
#endif

#endif
