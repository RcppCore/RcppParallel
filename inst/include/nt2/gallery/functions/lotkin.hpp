//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LOTKIN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LOTKIN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lotkin lotkin
 *
 *    a = lotkin(n) is the hilbert matrix with its first row
 *    altered to all ones.  a is unsymmetric, ill-conditioned, and has
 *    many negative eigenvalues of small magnitude. its inverse has
 *    integer entries and is known explicitly.
 *
 *    Reference:
 *    M. Lotkin, A set of test matrices, M.T.A.C., 9 (1955), pp. 153-161.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lotkin.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lotkin actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lotkin_ of functor lotkin
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lotkin_ : ext::abstract_<lotkin_>
    {
      typedef ext::abstract_<lotkin_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lotkin_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lotkin_, Site> dispatching_lotkin_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lotkin_, Site>();
    }
    template<class... Args>
    struct impl_lotkin_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lotkin_, lotkin, 2)

}

#endif

