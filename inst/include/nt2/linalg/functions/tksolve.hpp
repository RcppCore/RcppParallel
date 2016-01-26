//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TKSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TKSOLVE_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_tksolve tksolve
 *
 * \par Description
 * function x = tksolve(r, b, tran)
 * ksolve     solves block triangular kronecker system.
 *            x = tksolve(r, b, tran) solves
 *                  a*x = b  if tran = '',
 *                 a'*x = b  if tran = 't',
 *            where a = kron(eye,r) + kron(transpose(r),eye).
 *            default: tran = ''.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tksolve.hpp>
 * \endcode
 *
 *
 * \param a the matrix or vector expression a
 *
 * \param type of tksolve required
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag tksolve_ of functor tksolve
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct tksolve_ :  ext::abstract_<tksolve_> { typedef ext::abstract_<tksolve_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_tksolve_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::tksolve_, Site> dispatching_tksolve_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::tksolve_, Site>();
    }
    template<class... Args>
    struct impl_tksolve_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tksolve_, tksolve, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tksolve_, tksolve, 3)

}

#endif
