//==============================================================================
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_LOCALITY_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_LOCALITY_HPP_INCLUDED

namespace nt2
{
  /*!
      @brief Host locality option

      By default, memory of tables is stored on the host (ie the CPU).
  **/
  struct host_;

  /*!
      @brief Device locality option

      This option indicates that the memory of a table has to be stored in
      the memory of an external device (liek a GPU for instance).

  **/
  struct device_;

  namespace tag
  {
    /// @brief Option tag for storage_scheme options
    struct locality_;
  }
}

#endif
