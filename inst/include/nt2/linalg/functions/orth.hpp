//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_ORTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_ORTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * @brief orth basis of image space
 *    q = orth(a) is an orthonormal basis for the range of a.
 *    that is, transconj(q)*q = i, the columns of q span the same space as
 *    the columns of a, and the number of columns of q is the
 *    rank of a.
 *    q = orth(a, tol) produces an image space basis of a compatible with the
 *    kernel basis given by null(a, tol)
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag orth_ of functor orth
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct orth_ :  ext::abstract_<orth_> { typedef ext::abstract_<orth_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_orth_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::orth_, Site> dispatching_orth_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::orth_, Site>();
    }
    template<class... Args>
    struct impl_orth_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orth_, orth, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orth_, orth, 2)

}

#endif
