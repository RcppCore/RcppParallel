//==================================================================================================
/*!
  @file

  Defines the enable_if_type SFINAE helper

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_DISPATCH_META_ENABLE_IF_TYPE_HPP_INCLUDED
#define BOOST_DISPATCH_META_ENABLE_IF_TYPE_HPP_INCLUDED

namespace boost
{
  /*!
    @brief SFINAE context for type existence validation

    Checks if a type is defined in a way this piece of informations can be
    used in SFINAE contexts.

    @tparam T Type to check existence of.
    @tparam R Type to return if @c T is defined.
  **/
  template<typename T, typename R=void> struct enable_if_type { using type =  R; };
}

#endif
