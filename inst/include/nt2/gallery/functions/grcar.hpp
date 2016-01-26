//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GRCAR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GRCAR_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_grcar grcar
 *
 * \par Description
 *    grcar(n,k) is an n-by-n toeplitz matrix with -1s on
 *    the subdiagonal, 1s on the diagonal, and k superdiagonals of 1s.
 *    the default is k = 3.  the eigenvalues are sensitive.
 *   References:
 *     [1] J. F. Grcar, Operator coefficient methods for linear equations,
 *     Report SAND89-8691, Sandia National Laboratories, Albuquerque,
 *     New Mexico, 1989 (Appendix 2).
 *     [2] N. M. Nachtigal, L. Reichel and L. N. Trefethen, A hybrid GMRES
 *     algorithm for nonsymmetric linear systems, SIAM J. Matrix Anal.
 *     Appl., 13 (1992), pp. 796-825.
 *
 *
 *
 * \code
 * #include <nt2/include/functions/grcar.hpp>
 * \endcode
 *
**/
//==============================================================================
// grcar actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag grcar_ of functor grcar
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct grcar_ : ext::abstract_<grcar_>
    {
      typedef ext::abstract_<grcar_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_grcar_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::grcar_, Site> dispatching_grcar_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::grcar_, Site>();
    }
    template<class... Args>
    struct impl_grcar_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::grcar_, grcar, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::grcar_, grcar, 3)


  template < class T, class A0>
  typename meta::call<tag::grcar_(A0 const&, meta::as_<T>)>::type
  grcar(A0 const & n)
  {
    return grcar(n, 3, meta::as_<T>());
  }

}

#endif
