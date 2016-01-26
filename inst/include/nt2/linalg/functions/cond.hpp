//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_COND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_COND_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_trace trace
 *
 * \par Description
 * Elementary Least square
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/trace.hpp>
 * \endcode
 *
 *
 * \param a the matrix a
 *
 * \param p the norm in which trace is computed
 *          p can be 1, 2 inf or 'fro'
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/
//==============================================================================
// trace actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag trace_ of functor trace
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct cond_ :  ext::abstract_<cond_> { typedef ext::abstract_<cond_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_cond_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::cond_, Site> dispatching_cond_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::cond_, Site>();
    }
    template<class... Args>
    struct impl_cond_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cond_, cond, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cond_, cond, 2)
}

#endif
