//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2015          J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_OPTIONS_HPP_INCLUDED
#define NT2_LINALG_OPTIONS_HPP_INCLUDED

#include <nt2/core/options.hpp>
#include <nt2/sdk/meta/policy.hpp>
#include <nt2/core/options.hpp>
namespace nt2
{
  namespace ext
  {
    struct matrix_    : boost::mpl::true_   {}; //used in lu, qr, geneig, nseig, symeig
    struct vector_    : boost::mpl::false_  {}; //used in lu, qr, geneig, nseig, symeig
    struct fast_      : boost::mpl::false_  {}; //used in linsolve
    struct precise_   : boost::mpl::false_  {}; //used in linsolve
    struct classic_   : boost::mpl::false_  {}; //used in linsolve
    struct econ_      : boost::mpl::false_  {}; //used in svd, qr
    struct eigs_      : boost::mpl::false_  {}; //used in schur
    struct no_perm_   : boost::mpl::false_  {}; //used in balance
    struct perm_      : boost::mpl::false_  {}; //used in balance
    struct balance_   : boost::mpl::true_   {}; //used in nseig
    struct no_balance_: boost::mpl::false_  {}; //used in nseig
    struct alphabeta_ : boost::mpl::false_  {}; //used in geneig
    struct lambda_    : boost::mpl::false_  {}; //used in geneig
    struct in_place_  : boost::mpl::false_  {};
  }

  nt2::policy<ext::matrix_>      const matrix_;
  nt2::policy<ext::vector_>      const vector_;
  nt2::policy<ext::fast_>        const fast_;
  nt2::policy<ext::precise_>     const precise_;
  nt2::policy<ext::classic_>     const classic_;
  nt2::policy<ext::econ_>        const econ_;
  nt2::policy<ext::eigs_>        const eigs_;
  nt2::policy<ext::no_perm_>     const no_perm_;
  nt2::policy<ext::perm_>        const perm_;
  nt2::policy<ext::balance_>     const balance_;
  nt2::policy<ext::no_balance_>  const no_balance_;
  nt2::policy<ext::alphabeta_>   const alphabeta_;
  nt2::policy<ext::lambda_>      const lambda_;
  nt2::policy<ext::in_place_>    const in_place_;
}

#endif
