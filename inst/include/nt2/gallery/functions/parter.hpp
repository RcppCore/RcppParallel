//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_PARTER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_PARTER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_parter parter
 *
 *      c = parter(n) returns the matrix c such that
 *      c(i,j) = 1/(i-j+0.5).
 *      c is a cauchy matrix and a toeplitz matrix.
 *      most of the singular values of c are very close to pi.
 *
 *    References:
 *    [1] MathWorks Newsletter, Volume 1, Issue 1, March 1986, page 2.
 *    [2] A. Bottcher and B. Silbermann, Introduction to Large Truncated
 *        Toeplitz Matrices, Springer-Verlag, New York, 1999; Sec. 4.5.
 *    [3] S. V. Parter, On the distribution of the singular values of
 *        Toeplitz matrices, Linear Algebra and Appl., 80(1986), pp. 115-130.
 *    [4] E. E. Tyrtyshnikov, Cauchy-Toeplitz matrices and some applications,
 *        Linear Algebra and Appl., 149 (1991), pp. 1-18.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/parter.hpp>
 * \endcode
 *
 **/
//==============================================================================
// parter actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag parter_ of functor parter
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct parter_ : ext::abstract_<parter_>
    {
      typedef ext::abstract_<parter_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_parter_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::parter_, Site> dispatching_parter_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::parter_, Site>();
    }
    template<class... Args>
    struct impl_parter_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::parter_, parter, 2)

}

#endif

