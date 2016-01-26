//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_DETAILS_EMPTY_BODY_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_DETAILS_EMPTY_BODY_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

namespace nt2
{
  namespace details
  {

    struct empty_body
    {
      void operator()( tbb::flow::continue_msg ) const
      {}
    };
  }
}

#endif
#endif
