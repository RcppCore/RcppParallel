//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_PROD_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_PROD_HPP_INCLUDED

#include <boost/simd/reduction/include/functions/prod.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::prod_} **/
    struct prod_ {};
    #endif
    using boost::simd::tag::prod_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::prod} **/
  template<class... Args>
  details::unspecified prod(Args&&... args);
  #endif
  using boost::simd::prod;
}

#endif
