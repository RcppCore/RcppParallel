//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LESP_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LESP_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lesp lesp
 *
 *    lesp(n) is an n-by-n matrix whose eigenvalues are real
 *    and smoothly-distributed in the interval approximately
 *    [-2*n-3.5, -4.5]. the sensitivities of the eigenvalues increase
 *    exponentially as the eigenvalues grow more negative. the matrix
 *    is similar to the symmetric tridiagonal matrix with the same
 *    diagonal entries and with off-diagonal entries 1, via a similarity
 *    transformation with d = from_diag([1!,2!,...,n!]).

 *    References:
 *    [1] H. W. J. Lenferink and M. N. Spijker, On the use of stability
 *        regions in the numerical analysis of initial value problems,
 *        Math. Comp., 57 (1991), pp. 221-237.
 *    [2] L. N. Trefethen, Pseudospectra of matrices,
 *        Numerical Analysis 1991, Proceedings of the 14th Dundee
 *        Conference, D.F. Griffiths and G.A. Watson, eds,
 *        Pitman Research Notes in Mathematics, volume 260,
 *        Longman Scientific and Technical, Essex, UK, 1992,
 *        pp. 234-266.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lesp.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lesp actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lesp_ of functor lesp
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lesp_ : ext::abstract_<lesp_>
    {
      typedef ext::abstract_<lesp_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lesp_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lesp_, Site> dispatching_lesp_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lesp_, Site>();
    }
    template<class... Args>
    struct impl_lesp_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lesp_, lesp, 2)

}

#endif

