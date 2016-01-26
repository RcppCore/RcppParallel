//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GEARMAT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GEARMAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_gearmat gearmat
 *
 * \par Description
 *    a = gearmat(n,i,j,as_<T>()) is the n-by-n matrix with ones on
 *    the sub- and super-diagonals, sign(i) in the (1,abs(i)) position,
 *    sign(j) in the (n,n+1-abs(j)) position, and zeros everywhere else.
 *    defaults: i = n, j = -n.
 *
 *    properties:
 *    all eigenvalues are of the form 2*cos(a) and the eigenvectors
 *      are of the form [sin(w+a), sin(w+2a), ..., sin(w+na)].
 *      (the values of a and w are given in the reference below.)
 *    a can have double and triple eigenvalues and can be defective.
 *    gearmat(n) is singular.

 *    Reference:
 *    C. W. Gear, A simple set of test matrices for eigenvalue programs,
 *    Math.  Comp., 23 (1969), pp. 119-125.
 *
 * \code
 * #include <nt2/include/functions/gearmat.hpp>
 * \endcode
 *
**/
//==============================================================================
// gearmat actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag gearmat_ of functor gearmat
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct gearmat_ : ext::abstract_<gearmat_>
    {
      typedef ext::abstract_<gearmat_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_gearmat_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::gearmat_, Site> dispatching_gearmat_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::gearmat_, Site>();
    }
    template<class... Args>
    struct impl_gearmat_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::gearmat_, gearmat, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::gearmat_, gearmat, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::gearmat_, gearmat, 4)


  template < class T, class A0>
  typename meta::call<tag::gearmat_(A0 const&, meta::as_<T>)>::type
  gearmat(A0 const & n)
  {
    return gearmat(n, meta::as_<T>());
  }

}

#endif
