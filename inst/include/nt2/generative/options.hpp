 //==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GENERATIVE_OPTIONS_HPP_INCLUDED
#define NT2_GENERATIVE_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/meta/policy.hpp>

namespace nt2
{
  namespace ext
  {
    struct meshgrid_  {};
    struct whole_     {};
  }

  policy<ext::whole_>    const whole_;
  policy<ext::meshgrid_> const meshgrid_;
}

#endif
