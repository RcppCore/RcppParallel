//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_SMOKE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_SMOKE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_smoke smoke
 *
 *    smoke(n) is an n-by-n matrix with 1s on the
 *    superdiagonal, 1 in the (n,1) position, and powers of roots of
 *    unity along the diagonal.
 *
 *    smoke(n,1) is the same except for a zero (n,1) element.
 *
 *    the eigenvalues of smoke(n,1) are the n'th roots of
 *    unity; those of smoke(n) are the n'th roots of unity
 *    times 2^(1/n).
 *
 *    Reference:
 *    L. Reichel and L.N. Trefethen, Eigenvalues and
 *    pseudo-eigenvalues of Toeplitz matrices, Linear Algebra
 *    and Appl., 162-164:153-185, 1992.
 *
 * \par Header file
 *
 * \code
! * #include <nt2/include/functions/smoke.hpp>
 * \endcode
 *
 **/
//==============================================================================
// smoke actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag smoke_ of functor smoke
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct smoke_ : ext::abstract_<smoke_>
    {
      typedef ext::abstract_<smoke_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_smoke_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::smoke_, Site> dispatching_smoke_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::smoke_, Site>();
    }
    template<class... Args>
    struct impl_smoke_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::smoke_, smoke, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::smoke_, smoke, 3)

}

#endif

