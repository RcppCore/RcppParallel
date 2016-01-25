//==================================================================================================
/*!
  @file

  Provides a kitchen sink include files for the Boost.Dispatch library

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/as.hpp>
#include <boost/dispatch/config.hpp>
#include <boost/dispatch/function.hpp>
#include <boost/dispatch/hierarchy.hpp>
#include <boost/dispatch/hierarchy_of.hpp>
#include <boost/dispatch/meta.hpp>
#include <boost/dispatch/models.hpp>
#include <boost/dispatch/property_of.hpp>

/// Main Boost namespace
namespace boost
{
  /// Main Boost.Dispatch namespace
  namespace dispatch
  {
    /*!
      @defgroup group-concept Concepts
      Concepts defined by the library
    **/

    /*!
      @defgroup group-api User API
      User level library components
    **/

    /*!
      @ingroup group-api
      @defgroup group-hierarchy Hierarchy Functions and Traits
      Utility for handling type hierarchies provided by the library
    **/

    /*!
      @ingroup group-api
      @defgroup group-function Dispatchable Functions Utilities
      Utilities for defining and overloading dispatchable functions
    **/

    /*!
      @ingroup group-hierarchy
      @defgroup group-tag Hierarchy Tags
      Hierarchies tags provided by the library
    **/

    /*!
      @ingroup group-api
      @defgroup group-meta Meta-programming Utilities
      Meta-programming related components
    **/

    /*!
      @ingroup group-meta
      @defgroup group-generation Type Generation Traits
      Meta-programming related components
    **/

    /*!
      @ingroup group-meta
      @defgroup group-introspection Type Introspection Traits
      Meta-programming related components
    **/

    /// Boost.Dispatch Extension points namespace
    namespace ext
    {
      /*!
        @defgroup group-extension Extension points
        Extension points for library components
      **/
    }
  }
}

#endif
