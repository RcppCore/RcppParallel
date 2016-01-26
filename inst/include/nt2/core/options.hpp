//==============================================================================
//          Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_OPTIONS_HPP_INCLUDED
#define NT2_CORE_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/meta/policy.hpp>

namespace nt2
{
  namespace ext
  {
    struct lower_     : boost::mpl::false_  {}; //used in chol, symeig, ldl and many statistical and euler functors
    struct upper_     : boost::mpl::false_  {}; //used in chol, symeig, ldl and many statistical and euler functors
    struct real_      : boost::mpl::false_  {}; //used in schur
    struct cmplx_     : boost::mpl::false_  {}; //used in schur
    struct sort_      : boost::mpl::false_  {}; //used in schur
    struct both_      : boost::mpl::false_  {}; //used in balance
    struct none_      : boost::mpl::false_  {}; //used in balance
    struct raw_       : boost::mpl::false_  {}; //used in lu, qr, svd
  }

  nt2::policy<ext::lower_>       const lower_;
  nt2::policy<ext::upper_>       const upper_;
  nt2::policy<ext::real_>        const real_;
  nt2::policy<ext::cmplx_>       const cmplx_;
  nt2::policy<ext::sort_>        const sort_;
  nt2::policy<ext::both_>        const both_;
  nt2::policy<ext::none_>        const none_;
  nt2::policy<ext::raw_>         const raw_;
}

#endif
