//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_PROLATE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_PROLATE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_prolate prolate
 *
 *    a =prolate(n,w) is the n-by-n prolate matrix with
 *    parameter w. it is a symmetric toeplitz matrix.
 *    if 0 < w < 0.5 then
 *      1. a is positive definite
 *      2. the eigenvalues of a are distinct, lie in (0, 1), and tend to
 *         cluster around 0 and 1.
 *    w defaults to 0.25.
 *
 *    Reference:
 *    J. M. Varah. The Prolate matrix. Linear Algebra and Appl.,
 *    187:269-278, 1993.
 *
 * \par Header file
 *
 * \code
! * #include <nt2/include/functions/prolate.hpp>
 * \endcode
 *
 **/
//==============================================================================
// prolate actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag prolate_ of functor prolate
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct prolate_ : ext::abstract_<prolate_>
    {
      typedef ext::abstract_<prolate_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_prolate_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::prolate_, Site> dispatching_prolate_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::prolate_, Site>();
    }
    template<class... Args>
    struct impl_prolate_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::prolate_, prolate, 2)

}

#endif

